#!/usr/bin/env bash

# key for decryption
KEY=00112233445566778889aabbccddeeff
# Initialization Vector
IV=0102030405060708
# Base output filename
OUT=pic_cipher
# input filename
IN=pic_original.bmp

encrypt() {
    local OUT_NAME=$OUT$ENC_TYPE.bmp
    echo "Encrypt type: $ENC_TYPE"
    echo "Input file:   $IN"
    echo "Output file:  $OUT_NAME"
    openssl enc $ENC_TYPE -e -in $IN -out $OUT_NAME -K  $KEY -iv $IV
}

ENC_TYPE=-des-cbc
encrypt
echo ""

ENC_TYPE=-des-ecb
encrypt

# BMP header (first 36 bytes)
# 42 4D 8E D2 02 00 00 00 00 00 36 00 00 00 28 00 00 00 CC 01 00 00 86 00 00 00 01 00 18 00 00 00 00 00 58 D2 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00