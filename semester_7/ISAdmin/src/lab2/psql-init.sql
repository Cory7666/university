CREATE USER zabbix WITH
    PASSWORD 'secretpass'
    CREATEDB
    LOGIN;

CREATE DATABASE zabbix WITH
    OWNER 'zabbix';
