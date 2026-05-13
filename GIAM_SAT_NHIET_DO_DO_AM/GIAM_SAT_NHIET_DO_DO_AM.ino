#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include "DHTesp.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WiFi & ThingSpeak
const char* ssid = "Hiệu trưởng trường Phan";
const char* password = "quangtien";
WiFiClient client;

unsigned long myChannelNumber = 2943515;
const char* myWriteAPIKey = "3UG68C385KKESWVG";

  // OLED
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 32
  #define OLED_RESET -1
  #define SCREEN_ADDRESS 0x3C
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT
DHTesp dht;
float temperature, humidity;
unsigned long lastDhtReadTime = 0;

// Relay/Quạt
const int fanPin = D5;              // Relay nối với chân D5 (GPIO14)
const float tempThreshold = 30.0;   // Ngưỡng nhiệt độ bật quạt

// Timer
unsigned long lastSendTime = 0;
const long sendInterval = 20000;    // 20 giây

void setup() {
  Serial.begin(115200);
  delay(100);

  // Khởi động relay
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);  // Tắt quạt ban đầu

  // Khởi động WiFi
  WiFi.begin(ssid, password);
  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi đã kết nối");

  // ThingSpeak
  ThingSpeak.begin(client);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Không khởi tạo được OLED"));
    while (true);
  }
  display.display();
  delay(2000);

  // DHT11
  dht.setup(16, DHTesp::DHT11);
}

void controlFan(float temp) {
  if (temp > tempThreshold) {
    digitalWrite(fanPin, HIGH);  // Bật quạt (HIGH)
    Serial.println(">> Quạt ĐÃ BẬT (nhiệt độ cao)");
  } else {
    digitalWrite(fanPin, LOW);   // Tắt quạt
    Serial.println(">> Quạt TẮT (nhiệt độ bình thường)");
  }
}

void loop() {
  if (millis() - lastDhtReadTime > dht.getMinimumSamplingPeriod()) {
    float t = dht.getTemperature();
    float h = dht.getHumidity();

    if (dht.getStatusString() == "OK") {
      temperature = t;
      humidity = h;
      showOled(temperature, humidity);
      controlFan(temperature); // ← Gọi hàm điều khiển quạt tại đây
    }

    lastDhtReadTime = millis();
  }

  if (millis() - lastSendTime > sendInterval) {
    sendToThingSpeak(temperature, humidity);
    lastSendTime = millis();
  }
}

void sendToThingSpeak(float t, float h) {
  // Lấy trạng thái hiện tại của chân điều khiển quạt/relay (fanPin)
  int fanPinState = digitalRead(fanPin); // Đọc trạng thái logic của chân
  int relayState;
  if (fanPinState == HIGH) {
    relayState = 1; // Nếu chân ở mức CAO (BẬT), gửi 1 (Biểu thị Relay BẬT)
  } else {
    relayState = 0; // Nếu chân ở mức THẤP (TẮT), gửi 0 (Biểu thị Relay TẮT)
  }


  // In ra các giá trị sẽ gửi lên Serial Monitor
  Serial.print("Sending to ThingSpeak: Temp=");
  Serial.print(t, 2);
  Serial.print("°C, Hum=");
  Serial.print(h, 2);
  Serial.print("%, Relay=");
  Serial.print(relayState); // In ra trạng thái 0 hoặc 1
  Serial.print(". ");


  // Gửi dữ liệu lên các Field trên ThingSpeak
  ThingSpeak.setField(1, t); // Gửi Nhiệt độ lên Field 1 (Như code gốc)
  ThingSpeak.setField(2, h); // Gửi Độ ẩm lên Field 2 (Như code gốc)
  ThingSpeak.setField(3, relayState); // Gửi Trạng thái Relay (0 hoặc 1) lên Field 3


  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (x == 200) {
    Serial.println("Đã gửi dữ liệu thành công (Mã 200).");
  } else {
    Serial.print("Gửi dữ liệu thất bại. Mã lỗi: ");
    Serial.println(x);
    // Kiểm tra các mã lỗi phổ biến như đã nêu trước đó.
  }

  Serial.println("Đang chờ...");
}


void showOled(float t, float h) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("T: ");
  display.print(t, 1);
  display.print((char)247);
  display.println("C");
  display.print("H: ");
  display.print(h, 0);
  display.println("%");
  display.display();
}


