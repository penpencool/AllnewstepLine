#include <AllnewstepLine.h>
// *** LINE กรอก Channel access token
String token = "Channel access token";
String wifi = "wifi";
String pass = "pass";

AllnewstepLine Line(token);
void setup() {
  Serial.begin(115200);
  WiFi.begin(wifi, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.priintln(".");
    delay(1000);
  }
  Serial.priintln("Connected");
  // ฟังก์ชั่นการส่งข้อความ LINE
  Line.sendText("สวัสดี 555", "");                                  // ส่งข้อความ ให้ทุกคนในกลุ่ม
  Line.sendSticker("", "8515", "16581243");                       // ส่งสติกเกอร์ ให้ทุกคนในกลุ่ม
  Line.sendTextWithSticker("Hello ALL", "", "8515", "16581242");  // ส่งข้อความพร้อมสติกเกอร์ ให้ทุกคนในกลุ่ม
  Serial.priintln("LINE Send");
}

void loop() {
}
