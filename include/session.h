#pragma once
#include <stdint.h>
#include "protocol.h"


// 会话状态枚举 / Session State Enum

typedef enum {
    SESSION_IDLE = 0,        // 空闲状态 / Idle (no session)
    SESSION_HANDSHAKE,       // 握手中 / Performing handshake
    SESSION_ACTIVE,          // 会话激活中 / Active session (real-time exchange ongoing)
    SESSION_ENDING           // 正在结束 / Terminating session
} session_state_t;


// 会话状态结构体 / Session Control Structure
typedef struct {
    session_state_t state;           // 当前会话状态 / Current session state
    uint16_t partner_id;            // 会话对端 ID / Communication partner ID
    uint32_t session_start_time;    // 会话开始时间（毫秒）/ Session start time (ms)
    uint32_t last_msg_time;         // 最后一次收到消息时间 / Timestamp of last received message
    uint16_t expected_seq_num;      // 期望收到的序列号 / Expected message sequence number
    uint8_t retry_count;            // 当前重试次数 / Retry attempt counter
    uint8_t session_id;             // 会话编号（用于确认握手）/ Session ID for handshake confirmation
    bool is_initiator;              // 是否由本端发起（机器人）/ True if robot initiated the session

    uint8_t assigned_gts_slot;      // 分配的 GTS 槽位编号 / Assigned Guaranteed Time Slot (GTS)
    uint8_t gts_count;              // 使用的 GTS 槽数量 / Number of GTS slots used
    uint8_t rf_channel;             // 当前使用的 RF 信道 / Assigned RF channel for this session
    int8_t tx_power_dbm;            // 发射功率（单位 dBm）/ Transmission power in dBm
} session_t;


// 实时通信性能统计结构 / Real-time Communication Statistics

typedef struct {
    uint32_t avg_interval;        // 平均收包间隔（ms）/ Average interval between messages (ms)
    uint32_t max_interval;        // 最大收包间隔（ms）/ Maximum observed interval (ms)
    uint32_t missed_count;        // 丢包计数 / Number of missed messages
} realtime_stats_t;


// 会话接口函数 / Session Interface APIs


// 初始化会话结构体（分配ID、设置初始状态）
// Initialize a session object with default state and partner info
void session_init(session_t *s, uint16_t partner_id, bool is_initiator);

// 处理握手阶段的消息（更新状态、记录会话信息）
// Handle handshake message and update session state
void session_handle_handshake(session_t *s, const message_t *msg);

// 处理实时数据消息，更新统计信息
// Handle real-time message and update performance statistics
void session_handle_realtime(session_t *s, const message_t *msg, realtime_stats_t *stats);

// 周期性更新会话状态（如检测超时、状态转换）
// Periodic session update (used for timeout detection or state transitions)
void session_update(session_t *s, uint32_t current_time);

// 判断当前会话是否需要重发消息
// Check whether message retransmission is required
bool session_need_retry(const session_t *s, uint32_t current_time);

// 清空并重置会话状态（如断开后重连）
// Reset session to initial state (e.g., after disconnection)
void session_reset(session_t *s);