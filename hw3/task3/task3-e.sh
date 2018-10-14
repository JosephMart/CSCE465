#!/usr/bin/env bash

# key for decryption
KEY=00112233445566778889aabbccddeeff
# Initialization Vector
IV=0102030405060708
# Base output filename
OUT=cipher
# input filename
IN=plain.txt

MODES=(ecb cbc cfb ofb)

encrypt() {
    local OUT_NAME=$OUT$ENC_TYPE.bin
    echo "Encrypt type: $ENC_TYPE"
    echo "Input file:   $IN"
    echo "Output file:  $OUT_NAME"
    openssl enc $ENC_TYPE -e -in $IN -out $OUT_NAME -K  $KEY -iv $IV
}


for m in "${MODES[@]}"
do
    ENC_TYPE=-aes-128-$m
    encrypt
    echo ""
done

# -aes128
# encrypt
# echo ""
# decrypt