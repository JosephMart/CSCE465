#!/usr/bin/env bash

# MD5 and SHA256:
# 1. Create a text file of any length.
# 2. Generate the hash value H1 for this file using a specific hash algorithm.
# 3. Flip one bit of the input file. You can achieve this modification using ghex.
# 4. Generate the hash value H2 for the modified file.
# 5. Please observe whether H1 and H2 are similar or not. Please describe your observations in the report. You can write a short program to count how many bits are the same between H1 and H2.


filename="plain.txt"

for dgsttype in -md5 -sha256; do
    openssl dgst $dgsttype $filename
done