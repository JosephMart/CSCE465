#ifndef _utils_H_
#define _utils_H_

#include <array>
#include <string>
#include <stdio.h>
#include <openssl/evp.h>
#include <iostream>

#define MSG_LEN 30
#define REDUCE_HASH_LEN 3

class HashGen
{
private:
  const EVP_MD *md;

public:
  std::string msg;
  std::array<unsigned char, EVP_MAX_MD_SIZE> md_value;
  unsigned int md_len;

  HashGen(const EVP_MD *md);
  void gen_hash();
  std::string gen_msg();
  void gen_all();
  void print_msg();
  void print_digest();
  std::array<unsigned char, REDUCE_HASH_LEN> get_short_digest();
};

#endif