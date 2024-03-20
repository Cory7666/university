#!/bin/sh

docker container rm `docker-compose ps -q`
docker network rm lab3_zabbixnet
