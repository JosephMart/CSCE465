#include "hash_gen.hpp"

HashGen::HashGen(const EVP_MD *md) : md(md){};

void HashGen::gen_hash()
{
    if (this->msg.empty())
        this->msg = this->gen_msg();

    EVP_MD_CTX *mdctx;
    mdctx = EVP_MD_CTX_create();

    EVP_DigestInit_ex(mdctx, this->md, NULL);
    EVP_DigestUpdate(mdctx, this->msg.c_str(), this->msg.length());
    EVP_DigestFinal_ex(mdctx, this->md_value.data(), &this->md_len);
    EVP_MD_CTX_destroy(mdctx);
}

std::string HashGen::gen_msg()
{
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(MSG_LEN, 0);
    std::generate_n(str.begin(), MSG_LEN, randchar);
    return str;
}

void HashGen::gen_all()
{
    this->msg = this->gen_msg();
    this->gen_hash();
}

void HashGen::print_msg()
{
    for (size_t i = 0; i < MSG_LEN; i++)
        std::cout << this->msg[i];
}

void HashGen::print_digest()
{
    for (auto i : this->md_value)
        printf("%02x", i);
}

std::array<unsigned char, REDUCE_HASH_LEN> HashGen::get_short_digest()
{
    std::array<unsigned char, REDUCE_HASH_LEN> t;

    for (size_t i = 0; i < REDUCE_HASH_LEN; i++)
        t[i] = this->md_value[i];
    return t;
}
