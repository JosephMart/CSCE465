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
    HashGen hg(md);
    std::map<std::array<unsigned char, REDUCE_HASH_LEN>, std::string> msg_digest_map; // key: digest, val: msg
    bool collision = false;
    std::map<std::array<unsigned char, REDUCE_HASH_LEN>, std::string>::iterator it;
    int count = 0;

    do
    {
        hg.gen_all();
        count += 1;
        it = msg_digest_map.find(std::array<unsigned char, REDUCE_HASH_LEN>(hg.get_short_digest()));

        if (it != msg_digest_map.end() && it->second != hg.msg)
            collision = true;
        else
            msg_digest_map[hg.get_short_digest()] = hg.msg;

    } while (!collision);

    // print csv format (message 1,message 2,digest 1,digest 2,tries)
    std::cout << '\n';
    hg.print_msg();
    std::cout << "," << it->second << ",";
    hg.print_digest();
    std::cout << ",";
    hg.msg = it->second;
    hg.gen_hash();
    hg.print_digest();
    std::cout << ",";
    std::cout << count;

    EVP_cleanup();
    return 0;
}
