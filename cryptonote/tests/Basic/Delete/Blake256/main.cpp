// Copyright (c) 2018 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "gtest/gtest.h"
#include "Crypto/blake256.c"
#include <x86intrin.h>

// SKIP FOR NOW

/*

My Notes

blake256_init()
blake224_init()
blake256_update()
blake224_update()
blake256_final()
blake224_final()
blake256_hash()
blake224_hash()
hmac_blake256_init()
hmac_blake224_init()
hmac_blake256_update()
hmac_blake224_update()
hmac_blake256_final()
hmac_blake224_final()
hmac_blake256_hash()
hmac_blake224_hash()

*/

// blake256_init()
TEST(blake256, 1)
{
  state st;
  ASSERT_NO_THROW(blake256_init(&st));

  // s
  for (int i = 0; i < 4; i++)
  {
    ASSERT_EQ(0, st.s[i]);
  }

  // t
  for (int i = 0; i < 2; i++)
  {
    ASSERT_EQ(0, st.t[i]);
  }

  ASSERT_EQ(0, st.buflen);
  ASSERT_EQ(0, st.nullt);
}

// blake224_init()
TEST(blake256, 2)
{
  state st;
  ASSERT_NO_THROW(blake224_init(&st));

  // s
  for (int i = 0; i < 4; i++)
  {
    ASSERT_EQ(0, st.s[i]);
  }

  // t
  for (int i = 0; i < 2; i++)
  {
    ASSERT_EQ(0, st.t[i]);
  }

  ASSERT_EQ(0, st.buflen);
  ASSERT_EQ(0, st.nullt);
}

// blake256_update()
TEST(blake256, 3)
{
  state st;
  const uint8_t data32 = 1;
  uint64_t data64 = 1;
  ASSERT_NO_THROW(blake256_update(&st, &data32, data64));
}

// blake224_update()
TEST(blake256, 4)
{
  state st;
  const uint8_t data32 = 1;
  uint64_t data64 = 1;
  ASSERT_NO_THROW(blake224_update(&st, &data32, data64));
}

// // blake256_final()
// TEST(blake256, 5)
// {
  // state st;
  // uint8_t data32 = 1;
  // ASSERT_NO_THROW(blake256_final(&st, &data32));
// }

// // blake224_final()
// TEST(blake224, 6)
// {
  // state st;
  // uint8_t data32 = 1;
  // ASSERT_NO_THROW(blake224_final(&st, &data32));
// }
























































































int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}