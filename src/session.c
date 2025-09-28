// 会话管理模块（MCU A 与 MCU B 都会调用）
// 管理握手状态、实时通信状态、超时与重试逻辑

#include "session.h"

/**
 * @brief 初始化一个新会话
 *
 * @param s 会话对象指针
 * @param partner_id 对端设备 ID（机器人或基站）
 * @param is_initiator 当前端是否为主动方（机器人为 true）
 */
void session_init(session_t *s, uint16_t partner_id, bool is_initiator) {
    // TODO: 重置所有状态字段
    // TODO: 设置 partner_id 和 is_initiator
    // TODO: state = SESSION_HANDSHAKE
}

/**
 * @brief 处理握手消息（100字节）
 *
 * @param s 会话对象
 * @param msg 接收到的握手消息
 */
void session_handle_handshake(session_t *s, const message_t *msg) {
    // TODO: 校验消息类型
    // TODO: 提取 GTS、信道、功率信息
    // TODO: 更新 session 状态为 SESSION_ACTIVE
}

/**
 * @brief 处理实时通信消息（50字节）
 *
 * @param s 会话对象
 * @param msg 接收到的实时消息
 * @param stats 用于统计实时性能数据（间隔、丢包等）
 */
void session_handle_realtime(session_t *s, const message_t *msg, realtime_stats_t *stats) {
    // TODO: 检查序列号是否连续
    // TODO: 更新 last_msg_time
    // TODO: 更新 stats 统计信息
}

/**
 * @brief 会话状态更新（周期调用）
 *
 * @param s 会话对象
 * @param current_time 当前系统时间（单位 ms）
 */
void session_update(session_t *s, uint32_t current_time) {
    // TODO: 检测超时
    // TODO: 若长时间无通信则进入 SESSION_ENDING
}

/**
 * @brief 判断是否需要重试发送
 *
 * @param s 会话对象
 * @param current_time 当前系统时间
 * @return true 表示需要重试
 */
bool session_need_retry(const session_t *s, uint32_t current_time) {
    // TODO: 根据 last_msg_time 和 retry_count 判断是否超时重发
    return false;
}

/**
 * @brief 彻底重置会话状态
 *
 * @param s 会话对象
 */
void session_reset(session_t *s) {
    // TODO: 重置所有字段为初始状态
}