# Smart Home Security System

**Files**  
- `README.md`  
- `SmartHomeSecurity.ino`

## 1. Concept  
A 24/7 home security solution that detects:  
- **Intrusion** via PIR motion sensor  
- **Door/window open** via magnetic reed switch  
- **Gas leak** via MQ-2 combustible gas sensor  
When any alarm triggers, the system sounds a buzzer, flashes an LED, and sends a push notification to your smartphone via Blynk.

## 2. Bill of Materials  
- 1 × NodeMCU ESP8266 board  
- 1 × PIR motion sensor (HC-SR501)  
- 1 × Magnetic reed switch + magnet  
- 1 × MQ-2 gas sensor module + pull-down resistor (10 kΩ)  
- 1 × Active buzzer  
- 1 × LED (5 mm) + resistor (220 Ω)  
- 1 × Breadboard + jumper wires  
- 1 × USB cable for power/programming  
- **Software**: Blynk app (iOS/Android), Blynk library

## 3. Wiring  

    NodeMCU ESP8266            Sensor/Actuator
    ┌─────────────────┐        ┌───────────────┐
    │    VIN (5 V) ──► Vcc     │ PIR motion     │
    │    GND ────────► GND     │ PIR motion     │
    │    D5 ────────► OUT      │ PIR motion     │
    ├─────────────────┤       
    │    3V3 ────────► Vcc     │ MQ-2 gas       │
    │    GND ────────► GND     │ MQ-2 gas       │
    │    A0 ────────► AO       │ MQ-2 gas       │
    ├─────────────────┤       
    │    D6 ────────► one side │ Reed switch    │
    │    GND ────────► other   │ Reed switch    │
    ├─────────────────┤       
    │    D7 ────────► Anode    │ LED (+ 220 Ω)   │
    │    GND ────────► Cathode │ LED             │
    ├─────────────────┤       
    │    D8 ────────► +        │ Buzzer (+)      │
    │    GND ────────► –        │ Buzzer (–)      │
    └─────────────────┘       

> **Note:** MQ-2 analog output goes to A0. Adjust its onboard potentiometer for threshold.

## 4. Blynk Setup  
1. Install the Blynk app on your phone.  
2. Create a new “Device”: select **ESP8266**, connection **Wi-Fi**.  
3. Copy the **Auth Token** emailed to you.  
4. In the app, add a **Notification** widget.

## 5. Usage  
1. Edit `SmartHomeSecurity.ino` with your `WIFI_SSID`, `WIFI_PASS` and `BLYNK_AUTH`.  
2. Open project folder in Arduino IDE.  
3. Install libraries:  
   - **Blynk** (BlynkSimpleEsp8266)  
4. Select **NodeMCU 1.0 (ESP-12E Module)**, correct port.  
5. Compile & Upload.  
6. Open the Blynk app, start the dashboard.  
7. Arm the system by resetting power; any motion, door-open, or gas leak triggers alarm and push notification.

---  
Say **continua** to move on to project #3!  
