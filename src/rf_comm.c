// RF 收发封装
// RF Transceiver Abstraction Layer for IEEE 802.15.4

#include "rf_comm.h"

/// 初始化射频模块
/// Initialize RF hardware and PHY/MAC settings
int rf_init(const rf_config_t *config) {
    // TODO: 初始化射频芯片、配置信道、地址和发射功率
    // TODO: Initialize RF chip, set channel, PAN ID, short address, TX power
    return RF_OK;
}

/// 发送一条完整消息（包含 MAC + APP + Payload）
/// Send a full message frame (MAC + APP + Payload)
int rf_send(const message_t *msg) {
    // TODO: 打包 message 为字节流并发送
    // TODO: Serialize and transmit message via RF module
    return RF_OK;
}

/// 接收一条消息，支持超时机制（单位：毫秒）
/// Receive a message with timeout in milliseconds
int rf_receive(message_t *msg, uint32_t timeout_ms) {
    // TODO: 阻塞接收数据并解析成结构体
    // TODO: Block until frame received or timeout; parse into message_t
    return RF_ERR_TIMEOUT;
}

/// 设置工作信道（如遇干扰可重新选频）
/// Dynamically set RF channel (for interference avoidance)
void rf_set_channel(uint8_t channel) {
    // TODO: 切换射频模块的工作信道
    // TODO: Switch transceiver to specified RF channel
}

/// 扫描所有信道并返回 RSSI 清洁信道
/// Scan RF channels to find low-interference options based on RSSI
void rf_scan_channels(uint8_t *available_channels, uint8_t max_channels) {
    // TODO: 扫描 802.15.4 频段，记录清洁信道
    // TODO: Measure RSSI across channels and return best candidates
}