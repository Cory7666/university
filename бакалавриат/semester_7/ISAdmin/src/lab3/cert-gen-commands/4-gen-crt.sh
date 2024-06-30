#!/bin/sh

openssl x509 -req \
	-in request.csr \
	-CA root-ca.pem \
	-CAkey root-ca.key \
	-CAcreateserial \
	-out lnt.zabbix.crt \
	-days 365 \
	-sha256 \
	-extfile properties.ext
