#  🚀 ปลดล็อค LINE Messaging API จบงาน ส่งข้อความและสติกเกอร์ ไปยัง LINE ด้วย ESP32 ESP8266
หมดปัญหาการจัดการกับ LINE API ที่ยุ่งยากด้วยตัวเอง AllnewstepLine ช่วยให้สามารถส่งทั้งข้อความ และสติกเกอร์ ไปยังผู้ใช้ LINE ได้ทันที โดยใช้ LINE Messaging API 
ด้วยไลบารีส่งข้อความ AllnewstepLine ที่ใช้งานง่าย สำหรับ ESP32 และ ESP8266 จบปัญหาและประหยัดเวลาในการพัฒนาโปรเจกต์ IoT 

**AllnewstepLine** เป็นไลบารีสำหรับ ESP32 ESP8266 ที่ช่วยให้สามารถส่งข้อความและสติกเกอร์ไปยังผู้ใช้ LINE โดยใช้ **LINE Messaging API** รองรับการส่งข้อความ, สติกเกอร์, และข้อความพร้อมสติกเกอร์ให้กับผู้ใช้คนเดียว หลายคน หรือทุกคนในกลุ่ม จบงานได้อย่างรวดเร็ว
คุณสามารถโฟกัสกับฟังก์ชันการทำงานหลักของโปรเจกต์ได้ทันที ไม่ต้องเสียเวลาในการจัดการกับการเชื่อมต่อ API หรือการจัดการข้อความและสติกเกอร์เองให้ยุ่งยาก

## คุณสมบัติ
- ส่ง **ข้อความ** ให้กับผู้ใช้คนเดียว, หลายคน หรือทุกคน
- ส่ง **สติกเกอร์** ให้กับผู้ใช้คนเดียว, หลายคน หรือทุกคน
- ส่ง **ข้อความพร้อมสติกเกอร์** ให้กับผู้ใช้คนเดียว, หลายคน หรือทุกคน
- รองรับการ **escape special characters** ในข้อความ (เช่น การแปลง `\`, `"` และอื่น ๆ)

## การติดตั้ง

### วิธีติดตั้งใน Arduino IDE

1. ดาวน์โหลดไฟล์ไลบารีนี้จาก GitHub
2. ไปที่ **Sketch** > **Include Library** > **Add .ZIP Library** ใน Arduino IDE
3. เลือกไฟล์ .zip ที่ดาวน์โหลดแล้วคลิก **Open**
4. หลังจากติดตั้งเสร็จแล้ว คุณสามารถใช้งานไลบารีนี้ในโปรเจกต์ของคุณได้ทันที

### การติดตั้งผ่าน GitHub

1. คลิกที่ปุ่ม **Clone or Download** บนหน้า GitHub repository ของคุณ
2. คัดลอก URL หรือดาวน์โหลดไฟล์ ZIP
3. ถ้าคุณใช้ Arduino IDE ให้นำไฟล์ไปไว้ในโฟลเดอร์ `libraries` ในโฟลเดอร์โปรเจกต์ของคุณ

## วิธีการใช้งาน

### การตั้งค่า Access Token

ก่อนที่จะสามารถใช้ไลบารีนี้ได้ ต้องมี **LINE Access Token** ก่อน จากที่นี่ LINE Developers https://developers.line.biz/

### ฟังก์ชันการใช้งาน

#### 1. การส่งข้อความ
- ส่งข้อความให้คนเดียว: `Line.sendText("สวัสดี A", "userId");`
- ส่งข้อความให้หลายคน: `Line.sendText("สวัสดี A+B", "userId1,userId2");`
- ส่งข้อความให้ทุกคน: `Line.sendText("สวัสดี 55/5", "");`

#### 2. การส่งสติกเกอร์
- ส่งสติกเกอร์ให้คนเดียว: `Line.sendSticker("userId", "packageId", "stickerId");`
- ส่งสติกเกอร์ให้หลายคน: `Line.sendSticker("userId1,userId2", "packageId", "stickerId");`
- ส่งสติกเกอร์ให้ทุกคน: `Line.sendSticker("", "packageId", "stickerId");`

#### 3. การส่งข้อความพร้อมสติกเกอร์
- ส่งข้อความพร้อมสติกเกอร์ให้คนเดียว: `Line.sendTextWithSticker("Hello Max", "userId", "packageId", "stickerId");`
- ส่งข้อความพร้อมสติกเกอร์ให้หลายคน: `Line.sendTextWithSticker("Hello A+B", "userId1,userId2", "packageId", "stickerId");`
- ส่งข้อความพร้อมสติกเกอร์ให้ทุกคน: `Line.sendTextWithSticker("Hello All", "", "packageId", "stickerId");`

### ฟังก์ชันที่รองรับ
- `sendText(String message, String userId)` : ส่งข้อความ
- `sendSticker(String userId, String packageId, String stickerId)` : ส่งสติกเกอร์
- `sendTextWithSticker(String message, String userId, String packageId, String stickerId)` : ส่งข้อความพร้อมสติกเกอร์
- `escapeStr(String message)` : ฟังก์ชันช่วยในการจัดการกับอักขระพิเศษในข้อความ

**AllnewstepLine** เป็นไลบารี แจกฟรี ที่สะดวกและมีประสิทธิภาพสำหรับการส่งข้อความและสติกเกอร์ผ่าน **LINE Messaging API** บน ESP32 หรือ ESP8266 ช่วยให้คุณสามารถส่งข้อความ, สติกเกอร์ หรือแม้แต่ข้อความพร้อมสติกเกอร์ให้กับผู้ใช้คนเดียว, หลายคน หรือทุกคนในกลุ่มได้อย่างรวดเร็วและง่ายดาย โดยไม่จำเป็นต้องเขียนโค้ดยาว ๆ ให้ซับซ้อน ข้อมูลเพิ่มเติมที่ www.allnewstep.com


