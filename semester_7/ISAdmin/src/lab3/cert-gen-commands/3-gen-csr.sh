#!/bin/sh

openssl req \
	-subj "/C=XX/ST=Sevactopol/L=Sevastopol/O=SevSU/OU=SevSU/CN=StrangeCA" \
	-key root-ca.key \
	-new -out request.csr

