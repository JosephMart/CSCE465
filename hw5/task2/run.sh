#!/usr/bin/env bash

filename="plain.txt"

for keyLen in 3 15 21 32; do
    key=$(openssl rand -base64 $keyLen)
    echo "key: $key"
    for dgsttype in -md5 -sha1 -sha256; do
        openssl dgst $dgsttype -hmac $key $filename
    done
    echo ''
done