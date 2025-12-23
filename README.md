# 🎹 Mini Piano with OLED & Mode Switch  
## 基于 Arduino 的 OLED 显示多模式迷你电子钢琴

---

https://github.com/user-attachments/assets/3b03f5a1-47cc-4138-9220-01d30758ef2d


## 📖 Project Overview | 项目简介

This project implements a **mini electronic piano** based on **Arduino Uno**, simulated using **Wokwi**.  
It supports **manual play mode** and **auto demo mode**, with a **SSD1306 OLED display** showing the current mode and note in real time.

本项目基于 **Arduino Uno**，在 **Wokwi 在线仿真平台**上实现了一个迷你电子钢琴系统。  
系统支持 **手动演奏模式** 和 **自动演奏模式**，并通过 **SSD1306 OLED 屏幕**实时显示当前工作模式和音符信息。

---

## ✨ Features | 功能特点

- 🎼 8-key mini piano (C4 ~ C5)
- 🔘 Mode switch button (Manual / Auto Demo)
- 📺 SSD1306 OLED real-time display
- ⏱️ Non-blocking auto play using `millis()`
- ⚡ Instant mode switching without delay blocking

---

## 🔧 Hardware Components | 硬件组成

| Component | Description |
|---------|-------------|
| Arduino Uno | Main controller |
| Push Buttons × 8 | Piano keys |
| Push Button × 1 | Mode switch |
| Buzzer | Sound output |
| SSD1306 OLED | Mode & note display |

---

## 🔌 Wiring Overview | 主要接线说明

### OLED (I2C)

| OLED Pin | Arduino Uno |
|--------|-------------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

### Mode Button

| Button | Arduino Uno |
|------|-------------|
| One side | D2 |
| Other side | GND |

> Internal pull-up resistors are used (`INPUT_PULLUP`).

---

## 🧠 Software Design | 软件设计说明

### 🔄 Mode Control Logic

- `demoMode = false` → Manual Play Mode
- `demoMode = true` → Auto Demo Mode
- Mode toggled by detecting **button edge (HIGH → LOW)**

### ⏱️ Non-blocking Auto Play

Instead of using `delay()`, the auto demo mode uses `millis()` to control note timing.  
This ensures the system remains responsive and can exit demo mode instantly.

自动演奏模式采用基于 `millis()` 的非阻塞时间控制方式，避免了 `delay()` 导致的系统卡顿问题，使模式切换更加流畅、实时。

---

## 🖥️ OLED Display Content | OLED 显示内容

Mode: Manual
Note: C4

or

Mode: Demo
Note: E4

---

## 🧪 Simulation Platform | 仿真平台

- 🌐 **Wokwi Online Simulator**
- Board: Arduino Uno

---

## 📂 File Structure | 文件结构


```bash
├── mini-piano.ino
├── pitches.h
└── diagram.json
```

---

## 🎓 Educational Value | 教学意义

This project demonstrates:
- Digital input handling with pull-up resistors
- State-based mode control
- Non-blocking timing design in embedded systems
- Human–machine interaction via OLED display

非常适合作为：
- 嵌入式系统课程实验
- Arduino 入门与进阶项目
- 状态机与非阻塞设计示例

---

## ⭐ Star Support

如果你觉得这个项目对你有帮助，请给仓库点一个 ⭐ Star！
你的鼓励是我继续优化此项目的最大动力 😊
