// Copyright (c) 2018 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "InProcessNode/InProcessNode.h"
#include "CryptoNoteCore/Core.h"
#include "CryptoNoteCore/Currency.h"
#include "Logging/ConsoleLogger.h"
#include <gtest/gtest.h>
#include <iostream>
#include "helperFunctions.h"
#include "CryptoNoteCore/CoreConfig.h"
#include "CryptoNoteCore/MinerConfig.h"

/*

My Notes

class InProcessNode
public
  *InProcessNode()
  ~InProcessNode()
  *init()
  *shutdown()
  *addObserver()
  *removeObserver()
  *getPeerCount()
  *getLastLocalBlockHeight()
  *getLastKnownBlockHeight()
  *getLocalBlockCount()
  *getKnownBlockCount()
  *getLastLocalBlockTimestamp()
  getNewBlocks()
  getTransactionOutsGlobalIndexes()
  getRandomOutsByAmounts()
  relayTransaction()
  queryBlocks()
  getPoolSymmetricDifference()
  getMultisignatureOutputByGlobalIndex()
  getBlocks()
  getBlocks()
  getBlocks()
  getTransactions()
  getTransactionsByPaymentId()
  getPoolTransactions()
  isSynchronized()

*/

using namespace CryptoNote;

// Helper Functions

class CryptonoteProtocol : public i_cryptonote_protocol
{
public:
  void relay_block(NOTIFY_NEW_BLOCK_request& arg) override
  {
    std::cout << "relay block" << std::endl;
  }

  void relay_transactions(NOTIFY_NEW_TRANSACTIONS_request& arg) override
  {
    std::cout << "relay transactions" << std::endl;
  }
};

class CryptoNoteProtocolQuery : public ICryptoNoteProtocolQuery
{
public:
  virtual bool addObserver(ICryptoNoteProtocolObserver* observer) { return true; };
  virtual bool removeObserver(ICryptoNoteProtocolObserver* observer) { return true; };

  virtual uint32_t getObservedHeight() const { return 1; };
  virtual size_t getPeerCount() const { return 0; };
  virtual bool isSynchronized() const { return true; };
};

void printError(std::error_code ec)
{
  if(ec)
  {
    std::cout << ec.message() << std::endl;
  }
}

std::error_code returnError(std::error_code ec)
{
  return ec;
}

class NodeObserver : public INodeObserver
{
public:
  virtual ~NodeObserver() {}
  virtual void peerCountUpdated(size_t count) { printError(std::error_code()); };
  virtual void localBlockchainUpdated(uint32_t height) { printError(std::error_code()); };
  virtual void lastKnownBlockHeightUpdated(uint32_t height) { printError(std::error_code()); };
  virtual void poolChanged() { printError(std::error_code()); };
  virtual void blockchainSynchronized(uint32_t topHeight) { printError(std::error_code()); };
};

// Adds an empty block to the blockchain
bool addBlock1(core& core)
{
  uint32_t currentBlockchainHeight = core.get_current_blockchain_height();

  AccountPublicAddress accountPublicAddress;
  KeyPair viewKeyPair = generateKeyPair();
  KeyPair spendKeyPair = generateKeyPair();
  accountPublicAddress.viewPublicKey = viewKeyPair.publicKey;
  accountPublicAddress.spendPublicKey = spendKeyPair.publicKey;

  BinaryArray extraNonce;

  Block block;
  difficulty_type difficulty;
  uint32_t height;

  core.get_block_template(block, accountPublicAddress, difficulty, height, extraNonce);

  block.timestamp = time(nullptr) + (currentBlockchainHeight * parameters::DIFFICULTY_TARGET);

  bool blockAdded = core.handle_block_found(block);

  return blockAdded;
}

// Adds an empty block to the blockchain
// able to set timestamp
// finds nonce appropriate for difficulty
bool addBlock2(core& core, const uint64_t timestamp)
{
  AccountPublicAddress accountPublicAddress;
  KeyPair viewKeyPair = generateKeyPair();
  KeyPair spendKeyPair = generateKeyPair();
  accountPublicAddress.viewPublicKey = viewKeyPair.publicKey;
  accountPublicAddress.spendPublicKey = spendKeyPair.publicKey;

  BinaryArray extraNonce;

  Block block;
  difficulty_type difficulty;
  uint32_t height;

  core.get_block_template(block, accountPublicAddress, difficulty, height, extraNonce);

  block.timestamp = timestamp;

  // find nonce appropriate for difficulty
  Crypto::Hash proofOfWorkIgnore = NULL_HASH;
  Currency currency = core.currency();
  while(!currency.checkProofOfWork1(block, difficulty, proofOfWorkIgnore))
  {
    block.nonce++;
  }

  bool added = core.handle_block_found(block);

  return added;
}

