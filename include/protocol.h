#pragma once
#include <stdint.h>


// 消息类型定义 / Message Type Enumeration
typedef enum {
    MSG_SCAN_REQ    = 0x01,  // 扫描请求 / Scan Request
    MSG_SCAN_RESP   = 0x02,  // 扫描响应 / Scan Response
    MSG_CONNECT_REQ = 0x03,  // 连接请求 / Connection Request
    MSG_HANDSHAKE   = 0x04,  // 握手消息 / Handshake Message
    MSG_REAL_TIME   = 0x05,  // 实时消息 / Real-time Data Message
    MSG_SESSION_END = 0x06   // 会话结束 / Session Termination
} msg_type_t;


// 基站状态 / Station Status
typedef enum {
    STATION_FREE     = 0x00, // 空闲 / Free
    STATION_OCCUPIED = 0x01  // 占用中 / Occupied
} station_status_t;


// 握手消息载荷（100字节） / Handshake Payload (100 bytes)
typedef struct __attribute__((packed)) {
    uint8_t robot_id;              // 机器人编号 / Robot ID
    uint8_t session_id;            // 会话编号 / Session ID
    uint8_t battery_level;         // 当前电量（百分比）/ Battery level (%)
    uint8_t capabilities[5];       // 功能描述（如支持快充）/ Capabilities (e.g., fast charge support)
    char robot_name[16];           // 机器人名称 / Robot name (optional)

    uint8_t assigned_gts_slot;     // 分配的 GTS 槽编号（0–6）/ Assigned GTS slot (0–6)
    uint8_t gts_count;             // 使用的 GTS 槽数量（1 或 2）/ Number of GTS slots (1 or 2)
    uint8_t rf_channel;            // 分配的信道编号 / Assigned RF channel
    int8_t  tx_power_dbm;          // 发射功率设置 / Transmission power (dBm)
    uint8_t handshake_flags;       // 握手标志位（支持重传/抢占等）/ Handshake flags (e.g., retransmission, preemption)

    uint8_t reserved[69];          // 保留字段，补齐到 100 字节 / Reserved padding (total 100 bytes)
} handshake_payload_t;


// 实时消息载荷（50字节） / Real-time Payload (50 bytes)
typedef struct __attribute__((packed)) {
    uint16_t current_mA;           // 电流 (mA) / Current in mA
    uint16_t voltage_mV;           // 电压 (mV) / Voltage in mV
    uint16_t power_mW;             // 功率 (mW) / Power in mW
    uint8_t  status_flags;         // 状态标志位 / Status flags
    uint8_t  temperature;          // 当前温度（摄氏）/ Temperature (°C)
    uint8_t  reserved[43];         // 填充至 50 字节 / Reserved padding
} realtime_payload_t;


// 应用层消息头 / Application Layer Header
typedef struct __attribute__((packed)) {
    uint8_t  msg_type;             // 消息类型（如 MSG_HANDSHAKE）/ Message type (e.g., MSG_HANDSHAKE)
    uint16_t seq_num;              // 序列号 / Sequence number
    uint16_t src_id;               // 源设备 ID / Source device ID
    uint16_t dest_id;              // 目标设备 ID / Destination device ID
    uint8_t  payload_len;          // 有效载荷长度 / Payload length
} app_header_t;


// MAC 层头部（IEEE 802.15.4）/ MAC Header (802.15.4-compatible)
typedef struct __attribute__((packed)) {
    uint8_t frame_type     : 3;    // 帧类型 / Frame type
    uint8_t security       : 1;    // 加密标志 / Security enabled
    uint8_t frame_pending  : 1;    // 后续帧待发送 / Frame pending
    uint8_t ack_required   : 1;    // 需要 ACK / ACK required
    uint8_t intra_pan      : 1;    // 同 PAN 标志 / Intra-PAN
    uint8_t reserved       : 1;

    uint8_t dest_addr_mode : 2;    // 目的地址模式 / Destination addressing mode
    uint8_t version        : 2;    // 帧版本 / Frame version
    uint8_t src_addr_mode  : 2;    // 源地址模式 / Source addressing mode

    uint16_t dest_pan;             // 目标 PAN ID / Destination PAN ID
    uint16_t dest_addr;            // 目标短地址 / Destination short address
    uint16_t src_addr;             // 源短地址 / Source short address
} mac_header_t;


// 完整消息结构体 / Full Message Structure
typedef struct __attribute__((packed)) {
    mac_header_t mac_header;       // MAC 层头部 / MAC Header
    app_header_t app_header;       // 应用层头部 / Application Header
    union {
        handshake_payload_t handshake;   // 握手数据 / Handshake payload
        realtime_payload_t  realtime;    // 实时数据 / Realtime payload
        uint8_t raw_payload[100];        // 原始数据（兜底）/ Raw payload (fallback)
    } payload;
    uint16_t fcs;                  // 帧校验序列 / Frame Check Sequence
} message_t;