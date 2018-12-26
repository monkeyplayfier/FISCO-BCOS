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
 * @brief : common functions and types of Blocksync modules
 * @author: yujiechen
 * @date: 2018-09-21
 */

/**
 * @brief : common functions and types of Blocksync modules
 * @author: jimmyshi
 * @date: 2018-10-15
 */
#pragma once
#include <libnetwork/Common.h>
#include <libp2p/P2PMessage.h>

#include <libdevcore/Exceptions.h>
#include <libdevcore/FixedHash.h>
#include <libethcore/Block.h>


#include <set>

namespace dev
{
namespace sync
{
DEV_SIMPLE_EXCEPTION(SyncVerifyHandlerNotSet);

static unsigned const c_maxSendTransactions = 128;

// Every c_downloadingRequestTimeout request:
// c_maxRequestBlocks(each peer) * c_maxRequestShards(peer num) = blocks
static int64_t const c_maxRequestBlocks = 32;
static size_t const c_maxRequestShards = 4;
static uint64_t const c_downloadingRequestTimeout =
    c_maxRequestBlocks * 1000;  // ms: assume that we have 1s timeout for each block

static size_t const c_maxDownloadingBlockQueueSize =
    c_maxRequestBlocks * 128;  // maybe less than 128 is ok
static size_t const c_maxDownloadingBlockQueueBufferSize = c_maxRequestShards * 8;

static size_t const c_maxReceivedDownloadRequestPerPeer = 8;
static uint64_t const c_respondDownloadRequestTimeout = 200;  // ms

static unsigned const c_syncPacketIDBase = 1;
static size_t const c_maxPayload = dev::p2p::P2PMessage::MAX_LENGTH - 2048;

static uint64_t const c_maintainBlocksTimeout = 5000;  // ms

using NodeList = std::set<dev::p2p::NodeID>;
using NodeID = dev::p2p::NodeID;
using NodeIDs = std::vector<dev::p2p::NodeID>;
using BlockPtr = std::shared_ptr<dev::eth::Block>;
using BlockPtrVec = std::vector<BlockPtr>;

#define SYNCLOG(_OBV)                                               \
    LOG(_OBV) << " [#SYNC] [PROTOCOL: " << std::dec << m_protocolId \
              << "] [GROUP: " << std::to_string(m_groupId) << " ]"

enum SyncPacketType : byte
{
    StatusPacket = 0x00,
    TransactionsPacket = 0x01,
    BlocksPacket = 0x02,
    ReqBlocskPacket = 0x03,
    PacketCount
};

enum class SyncState
{
    Idle,         ///< Initial chain sync complete. Waiting for new packets
    Downloading,  ///< Downloading blocks
    Size          /// Must be kept last
};

struct SyncPeerInfo
{
    NodeID nodeId;
    int64_t number;
    h256 genesisHash;
    h256 latestHash;
};

}  // namespace sync
}  // namespace dev
