#include "header.hpp"

using namespace std;

int main (int argc, char **argv)
{
    l::Graph g{"table-11.dat"};
    int from = 0, to = 8;
    l::length nearest_way_dp = l::NO_WAY,
              nearest_way_dijkstra = l::NO_WAY;
    timespec t_start, t_stop,
             t_diff_dp, t_diff_dijkstra;

    /* Измерение скорости работы алгоритма динамического программирования */
    clock_gettime (CLOCK_REALTIME, &t_start);
    nearest_way_dp = g(from, to);
    clock_gettime (CLOCK_REALTIME, &t_stop);
    t_diff_dp.tv_nsec = t_stop.tv_nsec - t_start.tv_nsec;

    /* Измерение скорости работы алгоритма Дейкстры */
    clock_gettime (CLOCK_REALTIME, &t_start);
    nearest_way_dijkstra = g.getShortestWayByDijkstraAlgorithm (from, to);
    clock_gettime (CLOCK_REALTIME, &t_stop);
    t_diff_dijkstra.tv_nsec = t_stop.tv_nsec - t_start.tv_nsec;

    /* Вывод результатов */
    cout << "|                   | ДинамПрогр | Дейкстр |" << endl
         << "| Длина кратч пути  |" << setw(12) << nearest_way_dp <<    "|" << setw(9) << nearest_way_dijkstra <<    "|" << endl
         << "| Затрач время, нс  |" << setw(12) << t_diff_dp.tv_nsec << "|" << setw(9) << t_diff_dijkstra.tv_nsec << "|" << endl;

    return 0; 
}
