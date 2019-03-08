#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <bitset>
#include "crypto/blake2.h"
#include "Common/StringTools.h"
#include "CryptoNote.h"
#include "gtest/gtest.h"
#include "CryptoNoteCore/CryptoNoteTools.h"

bool blake2b32(CryptoNote::BinaryArray ba, Crypto::Hash& hash)
{
  size_t hashLength = 32;
  int result = blake2b(&hash, hashLength, ba.data(), ba.size(), nullptr, 0);

  if (result == -1)
  {
    return false;
  }

  return true;
}

bool hash_arbtx(std::string arbtx, Crypto::Hash& arbtx_hash_bin)
{
  // CryptoNote::BinaryArray arbtxBinaryArray;

  // // convert string to binary array
  // for (std::size_t i = 0; i < arbtx.size(); ++i)
  // {
    // uint8_t binaryAsInt = static_cast<uint8_t>(std::bitset<8>(arbtx[i]).to_ulong());
    // arbtxBinaryArray.push_back(binaryAsInt);
  // }

  
  // arbtxBinaryArray.insert(arbtxBinaryArray.begin(), 0);

  uint8_t data[121];

  // prepend byte with value of zero
  data[0] = 0;

  size_t sizeIgnore;

  Common::fromHex(arbtx, data + 1, 120, sizeIgnore);
  // Common::podFromHex(arbtx, data + 1);

  CryptoNote::BinaryArray ba(std::begin(data), std::end(data));

  // std::string toHex = Common::podToHex(data);

  


  // return true;

  return blake2b32(ba, arbtx_hash_bin);
}

// void build_merkle_root(const std::vector<std::string>& merkle_branch, const Crypto::Hash& arbtx_hash_bin, Crypto::Hash& merkle_root)
// {
  // merkle_root = arbtx_hash_bin;

  // for (std::size_t h = 0; h < merkle_branch.size(); h++)
  // {
    // // convert merkle branch string to a hash
    // Crypto::Hash merkleBranchHash;
    // size_t size = Common::fromHex(merkle_branch[h], merkleBranchHash.data, 32);

    // std::vector<uint8_t> combinedData = {1};

    // // prepend byte with value of zero
    // merkleBranchBinaryArray.insert(merkleBranchBinaryArray.begin(), 1);

    // merkle_root = blake2b32(merkleBranchBinaryArray + merkle_root);
  // }

  // // def build_merkle_root(merkle_branch, arbtx_hash_bin):
    // // merkle_root = arbtx_hash_bin
    // // for h in merkle_branch:
        // // merkle_root = blake2b32(b"\x01" + unhexlify(h) + merkle_root)
    // // return merkle_root
// }

