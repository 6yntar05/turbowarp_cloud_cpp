#!/bin/sh

openssl req -newkey rsa:4096 \
            -x509 \
            -sha256 \
            -days 3650 \
            -nodes \
            -out cert \
            -keyout privkey \
            -subj "/C=RU/L=Tomsk/O=TUSUR/CN=127.0.0.1"
