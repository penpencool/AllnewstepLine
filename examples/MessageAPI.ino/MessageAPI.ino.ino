#include <AllnewstepLine.h>
// ไลบารีนี้ สร้างโดย www.allnewstep.com 
/* ความสามารถ ส่งข้อความ ส่งสติกเกอร์ ส่งสติกเกอร์พร้อมข้อความ
มี 3 โหมดการส่ง คือ
push: ส่งข้อความ, สติกเกอร์, หรือข้อความพร้อมสติกเกอร์ให้ผู้ใช้คนเดียว
multicast: ส่งข้อความ, สติกเกอร์, หรือข้อความพร้อมสติกเกอร์ให้หลายคนที่ระบุ
broadcast: ส่งข้อความ, สติกเกอร์, หรือข้อความพร้อมสติกเกอร์ให้ทุกคนในกลุ่ม

การดู userID ดูได้จากเว็บนี้ https://webhook.site/
โดยนำ webhook ไปกรอกใน LINE API
เมื่อพิมพ์ใน Chat จะขึ้น userID ในหน้าเว็บ
*/

// LINE กรอก Channel access token
String token = "LINE Channel access token";
String wifi = "wifi";
String pass = "pass";

AllnewstepLine Line(token);

void setup() {
  Serial.begin(115200);
  WiFi.begin(wifi, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // ส่งข้อความ
  // พารามิเตอร์ในฟังก์ชั่นจะเหมือนกัน ต่างกันที่คำสั่งการส่ง ว่าส่งข้อความ ส่งรูป หรือส่งข้อความพร้อมรูป

  Line.sendText("สวัสดี 55/5", ""); //broadcast รูปแบบคำสั่ง สำหรับส่งข้อมูลหาทุกคนในกลุ่ม Line.sendText("ข้อความ","")
  Line.sendText("สวัสดี A", "U4fe185d3a4e7b5809f6d3bb553dfa6"); // push  รูปแบบคำสั่ง สำหรับส่งข้อมูลหา 1 คน Line.sendText("ข้อความ","userID")
  Line.sendText("สวัสดี A+B", "U4fe185d3a4e7b5809f6d3bb553fae6,Ubc065bd2ea8f2f4343ad320102643d"); // multicast รูปแบบคำสั่ง สำหรับส่งข้อมูลหาหลาย คน Line.sendText("ข้อความ","userID1,userID2,...")
  
  // ส่งข้อความพร้อมสติกเกอร์
  Line.sendTextWithSticker("Hello Max", "U4fe185d3a4e7b59f6d3bb553fdfae6", "8515", "16581242");                                              // push :: Line.sendTextWithSticker("ข้อความ", "userId", "packageId", "stickerId")
  Line.sendTextWithSticker("Hello Max + Gift", "U4fe185d3a4e7b59f6d3bb553fdfae6,Ubc065bd2e5a8f2f41343a20102643d", "8515", "16581242");       // multicast :: Line.sendTextWithSticker("ข้อความ", "userId1,userId2", "packageId", "stickerId")
  Line.sendTextWithSticker("Hello ALL", "", "8515", "16581242");                                                                              //broadcast :: Line.sendTextWithSticker("ข้อความ", "", "packageId", "stickerId")

  //ส่งสติกเกอร์
  Line.sendSticker("","8515","16581243"); //broadcast Line.sendSticker("", "packageId", "stickerId")
  Line.sendSticker("U4fe185d3a4e7b5809f6d3bb553fdfae6","8515","16581243"); // push Line.sendSticker("userId", "packageId", "stickerId")
  Line.sendSticker("U4fe185d3a4e7b5809f6d3bb553fdfae6,Ubc065bd2e5a8f2f41343ad320102643d","8515","16581244"); // multicast Line.sendSticker("userId1,userId2", "packageId", "stickerId")
 
}

void loop() {
  // ทำงานอื่น ๆ ที่ต้องการ
}
