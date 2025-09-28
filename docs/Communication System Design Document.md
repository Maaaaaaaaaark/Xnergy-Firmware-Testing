# 1 Design Details

## 1.1 Communication Protocol Overview
This system implements a **lightweight time-slotted communication protocol** over IEEE 802.15.4 RF channels, designed for **short-range (≤1 m)** high-concurrency charging networks consisting of mobile robots (MCU A) and stationary charging stations (MCU B). The protocol ensures deterministic message delivery (<100 ms interval) while supporting dynamic session establishment and robust interference handling.
### 1.1.1 Protocol Architecture
- **Topology**: Distributed, decentralized architecture.
- **Device Roles**:
    - **Robot (MCU A)**: Mobile client, initiates charging session.
    - **Station (MCU B)**: Fixed responder, grants or denies charging access.
- **Communication Model**: Semi-synchronous master–slave pairing with **TDMA-based session scheduling** (using GTS).
- **Medium**: 2.4 GHz ISM band using IEEE 802.15.4 PHY/MAC.
- **Channel Strategy**:
    - Select from channels 15, 20, or 25 (less overlapping with Wi-Fi).
    - Neighboring stations use different channels (interference-aware deployment).
    - **CCA (Clear Channel Assessment)** enabled with dynamic black/white list and channel reselection.
### 1.1.2 Session Establishment Procedure
1. **Idle State**: No exchange occurs unless charging is needed.
2. **Scanning**: Robot broadcasts Scan Request in a selected channel band.
3. **Discovery**: Available stations respond with Scan Response, including station_id, status, rf_channel.
4. **Connection Attempt**: Robot sends Connect Request to preferred station.
5. **Handshake**: Both parties exchange **100 B handshake messages** to confirm session.
6. **GTS Assignment**: Upon successful handshake, the station assigns a dedicated **1–2 GTS slots** for the session.
### 1.1.3 Realtime Data Exchange
- During the charging session, robot and station exchange 50 B real-time messages every <100 ms
- GTS guarantees deterministic delivery without collision.
- Timeout monitors are used to detect failure (e.g., >150 ms silence triggers session abort).
### 1.1.4 Concurrency & Capacity Control
- **Air Time Modeling**: A pair consumes ~6 ms of airtime per second .
- **Channel Capacity**: Each channel supports up to 8 concurrent robot–station sessions.
- **Dynamic Admission**:
    - If channel is saturated, station queues or rejects new connect attempts.
    - Capacity-aware policy prevents collisions, supports fairness.
### 1.1.5 Error Handling and Recovery
- **Timeouts**: Missed handshake or delayed real-time updates trigger automatic session reset.
- **Channel Interference**:
    - CCA monitors energy threshold to detect conflict.
    - Channel re-selection and station hopping is supported.
- **Session Termination**:
    - Robot sends Session End upon charge completion or failure.
    - Station releases GTS slots and returns to IDLE state.
## 1.2 Functional Modules Overview

### (1)Charging Requirement Detection Module
- **Responsibility**: Determine when a robot requires charging.
- **Functions**:
    - Monitor battery level and status.
    - Trigger scan when threshold is reached.
### (2)Base Station Discovery Module
- **Responsibility**: Identify suitable charging stations in RF range.
- **Submodules**:
    - Broadcast Scan Request: Robot generates and broadcasts scan messages.
    -  Collect Responses: Station B responds if available. Robot filters valid replies.
    - Select Optimal Station: Evaluate based on signal strength and response latency.
    - Resource Coordination:
        - Assign 1–2 GTS slots.
        - Select interference-free channel.
        - Configure transmission power.
        - Resolve contention if multiple robots are involved.
### (3) Session Establishment Module
- **Responsibility**: Initiate and confirm secure session connection.
- **Submodules**:
    - Connection Request Transmission: Robot sends a targeted connection request.
    - Handshake Exchange:
        - 100-byte payload.
        - Include assigned slot/channel, encryption, authentication.
        - ACK/REJECT logic based on conflict arbitration.
    - Session Confirmation: Validate session_id and robot_id. Transition to SESSION_ACTIVE.
### (4) Real-Time Communication Module
- **Responsibility**: Maintain real-time bidirectional data exchange.
- **Submodules**:
    - Scheduled Message Generation:
        - 50-byte messages.
        - Sent at intervals < 100ms.
    - Message Transmission Processing:
        - Encode, send, receive, and decode real-time messages.
    - Session Monitoring & Maintenance:
        - Detect timeouts.
        - Initiate error recovery if packet lost or delayed.
    - GTS Monitoring & Time Sync:
        - Ensure slot integrity.
        - Time resync if necessary.
### (5) Channel & Power Management Module
- **Responsibility**: Ensure interference-free RF communication.
- **Functions**:
    - Implement blacklist & energy detection.
    - Apply frequency hopping or CCA (Clear Channel Assessment).
    - Select reuse-safe channel.
    - Dynamically manage transmission power.
### (6) GTS Arbitration & Slot Scheduler
- **Responsibility**: Assign transmission slots for real-time data.
- **Functions**:
    - Allocate 1–2 GTS slots per session.
    - Enforce slot duration ≤ 61.44ms (per GTS).
    - Reschedule missed or delayed packets.
# 2 Pseudocode Overview
## 2.1  Session FSM Pseudocode（session.c)
```c
void session_update(session, time):
    switch(session.state):
        case SESSION_IDLE:
            if handshake_received:
                session.state = SESSION_HANDSHAKE
        case SESSION_HANDSHAKE:
            if handshake_valid:
                session.state = SESSION_ACTIVE
        case SESSION_ACTIVE:
            if timeout or error:
                session.state = SESSION_ENDING
        case SESSION_ENDING:
            session_reset(session)
```
## 2.2 Robot charging request(robot_app.c)
```c
void robot_charging_request(robot_context_t *ctx) {
    if (ctx->state != ROBOT_IDLE) return;

    ctx->state = ROBOT_SCANNING;
    int scan_result = robot_scan_stations(ctx, 500);  

    if (scan_result >= 0) {
        ctx->selected_station_id = scan_result;
        ctx->state = ROBOT_CONNECTING;

        int conn_result = robot_connect_to_station(ctx, ctx->selected_station_id);
        if (conn_result == 0) {
            ctx->state = ROBOT_IN_SESSION;
            robot_maintain_session(ctx);  
        } else {
            ctx->state = ROBOT_ERROR;
        }
    } else {
        ctx->state = ROBOT_ERROR;
    }
}
```
## 2.3 station select unique channel(station_app.c)
```c
void station_select_unique_channel(station_context_t *stations, uint8_t count) {
    uint8_t preferred_channels[] = {15, 20, 25};
    for (uint8_t i = 0; i < count; ++i) {
        stations[i].rf_channel = preferred_channels[i % 3];
    }
}
```