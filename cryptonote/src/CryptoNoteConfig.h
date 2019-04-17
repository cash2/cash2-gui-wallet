// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <initializer_list>

namespace CryptoNote {
namespace parameters {

const uint64_t DIFFICULTY_TARGET                             = 9; // seconds

const uint64_t CRYPTONOTE_MAX_BLOCK_NUMBER                   = 500000000;
const size_t   CRYPTONOTE_MAX_BLOCK_BLOB_SIZE                = 500000000;
const size_t   CRYPTONOTE_MAX_TX_SIZE                        = 1000000000;
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX       = 0x6; // all Cash2 addresses start with a '2' 
const size_t   CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW          = 60;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT            = 60 * 60 * 2;
const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW             = 60;
const uint64_t MONEY_SUPPLY                                  = UINT64_C(15000000000000000); // 15,000,000.000000000 total coins
const unsigned EMISSION_SPEED_FACTOR                         = 24;

static_assert(EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");

const size_t   CRYPTONOTE_REWARD_BLOCKS_WINDOW               = 60 * 24 * 60 * 60 / DIFFICULTY_TARGET; // number of blocks produced in 60 days
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE     = 200 * 1024; //size of block (bytes) after which reward for block calculated using block size, 200 kb
const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE        = 600;
const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT              = 9; // number of digits after decimal point

const uint64_t MINIMUM_FEE_1                                 = 0; // free transactions
const uint64_t MINIMUM_FEE_2                                 = UINT64_C(10000000); // 0.01
const uint64_t MINIMUM_FEE                                   = MINIMUM_FEE_2;

const uint64_t DEFAULT_DUST_THRESHOLD_1                      = MINIMUM_FEE_1;
const uint64_t DEFAULT_DUST_THRESHOLD_2                      = MINIMUM_FEE_2;
const uint64_t DEFAULT_DUST_THRESHOLD                        = DEFAULT_DUST_THRESHOLD_2;

const uint64_t MAX_MIXIN                                     = 3;
const size_t   DIFFICULTY_WINDOW                             = 3600; // blocks, number of blocks expected in 9 hours
const size_t   DIFFICULTY_CUT                                = 60;  // timestamps to cut after sorting
const size_t   DIFFICULTY_LAG                                = 15;

static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

const size_t   MAX_BLOCK_SIZE_INITIAL                        = 400 * 1024; // 400 kb
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;
const uint64_t MAX_TX_EXTRA_SIZE                             = 256;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;
const uint64_t CRYPTONOTE_MEMPOOL_TX_LIVETIME                = 60 * 60; //seconds, 1 hour
const uint64_t CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = 60 * 60; //seconds, 1 hour
const uint64_t CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 1;  // CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL * CRYPTONOTE_MEMPOOL_TX_LIVETIME = time to forget tx
const size_t   FUSION_TX_MAX_SIZE                            = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE * 30 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;
const char     CRYPTONOTE_BLOCKS_FILENAME[]                  = "blocks.dat";
const char     CRYPTONOTE_BLOCKINDEXES_FILENAME[]            = "blockindexes.dat";
const char     CRYPTONOTE_BLOCKSCACHE_FILENAME[]             = "blockscache.dat";
const char     CRYPTONOTE_POOLDATA_FILENAME[]                = "poolstate.bin";
const char     P2P_NET_DATA_FILENAME[]                       = "p2pstate.bin";
const char     CRYPTONOTE_BLOCKCHAIN_INDEXES_FILENAME[]      = "blockchainindexes.dat";
const char     MINER_CONFIG_FILE_NAME[]                      = "miner_conf.json";

// HARD_FORK_HEIGHT_1 was originally set to height 230,500 but was later removed from the code because
// all blocks prior to height 230,500 followed the new consensus rules implemented
// Therefore, a hard fork did not really occur at height 230,500
// const uint64_t HARD_FORK_HEIGHT_1                            = 230500;

const uint64_t HARD_FORK_HEIGHT_2                            = 420016;
const uint64_t SOFT_FORK_HEIGHT_1                            = 1100000;

} // end namespace parameters

const char     CRYPTONOTE_NAME[]                             = "cash2";
const char     GENESIS_COINBASE_TX_HEX[]                     = "013c01ff0001a7d7a9aa03028037deeee59fb526b6474696bd4246c21b2e7dbd4fc17a02a6037ca6835e3a4f2101f6632c8a6d6102c85597eaccb5c0be3880b7220aee0d0e4c5b852d8757f5b67f";
const uint8_t  CURRENT_TRANSACTION_VERSION                   = 1;
const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT        = 10000;  //by default, blocks ids count in synchronizing
const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            = 20;    //by default, blocks count in blocks downloading
const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT         = 1000;
const int      P2P_DEFAULT_PORT                              = 12275;
const int      RPC_DEFAULT_PORT                              = 12276;
const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT                = 1000;
const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT                 = 5000;
const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE          = 16 * 1024 * 1024; // 16 MB
const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT                 = 8;
const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT     = 70;
const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL                = 60;            // seconds
const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE                   = 50000000;      // 50000000 bytes maximum packet size
const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE                = 250;
const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT                = 5000;          // 5 seconds
const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT           = 2000;          // 2 seconds
const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT                    = 60 * 2 * 1000; // 2 minutes
const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT          = 5000;          // 5 seconds
const char     P2P_STAT_TRUSTED_PUB_KEY[]                    = "";

//seed nodes
const std::initializer_list<const char*> SEED_NODES = {
  "seed1.cash2.org:12277",
  "seed2.cash2.org:12279",
  "seed3.cash2.org:12275",
};

struct CheckpointData {
  uint32_t height;
  const char* blockId;
};

#ifdef __GNUC__
__attribute__((unused))
#endif

const std::initializer_list<CheckpointData> CHECKPOINTS = {};

} // end namespace CryptoNote

#define ALLOW_DEBUG_COMMANDS
