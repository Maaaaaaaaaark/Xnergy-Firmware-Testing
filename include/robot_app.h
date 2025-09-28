#pragma once
#include "protocol.h"
#include "session.h"


// 机器人工作状态 / Robot Operational State

typedef enum {
    ROBOT_IDLE = 0,         // 空闲状态 / Idle
    ROBOT_SCANNING,         // 正在扫描可用基站 / Scanning for available charging stations
    ROBOT_CONNECTING,       // 尝试连接 / Attempting to connect
    ROBOT_IN_SESSION,       // 正在通信会话中 / Actively exchanging messages (in session)
    ROBOT_ERROR             // 错误状态 / Error occurred
} robot_state_t;


// 机器人上下文结构体 / Robot Context Structure

typedef struct {
    robot_state_t state;               // 当前状态 / Current FSM state
    uint16_t robot_id;                // 机器人ID / Unique robot identifier
    session_t current_session;        // 当前会话结构 / Ongoing session information
    realtime_stats_t stats;           // 实时通信性能统计 / Real-time performance statistics
    uint8_t selected_station_id;      // 已选择的目标基站ID / Target station selected for connection

    uint32_t last_state_change_time;  // 状态切换时间戳（用于超时判断）/ Timestamp of last state change
    uint8_t retry_attempts;           // 重试计数 / Number of connection retries
    bool has_pending_request;         // 是否存在未完成请求 / Whether a charging request is pending
} robot_context_t;



// 机器人主要逻辑函数接口 / Robot Behavior Function Prototypes


// 发起充电请求（进入 SCANNING 状态）
// Initiates a charging request; robot starts scanning
void robot_charging_request(robot_context_t *ctx);

// 扫描基站（并等待响应），返回找到的基站数量或错误码
// Scans for available stations, waits for responses; returns count or error
int robot_scan_stations(robot_context_t *ctx, uint32_t timeout_ms);

// 向指定基站发起连接请求
// Attempts to connect to the selected charging station
int robot_connect_to_station(robot_context_t *ctx, uint16_t station_id);

// 在连接成功后，保持实时通信，维护 session 状态
// Handles message exchange, session monitoring and auto-recovery
void robot_maintain_session(robot_context_t *ctx);