TEST(Stratum, 1)
{
  // Block 86011
  // Hash 000000000000007384ca7ba61a988d14f9a9d731a981c186e8904f1e1d82e6f5

  std::string prevHashStr = "0000000000000079039da6f4d7790d54d774812f92e459387846524f4024afe3";
  
  std::cout << prevHashStr << std::endl;

  Crypto::Hash prevBlockHash;
  Common::fromHex(prevHashStr, prevBlockHash.data, 32);

  ASSERT_EQ(prevBlockHash.data[0], 0x00);
  ASSERT_EQ(prevBlockHash.data[1], 0x00);
  ASSERT_EQ(prevBlockHash.data[2], 0x00);
  ASSERT_EQ(prevBlockHash.data[3], 0x00);
  ASSERT_EQ(prevBlockHash.data[4], 0x00);
  ASSERT_EQ(prevBlockHash.data[5], 0x00);
  ASSERT_EQ(prevBlockHash.data[6], 0x00);
  ASSERT_EQ(prevBlockHash.data[7], 0x79);
  ASSERT_EQ(prevBlockHash.data[8], 0x03);
  ASSERT_EQ(prevBlockHash.data[9], 0x9d);
  ASSERT_EQ(prevBlockHash.data[10], 0xa6);
  ASSERT_EQ(prevBlockHash.data[11], 0xf4);
  ASSERT_EQ(prevBlockHash.data[12], 0xd7);
  ASSERT_EQ(prevBlockHash.data[13], 0x79);
  ASSERT_EQ(prevBlockHash.data[14], 0x0d);
  ASSERT_EQ(prevBlockHash.data[15], 0x54);
  ASSERT_EQ(prevBlockHash.data[16], 0xd7);
  ASSERT_EQ(prevBlockHash.data[17], 0x74);
  ASSERT_EQ(prevBlockHash.data[18], 0x81);
  ASSERT_EQ(prevBlockHash.data[19], 0x2f);
  ASSERT_EQ(prevBlockHash.data[20], 0x92);
  ASSERT_EQ(prevBlockHash.data[21], 0xe4);
  ASSERT_EQ(prevBlockHash.data[22], 0x59);
  ASSERT_EQ(prevBlockHash.data[23], 0x38);
  ASSERT_EQ(prevBlockHash.data[24], 0x78);
  ASSERT_EQ(prevBlockHash.data[25], 0x46);
  ASSERT_EQ(prevBlockHash.data[26], 0x52);
  ASSERT_EQ(prevBlockHash.data[27], 0x4f);
  ASSERT_EQ(prevBlockHash.data[28], 0x40);
  ASSERT_EQ(prevBlockHash.data[29], 0x24);
  ASSERT_EQ(prevBlockHash.data[30], 0xaf);
  ASSERT_EQ(prevBlockHash.data[31], 0xe3);

  std::string coinb1 = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000020000000000000004e6f6e536961000000000000000000006aba4dfb5df01095";
  std::string coinb2 = "0000000000000000";
  std::string merkle_branch[] =
  {
    "25cc1c464ed8f0a13da6c14098c2cd47526dcd64d3594a2ace794b9bc0ab704d",
    "2c162ebd012c0044cd34808a0dc9e5790f428cba73ce7b848a6f63ddd845c80e",
    "20283c26aa6cf99c126fe74021f2c5fb39baffd81814d725c57c883e16676c5d",
  };
  std::string ntime = "2ed1705800000000";
  std::string extranonce1 = "99cfbade";
  std::string extranonce2 = "ef7488b3";
  std::string nonce = "40371d049700e893";

  std::cout << "coinbase1\n" << coinb1 << "\n" << std::endl;
  std::cout << "extranonce1\n" << extranonce1 << "\n" << std::endl;
  std::cout << "extranonce2\n" << extranonce2 << "\n" << std::endl;
  std::cout << "coinbase2\n" << coinb2 << "\n" << std::endl;

  std::string arbtx = coinb1 + extranonce1 + extranonce2 + coinb2;

  std::cout << "arbtx\n" << arbtx << "\n" << std::endl;

  Crypto::Hash arbtx_hash_bin;
  hash_arbtx(arbtx, arbtx_hash_bin);

  // arbtx_hash_bin =
  // {
  //    0xd9, 0x95, 0x21, 0x9b, 0xcc, 0x23, 0x49, 0x7f, 0x6e, 0x7d,
  //    0x44, 0xdb, 0x94, 0xae, 0xb9, 0xe1, 0x54, 0x82, 0xd8, 0xc2,
  //    0x46, 0x60, 0x88, 0xc0, 0xbf, 0x7d, 0x4d, 0xed, 0x7, 0x92,
  //    0xef, 0x23
  //  }

  // goal hash = #d995219bcc23497f6e7d44db94aeb9e15482d8c2466088c0bf7d4ded0792ef23

  ASSERT_EQ(0xd9, arbtx_hash_bin.data[0]);
  ASSERT_EQ(0x95, arbtx_hash_bin.data[1]);
  ASSERT_EQ(0x21, arbtx_hash_bin.data[2]);
  ASSERT_EQ(0x9b, arbtx_hash_bin.data[3]);
  ASSERT_EQ(0xcc, arbtx_hash_bin.data[4]);
  ASSERT_EQ(0x23, arbtx_hash_bin.data[5]);
  ASSERT_EQ(0x49, arbtx_hash_bin.data[6]);
  ASSERT_EQ(0x7f, arbtx_hash_bin.data[7]);
  ASSERT_EQ(0x6e, arbtx_hash_bin.data[8]);
  ASSERT_EQ(0x7d, arbtx_hash_bin.data[9]);
  ASSERT_EQ(0x44, arbtx_hash_bin.data[10]);
  ASSERT_EQ(0xdb, arbtx_hash_bin.data[11]);
  ASSERT_EQ(0x94, arbtx_hash_bin.data[12]);
  ASSERT_EQ(0xae, arbtx_hash_bin.data[13]);
  ASSERT_EQ(0xb9, arbtx_hash_bin.data[14]);
  ASSERT_EQ(0xe1, arbtx_hash_bin.data[15]);
  ASSERT_EQ(0x54, arbtx_hash_bin.data[16]);
  ASSERT_EQ(0x82, arbtx_hash_bin.data[17]);
  ASSERT_EQ(0xd8, arbtx_hash_bin.data[18]);
  ASSERT_EQ(0xc2, arbtx_hash_bin.data[19]);
  ASSERT_EQ(0x46, arbtx_hash_bin.data[20]);
  ASSERT_EQ(0x60, arbtx_hash_bin.data[21]);
  ASSERT_EQ(0x88, arbtx_hash_bin.data[22]);
  ASSERT_EQ(0xc0, arbtx_hash_bin.data[23]);
  ASSERT_EQ(0xbf, arbtx_hash_bin.data[24]);
  ASSERT_EQ(0x7d, arbtx_hash_bin.data[25]);
  ASSERT_EQ(0x4d, arbtx_hash_bin.data[26]);
  ASSERT_EQ(0xed, arbtx_hash_bin.data[27]);
  ASSERT_EQ(0x07, arbtx_hash_bin.data[28]);
  ASSERT_EQ(0x92, arbtx_hash_bin.data[29]);
  ASSERT_EQ(0xef, arbtx_hash_bin.data[30]);
  ASSERT_EQ(0x23, arbtx_hash_bin.data[31]);

/*

  merkle_root_bin = build_merkle_root(merkle_branch, arbtx_hash_bin)

  print("merkle_root_bin\n%s\n" % merkle_root_bin.hex())

  merkle_root = hexlify(merkle_root_bin).decode("ascii")

  print("merkle_root\n%s\n" % merkle_root)

  header = prevhash + nonce + ntime + merkle_root

  print("prevhash\n%s" % prevhash)
  print("nonce\n%s" % nonce)
  print("ntime\n%s" % ntime)
  print("merkle_root\n%s" % merkle_root)
  print("header\n%s\n" % header)

  header_bin = unhexlify(header)

  print("header_bin\n%s\n" % header_bin.hex())

  block_header_hash = hexlify(blake2b32(header_bin)).decode("ascii")

  print("block_header_hash\n%s\n" % block_header_hash)

*/
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}