#include <mpi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "intstack.h"

enum resource { COUNTER, PRICE, SHELF, RESOURCE_MAX };
enum request { REQUEST_ACQUIRE, REQUEST_FREE, REQUEST_MAX };

struct resource_request {
  int request_type;
  int resourse_id;
};

struct resource_response {
  bool result;
};

typedef enum resource resource_t;
typedef struct resource_request resource_req_t;
typedef struct resource_response resource_resp_t;

static int rank, size;
static MPI_Datatype resource_req_type, resource_res_type;

static void _init(int *argc, char ***argv) {
  MPI_Init(argc, argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
}

static void _finit(void) { MPI_Finalize(); }

static void _execute_procedure(uint64_t timeout, resource_t resource) {
  printf("Resource: Executed by Proc%d as resource %d.\n", rank, (int)resource);
  sleep(timeout);
}

static void _client_select_resource(resource_req_t *request) {
  switch (rand() % RESOURCE_MAX) {
    case 0:
      request->resourse_id = COUNTER;
      break;
    case 1:
      request->resourse_id = PRICE;
      break;
    case 3:
      request->resourse_id = SHELF;
      break;
    default:
      break;
  }
}

static void _run_client(void) {
  const int timeout_s = (rank < 3) ? 1 : rank * 0.8;
  resource_req_t request;
  resource_resp_t server_response;
  MPI_Status recv_status;

  printf("Proc%d: Will wait for %ds.\n", rank, timeout_s);
  while (true) {
    request.request_type = REQUEST_ACQUIRE;
    _client_select_resource(&request);
    printf("Proc%d: Send resource acquire request to Server.\n", rank);
    MPI_Send(&request, 1, resource_req_type, 0, 0, MPI_COMM_WORLD);
    printf("Proc%d: Wait for Server response.\n", rank);
    MPI_Recv(&server_response, 1, resource_res_type, 0, 0, MPI_COMM_WORLD,
             &recv_status);
    if (server_response.result) {
      request.request_type = REQUEST_FREE;
      _execute_procedure(timeout_s, request.resourse_id);
      MPI_Send(&request, 1, resource_req_type, 0, 0, MPI_COMM_WORLD);
      MPI_Recv(&server_response, 1, resource_res_type, 0, 0, MPI_COMM_WORLD,
               &recv_status);
    }
  }
}

static void _run_server(void) {
  resource_req_t client_request;
  resource_resp_t response;
  MPI_Status status;
  bool resource_acquired[RESOURCE_MAX] = {false};
  intstack_t queue[RESOURCE_MAX] = {0};

  memset(resource_acquired, 0, sizeof(resource_acquired));
  memset(queue, 0, sizeof(queue));

  puts("Server: Start listening.");

  while (true) {
    MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    if (0 != status.MPI_SOURCE) {
      MPI_Recv(&client_request, 1, resource_req_type, status.MPI_SOURCE, 0,
               MPI_COMM_WORLD, &status);
      intstack_t *resource_queue = &queue[client_request.resourse_id];

      if (REQUEST_ACQUIRE == client_request.request_type) {
        printf("Server: Process %d tries to acquire the resource %d.\n",
               status.MPI_SOURCE, client_request.resourse_id);

        if (resource_acquired[client_request.resourse_id]) {
          printf(
              "Server: Process %d were added to stack #%d of blocked "
              "processes.\n",
              status.MPI_SOURCE, client_request.resourse_id);

          intstack_append(resource_queue, status.MPI_SOURCE);
        } else {
          printf("Server: Process %d acquires the resource %d.\n",
                 status.MPI_SOURCE, client_request.resourse_id);

          response.result = true;
          MPI_Send(&response, 1, resource_res_type, status.MPI_SOURCE, 0,
                   MPI_COMM_WORLD);
        }
      } else if (REQUEST_FREE == client_request.request_type) {
        printf("Server: Process %d frees the resource %d.\n", status.MPI_SOURCE,
               client_request.resourse_id);

        resource_acquired[client_request.resourse_id] = false;
        response.result = true;
        MPI_Send(&response, 1, resource_res_type, status.MPI_SOURCE, 0,
                 MPI_COMM_WORLD);

        if (!intstack_is_empty(resource_queue)) {
          printf(
              "Server: Process %d acquires the resource %d in same "
              "iteration.\n",
              status.MPI_SOURCE, client_request.resourse_id);

          const int send_rank = intstack_pop(resource_queue);
          response.result = true;
          MPI_Send(&response, 1, resource_res_type, send_rank, 0,
                   MPI_COMM_WORLD);
        }
      } else {
        printf("Server: Unknown request type: %d.\n",
               client_request.request_type);
      }
    }
  }
}

static void _register_mpi_types(void) {
  static const int req_length[2] = {1, 1}, res_length[1] = {1};
  static const MPI_Aint req_offsets[2] = {offsetof(resource_req_t,
                                                   request_type),
                                          offsetof(resource_req_t,
                                                   resourse_id)},
                        res_offsets[1] = {offsetof(resource_resp_t, result)};
  static const MPI_Datatype req_types[2] = {MPI_INT, MPI_INT},
                            res_types[1] = {MPI_INT};
  MPI_Type_create_struct(2, req_length, req_offsets, req_types,
                         &resource_req_type);
  MPI_Type_create_struct(1, res_length, res_offsets, res_types,
                         &resource_res_type);
  MPI_Type_commit(&resource_req_type);
  MPI_Type_commit(&resource_res_type);
}

int main(int argc, char **argv) {
  _init(&argc, &argv);
  _register_mpi_types();
  if (0 == rank) {
    _run_server();
  } else {
    _run_client();
  }
  _finit();
}
