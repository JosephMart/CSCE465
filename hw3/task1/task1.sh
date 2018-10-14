#!/usr/bin/env bash

# key for decryption
KEY=00112233445566778889aabbccddeeff
# Initialization Vector
IV=0102030405060708
# Base output filename
OUT=cipher
# input filename
IN=plain.txt # You can't drown if you are always drowning

CIPHERS=(des aes-128 rc2)
MODES=(cbc cfb ecb)

encrypt() {
    local OUT_NAME=$OUT$ENC_TYPE.bin
    echo "Encrypt type: $ENC_TYPE"
    echo "Input file:   $IN"
    echo "Output file:  $OUT_NAME"
    openssl enc $ENC_TYPE -e -in $IN -out $OUT_NAME -K  $KEY -iv $IV
}

for c in "${CIPHERS[@]}"
do
    for m in "${MODES[@]}"
    do
        ENC_TYPE=-$c-$m
        encrypt
        echo ""
    done
done
