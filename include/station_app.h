#pragma once
#include "protocol.h"
#include "session.h"


// 充电站上下文结构 / Charging Station Context Structure

typedef struct {
    uint16_t station_id;              // 当前站点 ID / Station identifier
    station_status_t status;         // 当前状态（空闲 / 占用）/ Current status: free or occupied
    session_t current_session;       // 当前通信会话信息 / Ongoing session details
    uint8_t rf_channel;              // 当前使用的无线信道编号 / Operating RF channel

    uint32_t last_session_end_time;  // 上一次会话结束的时间戳 / Timestamp of last completed session
    uint8_t scan_rssi_threshold;     // 接收信号强度门限（屏蔽弱信号）/ RSSI threshold for rejecting weak signals
    bool auto_reject_busy;           // 当前繁忙时是否自动拒绝连接 / Whether to auto-reject connections when busy
} station_context_t;


// 基站功能接口 / Station Behavior Function Prototypes


// 为多个基站分配唯一信道以避免干扰
// Assigns unique RF channels to multiple stations to prevent collision
void station_select_unique_channel(station_context_t *stations, uint8_t count);

// 处理机器人发来的扫描请求
// Handles scan requests received from robot clients
int station_handle_scan_request(station_context_t *ctx, const message_t *req);

// 处理连接请求（决定是否允许连接）
// Handles connection requests and decides whether to accept/reject
int station_handle_connect_request(station_context_t *ctx, const message_t *req);