/*
 * @CopyRight:
 * FISCO-BCOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FISCO-BCOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>
 * (c) 2016-2018 fisco-dev contributors.
 */

/**
 * @brief : concrete implementation of LedgerParamInterface
 * @file : LedgerParam.h
 * @author: yujiechen
 * @date: 2018-10-23
 */
#pragma once
#include "LedgerParamInterface.h"
#include <libdevcore/FixedHash.h>
#include <memory>
#include <vector>

namespace dev
{
namespace ledger
{
/// forward class declaration
#define SYNC_TX_POOL_SIZE_DEFAULT 102400
struct TxPoolParam
{
    uint64_t txPoolLimit = SYNC_TX_POOL_SIZE_DEFAULT;
};
struct ConsensusParam
{
    std::string consensusType;
    dev::h512s sealerList = dev::h512s();
    dev::h512s observerList = dev::h512s();
    uint64_t maxTransactions;
    uint8_t maxTTL;
    /// unsigned intervalBlockTime;
    uint64_t minElectTime;
    uint64_t maxElectTime;
};

struct AMDBParam
{
    std::string topic;
    int retryInterval = 1;
    int maxRetry = 0;
};

#define SYNC_IDLE_WAIT_DEFAULT 200
struct SyncParam
{
    /// TODO: syncParam related
    unsigned idleWaitMs = SYNC_IDLE_WAIT_DEFAULT;
};

struct GenesisParam
{
    std::string genesisMark;
    std::string nodeListMark;
};
struct StorageParam
{
    std::string type;
    std::string path;
};
struct StateParam
{
    std::string type;
};
struct TxParam
{
    uint64_t txGasLimit;
};
class LedgerParam : public LedgerParamInterface
{
public:
    TxPoolParam& mutableTxPoolParam() override { return m_txPoolParam; }
    ConsensusParam& mutableConsensusParam() override { return m_consensusParam; }
    SyncParam& mutableSyncParam() override { return m_syncParam; }
    GenesisParam& mutableGenesisParam() override { return m_genesisParam; }
    AMDBParam& mutableAMDBParam() override { return m_amdbParam; }
    std::string const& baseDir() const override { return m_baseDir; }
    void setBaseDir(std::string const& baseDir) override { m_baseDir = baseDir; }
    StorageParam& mutableStorageParam() override { return m_storageParam; }
    StateParam& mutableStateParam() override { return m_stateParam; }
    TxParam& mutableTxParam() override { return m_txParam; }

private:
    TxPoolParam m_txPoolParam;
    ConsensusParam m_consensusParam;
    SyncParam m_syncParam;
    GenesisParam m_genesisParam;
    AMDBParam m_amdbParam;
    std::string m_baseDir;
    StorageParam m_storageParam;
    StateParam m_stateParam;
    TxParam m_txParam;
};
}  // namespace ledger
}  // namespace dev
