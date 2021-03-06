/**
 * $Id: rsa_test.cpp 3 2013-05-20 13:07:23Z cota@upard.org $
 * Copyright (c) 2016 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#include <iomanip>
#include <iostream>

using namespace std;

#include <RSACipher.h>

using namespace cutil;

int main() {
  intX_t n, e, d;

  //  RSAKey::generate(&n, &e, &d, 256);
    RSAKey::generate( &n, &e, &d, 1024 );

  cout << "n : " << std::dec << n << endl;
  cout << "e : " << std::dec << e << endl;
  cout << "d : " << std::dec << d << endl;

  //  intX_t M("0xfedcba98765432100123456789abcdef");
  intX_t M("0xfedcba98");
  cout << "M : " << std::hex << M << endl;

  intX_t C = RSACipher::encrypt(M, RSAKey(n, e));
  cout << "C : " << std::hex << C << endl;

  M = RSACipher::decrypt(C, RSAKey(n, d));
  cout << "M : " << std::hex << M << endl;

  C = RSACipher::encrypt(M, RSAKey(n, d));
  cout << "C : " << std::hex << C << endl;

  M = RSACipher::decrypt(C, RSAKey(n, e));
  cout << "M : " << std::hex << M << endl;

  return 0;
}
