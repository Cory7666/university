#!/bin/sh

openssl req -x509 \
	-key root-ca.key \
	-out root-ca.pem \
	-sha256 \
	-days 365 \
	-nodes \
	-subj "/C=XX/ST=Sevactopol/L=Sevastopol/O=SevSU/OU=SevSU/CN=StrangeCA"
