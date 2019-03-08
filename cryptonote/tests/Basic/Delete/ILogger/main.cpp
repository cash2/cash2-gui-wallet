// Copyright (c) 2018 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "gtest/gtest.h"
#include "Logging/ILogger.h"

using namespace Logging;

// constructor
TEST(ILogger, 1)
{
  ILogger logger;
}


int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}