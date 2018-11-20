#!/usr/bin/env bash

# Create RSA Key
ssh-keygen -t rsa -b 1024

# Create AES key and save kye to file manually
openssl enc -aes-128-cbc -k secret -P -md sha1

# Run speed tests
openssl speed rsa
openssl speed aes