// Adds an empty block to the blockchain
// returns the hash of the block added
bool addBlock3(core& core, Crypto::Hash& blockHash)
{
  uint32_t currentBlockchainHeight = core.get_current_blockchain_height();

  AccountPublicAddress accountPublicAddress;
  KeyPair viewKeyPair = generateKeyPair();
  KeyPair spendKeyPair = generateKeyPair();
  accountPublicAddress.viewPublicKey = viewKeyPair.publicKey;
  accountPublicAddress.spendPublicKey = spendKeyPair.publicKey;

  BinaryArray extraNonce;

  Block block;
  difficulty_type difficulty;
  uint32_t height;

  core.get_block_template(block, accountPublicAddress, difficulty, height, extraNonce);

  block.timestamp = time(nullptr) + (currentBlockchainHeight * parameters::DIFFICULTY_TARGET);

  blockHash = get_block_hash(block);

  bool added = core.handle_block_found(block);

  return added;
}

// constructor
TEST(InProcessNode, 1)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CryptoNoteProtocolQuery protocol;
  InProcessNode(core, protocol);
}

// init()
TEST(InProcessNode, 2)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);

  node.init(printError);
}

// shutdown()
TEST(InProcessNode, 3)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);

  node.init(printError);

  ASSERT_TRUE(node.shutdown());
}

// addObserver()
TEST(InProcessNode, 4)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);

  node.init(printError);

  NodeObserver nodeObserver;

  ASSERT_TRUE(node.addObserver(&nodeObserver));
}

// removeObserver()
TEST(InProcessNode, 5)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);

  node.init(printError);

  NodeObserver nodeObserver;

  ASSERT_TRUE(node.addObserver(&nodeObserver));

  ASSERT_TRUE(node.removeObserver(&nodeObserver));
}

// getPeerCount()
TEST(InProcessNode, 6)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);

  node.init(printError);

  size_t peerCount = node.getPeerCount();
  ASSERT_EQ(0, peerCount);
}

// getLastLocalBlockHeight()
TEST(InProcessNode, 7)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CoreConfig coreConfig;
  MinerConfig minerConfig;
  bool loadExisting = false;
  ASSERT_TRUE(core.init(coreConfig, minerConfig, loadExisting));

  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);
  node.init(printError);

  uint32_t height = node.getLastLocalBlockHeight();
  ASSERT_EQ(0, height);

  ASSERT_TRUE(addBlock1(core));
  ASSERT_TRUE(addBlock1(core));
  ASSERT_TRUE(addBlock1(core));

  ASSERT_EQ(3, node.getLastLocalBlockHeight());
}

// getLastKnownBlockHeight()
// "known" means accessing protocol
TEST(InProcessNode, 8)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);

  node.init(printError);

  uint32_t height = node.getLastKnownBlockHeight();
  ASSERT_EQ(0, height);
}

// getLocalBlockCount()
// "local" means accessing core
TEST(InProcessNode, 9)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CoreConfig coreConfig;
  MinerConfig minerConfig;
  bool loadExisting = false;
  ASSERT_TRUE(core.init(coreConfig, minerConfig, loadExisting));

  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);
  node.init(printError);

  uint32_t count = node.getLocalBlockCount();
  ASSERT_EQ(1, count);

  ASSERT_TRUE(addBlock1(core));
  ASSERT_TRUE(addBlock1(core));
  ASSERT_TRUE(addBlock1(core));

  ASSERT_EQ(4, node.getLocalBlockCount());
}

// getKnownBlockCount()
TEST(InProcessNode, 10)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);

  node.init(printError);

  uint32_t count = node.getKnownBlockCount();
  ASSERT_EQ(1, count);
}

// getLastLocalBlockTimestamp()
TEST(InProcessNode, 11)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CoreConfig coreConfig;
  MinerConfig minerConfig;
  bool loadExisting = false;
  ASSERT_TRUE(core.init(coreConfig, minerConfig, loadExisting));

  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);
  node.init(printError);

  uint64_t timestamp = time(nullptr);

  ASSERT_TRUE(addBlock2(core, timestamp));

  ASSERT_EQ(timestamp, node.getLastLocalBlockTimestamp());
}

// getNewBlocks()
TEST(InProcessNode, 12)
{
  Logging::ConsoleLogger logger;
  Currency currency = CurrencyBuilder(logger).currency();
  CryptonoteProtocol crpytonoteProtocol;
  core core(currency, &crpytonoteProtocol, logger);
  CoreConfig coreConfig;
  MinerConfig minerConfig;
  bool loadExisting = false;
  ASSERT_TRUE(core.init(coreConfig, minerConfig, loadExisting));

  CryptoNoteProtocolQuery protocol;
  InProcessNode node(core, protocol);
  node.init(printError);

  std::vector<Crypto::Hash> blockHashes;

  // add 5 blocks to core
  for (int i = 0; i < 5; i++)
  {
    Crypto::Hash blockHash;
    ASSERT_TRUE(addBlock3(core, blockHash));
    blockHashes.push_back(blockHash);
  }

  std::vector<Crypto::Hash> knownBlockIds; // leave vector empty
  std::vector<CryptoNote::block_complete_entry> newBlocks;
  uint32_t startHeight;
  node.getNewBlocks(std::move(knownBlockIds), newBlocks, startHeight, [&](std::error_code ec) {
    return ec;
  });

  
  
}































































int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}