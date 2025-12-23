/**
   Mini piano for Arduino (OLED + Mode Button Version)

   Added:
   - SSD1306 OLED display (I2C)
   - Mode button (D2) to switch between manual play and auto demo
   - OLED shows current mode and current note
   - Auto demo uses non-blocking millis() timing (can exit immediately)
*/

#include "pitches.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= 基本引脚定义 =================
#define SPEAKER_PIN 8          // 蜂鸣器
#define MODE_BUTTON_PIN 2      // 模式切换按钮（D2）

// ================= OLED 参数 =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ================= 钢琴按键 =================
const uint8_t buttonPins[] = { 12, 11, 10, 9, 7, 6, 5, 4 };
const int buttonTones[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};
const char* noteNames[] = {
  "C4", "D4", "E4", "F4",
  "G4", "A4", "B4", "C5"
};

const int numTones = sizeof(buttonPins) / sizeof(buttonPins[0]);

// ================= 模式控制变量 =================
bool demoMode = false;                 // false = 手动演奏，true = 自动演奏
bool lastModeButtonState = HIGH;       // 上一次按钮状态（用于检测按下）

// ================= 自动演奏旋律 =================
const int demoMelody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4,
  NOTE_E4, NOTE_D4, NOTE_C4
};
const char* demoNoteNames[] = {
  "C4", "D4", "E4", "G4",
  "E4", "D4", "C4"
};
const int demoLength = sizeof(demoMelody) / sizeof(demoMelody[0]);

// ================= 自动演奏状态变量（关键） =================
unsigned long lastNoteTime = 0;        // 上一次播放音符的时间
const unsigned long noteInterval = 500; // 每个音符持续时间（ms）
int demoIndex = 0;                     // 当前播放到第几个音符

// 当前音符（用于 OLED 显示）
const char* currentNote = "--";

// ================= 初始化 =================
void setup() {
  // 钢琴按键初始化（内部上拉）
  for (uint8_t i = 0; i < numTones; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);

  // OLED 初始化
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);  // OLED 初始化失败则停止
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Mini Piano Ready");
  display.display();
}

// ================= 主循环 =================
void loop() {
  // ---------- 模式按钮检测（边沿触发） ----------
  bool modeButtonState = digitalRead(MODE_BUTTON_PIN);
  if (modeButtonState == LOW && lastModeButtonState == HIGH) {
    demoMode = !demoMode;     // 切换模式
    noTone(SPEAKER_PIN);      // 切换时停止当前声音
    demoIndex = 0;            // 重置自动演奏位置
    delay(200);               // 简单消抖
  }
  lastModeButtonState = modeButtonState;

  // ---------- 根据模式执行 ----------
  if (demoMode) {
    playDemoMode();
  } else {
    playManualMode();
  }
}

// ================= 手动演奏模式 =================
void playManualMode() {
  bool keyPressed = false;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Mode: Manual");

  // 检测钢琴按键
  for (uint8_t i = 0; i < numTones; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      tone(SPEAKER_PIN, buttonTones[i]);
      currentNote = noteNames[i];
      keyPressed = true;
      break;   // 只播放一个音符
    }
  }

  // 没有按键则停止发声
  if (!keyPressed) {
    noTone(SPEAKER_PIN);
    currentNote = "--";
  }

  // OLED 显示音符
  display.setCursor(0, 20);
  display.print("Note: ");
  display.println(currentNote);
  display.display();
}

// ================= 自动演奏模式（非阻塞） =================
void playDemoMode() {
  unsigned long currentTime = millis();

  // 到达时间间隔，播放下一个音符
  if (currentTime - lastNoteTime >= noteInterval) {
    lastNoteTime = currentTime;

    tone(SPEAKER_PIN, demoMelody[demoIndex]);
    currentNote = demoNoteNames[demoIndex];

    // OLED 显示
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Mode: Demo");
    display.setCursor(0, 20);
    display.print("Note: ");
    display.println(currentNote);
    display.display();

    demoIndex++;

    // 播放完一轮后从头开始
    if (demoIndex >= demoLength) {
      demoIndex = 0;
    }
  }
}
