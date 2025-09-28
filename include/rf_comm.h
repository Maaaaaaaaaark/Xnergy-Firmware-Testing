#pragma once
#include <stdint.h>
#include "protocol.h"


// 信道配置范围 / RF Channel Range (IEEE 802.15.4 uses 11–26)
#define RF_CHANNEL_MIN 11     // 最小信道号 / Minimum RF channel
#define RF_CHANNEL_MAX 26     // 最大信道号 / Maximum RF channel


// 通用返回值定义 / Common Return Values
#define RF_OK            0    // 操作成功 / Operation succeeded
#define RF_ERR_TIMEOUT  -1    // 超时 / Timeout error
#define RF_ERR_BUSY     -2    // 正在忙碌 / Module busy
#define RF_ERR_INVALID  -3    // 无效参数 / Invalid parameter


// 射频模块配置结构体 / RF Configuration Structure
typedef struct {
    uint8_t channel;          // 当前信道号 / RF channel in use
    uint16_t pan_id;          // 网络 PAN ID / Personal Area Network ID
    uint16_t short_addr;      // 本地短地址 / Local short address
    int8_t tx_power;          // 发射功率（单位 dBm）/ Transmission power (in dBm)
} rf_config_t;


// 射频通信接口 / RF Communication Interface

// 初始化射频模块（设置信道、地址、功率）
// Initialize RF module with channel, address, power settings
int rf_init(const rf_config_t *config);

// 发送一条完整消息（含 MAC、APP 层和负载）
// Send a complete message (includes MAC + App + Payload)
int rf_send(const message_t *msg);

// 接收一条完整消息，带超时（单位：毫秒）
// Receive a message with timeout (timeout_ms in milliseconds)
int rf_receive(message_t *msg, uint32_t timeout_ms);

// 切换工作信道（运行时动态修改）
// Dynamically switch RF channel at runtime
void rf_set_channel(uint8_t channel);

// 主动扫描信道，记录可用信道列表（依据 RSSI）
// Scan available channels based on RSSI and populate available list
void rf_scan_channels(uint8_t *available_channels, uint8_t max_channels);