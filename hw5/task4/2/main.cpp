#include <string.h>
#include <stdio.h>
#include <openssl/evp.h>
#include <map>
#include <array>

#include "hash_gen.hpp"

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    srand(time(NULL));

    OpenSSL_add_all_digests();

    const EVP_MD *md = EVP_get_digestbyname("md5");

    // run the loop
    HashGen h1(md);
    HashGen h2(md);
    int count = 0;

    h1.msg = "If at first you don't succeed,";
    h1.gen_hash();

    do
    {
        h2.gen_all();
        count += 1;
    } while (!(h1.get_short_digest() == h2.get_short_digest() && h1.msg != h2.msg));

    // print csv format (message 1,message 2,digest 1,digest 2,tries)
    std::cout << '\n';
    h1.print_msg();
    std::cout << ",";
    h2.print_msg();
    std::cout << ",";
    h1.print_digest();
    std::cout << ",";
    h2.print_digest();
    std::cout << ",";
    std::cout << count;

    EVP_cleanup();
    return 0;
}
