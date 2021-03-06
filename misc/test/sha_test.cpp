/**
 * $Id: sha_test.cpp 3 2013-05-20 13:07:23Z cota@upard.org $
 * Copyright (c) 2016 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include <iomanip>
#include <iostream>

using namespace std;

#include <SHA256.h>

using namespace cutil;

int main() {
  const char* key = "abc";

  SHA256 sha;
  sha.push(key, 3);

  unsigned char hash[32];
  sha.hash(hash);

  cout << "test1: " << endl;
  for (int i = 0; i < 32; ++i) {
    cout << std::hex << std::setw(2) << std::setfill('0')
         << static_cast<int>(hash[i]);
  }
  cout << endl << endl;

  SHA256::hash(hash, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
               56);

  cout << "test2: " << endl;
  for (int i = 0; i < 32; ++i) {
    cout << std::hex << std::setw(2) << std::setfill('0')
         << static_cast<int>(hash[i]);
  }
  cout << endl << endl;

  SHA256 sha2;
  for (int i = 0; i < 1000000; ++i) {
    sha2.push("a", 1);
  }
  sha2.hash(hash);

  cout << "test3: " << endl;
  for (int i = 0; i < 32; ++i) {
    cout << std::hex << std::setw(2) << std::setfill('0')
         << static_cast<int>(hash[i]);
  }
  cout << endl << endl;

  return 0;
}
