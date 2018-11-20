#!/usr/bin/env python3

MD5_H1 = "700a2be0783cbaebbc42fd95a1ab0b93daafbce6"
MD5_H2 = "1d0ffcb4e2bc7f932f9db5553bc0cb54"

SHA256_H1 = "980717c03ccf8446736c0b89ecbcf2249f0ee20276c59a58a9c8509e2d3170fe"
SHA256_H2 = "151b2fd33149c7c19f3e1c81c654ea899f7873d6315b4bed53bef3de22e60f33"


def main():
    print(
        f"For MD5 {bit_string_diff(MD5_H1, MD5_H2)} bits are the same\n"
        f"For SHA256 {bit_string_diff(SHA256_H1, SHA256_H2)} bits are the same"
    )


def string2bits(s=''):
    return "".join([bin(ord(x))[2:].zfill(8) for x in s])


def bit_string_diff(h1: str, h2: str) -> str:
    count = i = 0
    h1_bits = string2bits(h1)
    h2_bits = string2bits(h2)

    while i < len(h1_bits) and i < len(h2_bits):
        if h1_bits[i] == h2_bits[i]:
            count += 1
        i += 1
    return f"{count} of H1-{len(h1_bits)}/H2-{len(h2_bits)}"


if __name__ == "__main__":
    main()
