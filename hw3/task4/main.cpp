#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <string>

static const unsigned char *plaintext = reinterpret_cast<const unsigned char *>("This is a top secret.");
static constexpr auto ciphertext = std::array<const unsigned char, 32>{
    0x8d, 0x20, 0xe5, 0x05, 0x6a, 0x8d, 0x24, 0xd0,
    0x46, 0x2c, 0xe7, 0x4e, 0x49, 0x04, 0xc1, 0xb5,
    0x13, 0xe1, 0x0d, 0x1d, 0xf4, 0xa2, 0xef, 0x2a,
    0xd4, 0x54, 0x0f, 0xae, 0x1c, 0xa0, 0xaa, 0xf9};
static constexpr auto iv = std::array<const unsigned char, 16>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main(int argc, char **argv)
{
    const int lenPlaintxt = std::strlen(reinterpret_cast<const char *>(plaintext));
    const EVP_CIPHER *cipher = EVP_aes_128_cbc();
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (!ctx)
        return 1;

    auto words = std::fstream("words.txt");
    std::string w;
    while (std::getline(words, w))
    {
        if (w.length() < 16)
        {
            int len = 0;
            unsigned char new_ciphertext[32];

            // Get length of the words
            w.append(16 - w.length(), ' ');

            // Encrypt
            auto key = reinterpret_cast<const unsigned char *>(w.c_str());
            if (EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv.data()) != 1)
                return 1;
            if (EVP_EncryptUpdate(ctx, new_ciphertext, &len, plaintext, lenPlaintxt) != 1)
                return 1;
            if (EVP_EncryptFinal_ex(ctx, new_ciphertext + len, &len) != 1)
                return 1;

            // Compare the ciphertexts
            if (std::strncmp(reinterpret_cast<const char *>(ciphertext.data()),
                             reinterpret_cast<const char *>(new_ciphertext),
                             32) == 0)
            {
                std::cout << "Key: " << w << '\n';
                break;
            }

            EVP_CIPHER_CTX_init(ctx);
        }
    }
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}