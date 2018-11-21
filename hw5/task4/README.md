# Task 4

## Setup openssl api

```shell
brew install openssl
cd /usr/local/include
ln -s ../opt/openssl/include/openssl .
```

## Compile

```shell
cc main.c -lssl -lcrypto -o task4
```
