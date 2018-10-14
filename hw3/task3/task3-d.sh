#!/usr/bin/env bash

# key for decryption
KEY=00112233445566778889aabbccddeeff
# Initialization Vector
IV=0102030405060708
# Base output filename
OUT=cipher

MODES=(ecb cbc cfb ofb)

decrypt() {
    local IN_NAME=$OUT$ENC_TYPE.bin
    local OUT_NAME=$OUT$ENC_TYPE.txt
    echo "Encrypt type: $ENC_TYPE"
    echo "Input file:   $IN_NAME"
    echo "Output file:  $OUT_NAME"
    openssl enc $ENC_TYPE -d -in $IN_NAME -out $OUT_NAME -K  $KEY -iv $IV
}

ENC_TYPE=-aes128
decrypt
echo ""

for m in "${MODES[@]}"
do
    ENC_TYPE=-aes-128-$m
    decrypt
    echo ""
done
