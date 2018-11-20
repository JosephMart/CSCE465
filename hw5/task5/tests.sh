#!/usr/bin/env bash

# Followed usage info from below
# http://krisjordan.com/essays/encrypting-with-rsa-key-pairs
# https://devops.datenkollektiv.de/using-aes-with-openssl-to-encrypt-files.html

in=message.txt
out=message_enc.txt


function enc_rsa {
    cat $in \
    | openssl rsautl \
        -encrypt \
        -pubin -inkey ./id_rsa.pub.pem \
    > $out
}

function dec_rsa {
    cat $out \
    | openssl rsautl \
        -decrypt \
        -inkey ./id_rsa \
    > data.txt
}

function enc_aes {
    openssl enc -nosalt -aes-128-cbc -in message.txt \
        -out $out -base64 \
        -K 3784EBEA881C1CA066017FD6754201E1 \
        -iv F9C4AFEE929E890167B872576CF52F5B
}

echo "Time for 1000 rsa encrypt"
time (for i in {1..1000}; do enc_rsa ; done)

echo "Time for 1000 rsa decrypt"
time (for i in {1..1000}; do dec_rsa ; done)

echo "Time for 1000 aes encrypt"
time (for i in {1..1000}; do enc_aes ; done)
