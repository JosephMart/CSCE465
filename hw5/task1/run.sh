#!/usr/bin/env bash

filename="plain.txt"

for dgsttype in -md5 -sha1 -sha256; do
    openssl dgst $dgsttype $filename
done