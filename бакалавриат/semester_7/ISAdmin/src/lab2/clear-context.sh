#!/bin/sh

docker container rm `docker-compose ps -q`
docker network rm lab2_zabbixnet
