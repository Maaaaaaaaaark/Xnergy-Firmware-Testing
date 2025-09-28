// 基站主逻辑模块（MCU B）
// 响应扫描请求、连接请求，管理会话与信道

#include "station_app.h"

/**
 * @brief 多基站部署时，选择不冲突的工作信道
 *
 * @param stations 所有基站的上下文数组
 * @param count 基站数量
 */
void station_select_unique_channel(station_context_t *stations, uint8_t count) {
    // TODO: 遍历所有基站
    // TODO: 分配不重叠的 rf_channel（如信道15/20/25）
}

/**
 * @brief 响应来自机器人的扫描请求
 *
 * @param ctx 当前基站上下文
 * @param req 收到的 MSG_SCAN_REQ 消息
 * @return 返回 0 表示已响应，负值表示拒绝（如信号太弱）
 */
int station_handle_scan_request(station_context_t *ctx, const message_t *req) {
    // TODO: 检查当前状态是否空闲
    // TODO: 根据 RSSI 等判断是否响应
    // TODO: 构造 MSG_SCAN_RESP 返回
    return -1;
}

/**
 * @brief 处理机器人的连接请求
 *
 * @param ctx 当前基站上下文
 * @param req 收到的 MSG_CONNECT_REQ 消息
 * @return 0 表示接收并建立连接，负值表示拒绝
 */
int station_handle_connect_request(station_context_t *ctx, const message_t *req) {
    // TODO: 检查是否处于空闲状态
    // TODO: 若 busy 且 auto_reject_busy 为真，直接返回拒绝
    // TODO: 构造握手（MSG_HANDSHAKE）消息并回复
    // TODO: 初始化 session
    return -1;
}