#!/usr/bin/env bash

in=example.txt
signature=example.sha256
pub_key=id_rsa.pub.pem
priv_key=id_rsa


printf "$in content\n\n"
cat $in

printf "\n\nSigning\n"
openssl dgst -sha256 -sign $priv_key -out $signature $in
openssl dgst -sha256 -verify $pub_key -signature $signature $in

printf "\nChange $in now\n"
read -n 1 -s -r -p "Press any key to continue"

printf "\n\n$in content\n\n"
cat $in


printf "\n\nVerifying signature\n"
openssl dgst -sha256 -verify $pub_key -signature $signature $in
