// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "crypto/crypto.cpp"

#include "crypto-tests.h"

bool check_scalar(const Crypto::SecretKey &secretKey) {
  return Crypto::sc_check(reinterpret_cast<const unsigned char*>(&secretKey)) == 0;
}