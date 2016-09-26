// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2015 The Dogecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;

#include "chainparamsseeds.h"

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";

        consensus.nSubsidyHalvingInterval = 1051200;
        consensus.nMajorityEnforceBlockUpgrade = 1500;
        consensus.nMajorityRejectBlockOutdated = 1900;
        consensus.nMajorityWindow = 2000;
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 20;
        consensus.nPowTargetTimespan = 60;
        consensus.nPowTargetSpacing = 60; // 1 minute
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        consensus.fSimplifiedRewards = true;
        consensus.nAuxpowChainId = 0x0062; // 98 - Josh Wise!
        consensus.fStrictChainId = true;
        consensus.fAllowLegacyBlocks = true;
        consensus.fAllowAuxPow = false;
        consensus.nHeightEffective = 0;
        consensus.fDigishieldDifficultyCalculation = true;
        consensus.nCoinbaseMaturity = 240;

        pConsensusRoot = &consensus;

        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xb8;
        pchMessageStart[3] = 0x00;
        vAlertPubKey = ParseHex("04befb79296b7f7a6965f0cbf39b3ae8b81305eda02e01bdff2ed2a4b869fd10b30325e8cb2ddf703e91a0f7c2c1eb0be480ae9fec4cb35208d36efb47ff362e11");
        nDefaultPort = 11228;
        nMinerThreads = 0;
        nPruneAfterHeight = 100000;

        /**
         * Build the genesis block. Note that the output of its generation
         * transaction cannot be spent since it did not originally exist in the
         * database.
         *
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1386325540, nBits=0x1e0ffff0, nNonce=99943, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
        const char* pszTimestamp = "Very Berry Much Clone";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 18 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion.SetGenesisVersion(1);
        genesis.nTime    = 1474848000;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 197084;

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xcb8ba6bb6a44b5a5b911227d528b8eac2f1315a38955cc89f2a7d08d5cb7a536"));
        assert(genesis.hashMerkleRoot == uint256S("0x59c81fc2fd59c7afb553c5fbdc6e27438ad138a907be876c9ff7113c5f9d026b"));

        vSeeds.push_back(CDNSSeedData("berry-coin.com", "seed.berry-coin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,26);  // 0x1e
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);  // 0x16
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,159); // 0x9e
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xfb)(0xcb)(0xfe).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0xfb)(0xc4)(0x99).convert_to_container<std::vector<unsigned char> >();

        //TODO: fix this for berrycoin -- plddr
        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        vFixedSeeds.clear();

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0xcb8ba6bb6a44b5a5b911227d528b8eac2f1315a38955cc89f2a7d08d5cb7a536")),
            0, // * UNIX timestamp of last checkpoint block
            0,   // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0     // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";

        consensus.nPowTargetTimespan = 60;
        consensus.fDigishieldDifficultyCalculation = true;
        consensus.fSimplifiedRewards = true;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.nCoinbaseMaturity = 240;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        consensus.nMajorityEnforceBlockUpgrade = 501;
        consensus.nMajorityRejectBlockOutdated = 750;
        consensus.nMajorityWindow = 1000;
        consensus.fStrictChainId = false;
        consensus.nHeightEffective = 0;
        consensus.fAllowLegacyBlocks = true;
        consensus.fAllowAuxPow = false;

        // Reset links before we copy parameters
        pConsensusRoot = &consensus;
        consensus.pLeft = NULL;
        consensus.pRight = NULL;

        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[2] = 0x00;
        vAlertPubKey = ParseHex("04befb79296b7f7a6965f0cbf39b3ae8b81305eda02e01bdff2ed2a4b869fd10b30325e8cb2ddf703e91a0f7c2c1eb0be480ae9fec4cb35208d36efb47ff362e11");
        nDefaultPort = 22278;
        nMinerThreads = 0;
        nPruneAfterHeight = 1000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1474851600;
        genesis.nNonce = 2608733;
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x8c7204a17cd798bbf528faeeeb1124d9997783706f57690a9f340d9091ef0c2a"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("berry-coin.com", "test-seed.berry-coin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,114); // 0x71
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,197); // 0xc4
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,242); // 0xf1
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x36)(0x88)(0xd0).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x36)(0x84)(0x95).convert_to_container<std::vector<unsigned char> >();

        //TODO: fix this for berrycoin -- plddr
        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x8c7204a17cd798bbf528faeeeb1124d9997783706f57690a9f340d9091ef0c2a")),
            0, // * UNIX timestamp of last checkpoint block
            0,    // * total number of transactions between genesis and last checkpoint
            0        // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.nPowTargetTimespan = 60;
        consensus.nPowTargetSpacing = 1; // regtest: 1 second blocks
        consensus.powLimit = uint256S("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint256(0) >> 1;
        consensus.fStrictChainId = true;
        consensus.fAllowLegacyBlocks = true;
        consensus.fAllowAuxPow = false;
        consensus.fSimplifiedRewards = true;
        consensus.fDigishieldDifficultyCalculation = true;
        consensus.nCoinbaseMaturity = 60; // For easier testability in RPC tests

        // Reset links before we copy parameters
        pConsensusRoot = &consensus;
        consensus.pLeft = NULL;
        consensus.pRight = NULL;

        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0x00;
        nMinerThreads = 1;
        genesis.nTime = 1474855200;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 4421;
        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 9222;
        assert(consensus.hashGenesisBlock == uint256S("0xe9aba1002c31e67f83e355c76f043ee5141f26dc1052f5d62760d40ed8eb6bc6"));
        nPruneAfterHeight = 1000;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0xe9aba1002c31e67f83e355c76f043ee5141f26dc1052f5d62760d40ed8eb6bc6")),
            0,
            0,
            0
        };
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
