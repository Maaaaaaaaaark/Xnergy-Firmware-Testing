// MCU A（机器人端）主逻辑模块
// 负责电量检测、基站扫描、建立连接、维持充电会话

#include "robot_app.h"

/**
 * @brief 机器人发起充电请求
 *
 * 逻辑说明：
 * - 当机器人电池低于阈值时调用该函数
 * - 设置状态为 ROBOT_SCANNING
 * - 触发扫描流程
 *
 * @param ctx 机器人上下文（包含状态、session 等信息）
 */
void robot_charging_request(robot_context_t *ctx) {
    // TODO: 检测电池电量
    // TODO: 如果需要充电，则更新 ctx->state = ROBOT_SCANNING
}

/**
 * @brief 扫描附近可用的基站
 *
 * 逻辑说明：
 * - 向 RF 模块广播 Scan Request
 * - 接收基站的 Scan Response
 * - 根据信号强度/延迟筛选可用基站
 *
 * @param ctx 机器人上下文
 * @param timeout_ms 扫描超时时间（毫秒）
 * @return 成功时返回找到的基站数量，失败返回负值
 */
int robot_scan_stations(robot_context_t *ctx, uint32_t timeout_ms) {
    // TODO: 构造 MSG_SCAN_REQ 消息
    // TODO: 调用 rf_send() 广播
    // TODO: 循环 rf_receive() 收集 MSG_SCAN_RESP
    // TODO: 根据 RSSI/延迟等策略筛选合适的基站
    return -1; // 默认未找到
}

/**
 * @brief 连接到指定的基站
 *
 * 逻辑说明：
 * - 向目标基站发送 Connect Request
 * - 等待握手确认
 * - 如果成功，更新 session 信息并进入 ROBOT_IN_SESSION
 *
 * @param ctx 机器人上下文
 * @param station_id 目标基站 ID
 * @return 0 表示成功，负值表示失败
 */
int robot_connect_to_station(robot_context_t *ctx, uint16_t station_id) {
    // TODO: 构造 MSG_CONNECT_REQ 消息
    // TODO: 调用 rf_send() 发送
    // TODO: 等待 MSG_HANDSHAKE 消息确认
    // TODO: 更新 ctx->current_session
    // TODO: ctx->state = ROBOT_IN_SESSION
    return -1; // 默认失败
}

/**
 * @brief 维持充电会话（周期性调用）
 *
 * 逻辑说明：
 * - 按 <100ms 的间隔发送 50B 实时数据
 * - 接收基站返回的实时数据
 * - 检测超时/丢包，进行错误恢复或断开
 * - 电量充满后发送 Session End
 *
 * @param ctx 机器人上下文
 */
void robot_maintain_session(robot_context_t *ctx) {
    // TODO: 构造 MSG_REAL_TIME 消息并发送
    // TODO: 接收基站返回的 MSG_REAL_TIME
    // TODO: 检查超时，必要时重发或重置会话
    // TODO: 判断电量是否充满，若充满则发送 MSG_SESSION_END
}