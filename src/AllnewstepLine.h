#pragma once

#if defined(ESP32)
  #include <WiFi.h>
  #include <HTTPClient.h>
  #include <WiFiClientSecure.h>
  #define HARDWARE "esp32"

#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClientSecure.h>
  #define HARDWARE "esp8266"

#else
  #error "This library supports only ESP8266 and ESP32 platforms"
#endif

class AllnewstepLine {
  private:
    String accessToken;
    String mode;  // เก็บโหมดของการส่งข้อความ (push, multicast, broadcast)
	String escapeStr(String S);
	
	// ส่งข้อความ
    bool sendTextToSingle(String userId, String message); // ฟังก์ชันส่งข้อความให้คนเดียว
    bool sendTextToMultiple(String* users, int numUsers, String message); // ฟังก์ชันส่งข้อความให้หลายคน
    bool sendTextToAll(String message); // ฟังก์ชันส่งข้อความให้ทุกคน
	
	// ส่งข้อความพร้อมสติกเกอร์
	bool sendTextWithStickerToSingle(String userId, String message, String packageId, String stickerId);
	bool sendTextWithStickerToMultiple(String* users, int numUsers, String message, String packageId, String stickerId);
	bool sendTextWithStickerToAll(String message, String packageId, String stickerId);


	// ฟังก์ชันหลักส่งสติกเกอร์
    bool sendStickerToSingle(String userId, String packageId, String stickerId); // ฟังก์ชันหลักส่งสติกเกอร์
    bool sendStickerToMultiple(String* users, int numUsers, String packageId, String stickerId);    // ฟังก์ชันส่งสติกเกอร์ให้หลายคน
    bool sendStickerToAll(String packageId, String stickerId);    // ฟังก์ชันส่งสติกเกอร์ให้ทุกคน
	
	
    // ฟังก์ชันดึงโหมด (push, multicast, broadcast)
    String getMode();

    // ประกาศฟังก์ชันช่วยแยกสตริง
    int splitString(String str, char delimiter, String* &outputArray);

  public:
    // Constructor
    AllnewstepLine(String token) {
      accessToken = token;
      mode = "";  // เริ่มต้นค่า mode เป็นค่าว่าง
    }

    // ฟังก์ชันหลักส่งข้อความ
    bool sendText(String data, String user);
	// ฟังก์ชันส่งข้อความพร้อมสติกเกอร์
    bool sendTextWithSticker(String data, String user, String packageId, String stickerId);
	// ฟังก์ชั่นส่งสติกเกอร์
	bool sendSticker(String user, String packageId, String stickerId);
};


