#include "AllnewstepLine.h"
#include <HTTPClient.h>

// ประกาศ HTTPClient เดียวสำหรับ reuse
HTTPClient http;

// ฟังก์ชันหลักส่งข้อความ
bool AllnewstepLine::sendText(String data, String user) {
  if (user == "") {
    mode = "broadcast";  // ส่งให้ทุกคน
    return sendTextToAll(data);
  } else if (user.indexOf(",") != -1) {
    mode = "multicast";  // ส่งให้หลายคน
    String* userArray;
    int numUsers = splitString(user, ',', userArray);
    return sendTextToMultiple(userArray, numUsers, data);
  } else {
    mode = "push";  // ส่งให้คนเดียว
    return sendTextToSingle(user, data);
  }
}
String AllnewstepLine::escapeStr(String S) {
  S.replace("\\", "\\\\");
  S.replace("\t", "\\t");
  S.replace("\r", "\\r");
  S.replace("\n", "\\n");
  S.replace("\"", "\\\"");
  return(S);
}

// ฟังก์ชันส่งข้อความให้คนเดียว
bool AllnewstepLine::sendTextToSingle(String userId, String message) {
  http.begin("https://api.line.me/v2/bot/message/push");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"to\":\"" + userId + "\",\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}]}";
  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    return true;  // ส่งสำเร็จ
  }
  return false;  // ส่งไม่สำเร็จ
}

// ฟังก์ชันส่งข้อความให้หลายคน
bool AllnewstepLine::sendTextToMultiple(String* users, int numUsers, String message) {
  http.begin("https://api.line.me/v2/bot/message/multicast");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"to\":[";

  // สร้างอาร์เรย์ของ userIds ใน JSON
  for (int i = 0; i < numUsers; i++) {
    payload += "\"" + users[i] + "\"";
    if (i < numUsers - 1) payload += ",";
  }

  payload += "],\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}]}";

  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    return true;  // ส่งสำเร็จ
  }
  return false;  // ส่งไม่สำเร็จ
}

// ฟังก์ชันส่งข้อความให้ทุกคน (Broadcast API)
bool AllnewstepLine::sendTextToAll(String message) {
  http.begin("https://api.line.me/v2/bot/message/broadcast");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}]}";

  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    return true;  // ส่งสำเร็จ
  }
  return false;  // ส่งไม่สำเร็จ
}

// ฟังก์ชันดึงโหมด (push, multicast, broadcast)
String AllnewstepLine::getMode() {
  return mode;
}

// ฟังก์ชันช่วยแยก string ตามตัวแบ่ง
int AllnewstepLine::splitString(String str, char delimiter, String* &outputArray) {
  int count = 0;
  int startIndex = 0;
  int index = 0;

  // คำนวณจำนวนครั้งที่มีตัวแบ่ง
  while ((index = str.indexOf(delimiter, startIndex)) != -1) {
    count++;
    startIndex = index + 1;
  }
  count++; // จำนวนสุดท้าย

  outputArray = new String[count];
  startIndex = 0;
  int i = 0;
  // แยก string
  while ((index = str.indexOf(delimiter, startIndex)) != -1) {
    outputArray[i++] = str.substring(startIndex, index);
    startIndex = index + 1;
  }
  outputArray[i] = str.substring(startIndex); // ค่า last part

  return count;
}

// ฟังก์ชันหลักส่งสติกเกอร์
bool AllnewstepLine::sendSticker(String user, String packageId, String stickerId) {
  if (user == "") {
    mode = "broadcast";  // ส่งให้ทุกคน
    return sendStickerToAll(packageId, stickerId);
  } else if (user.indexOf(",") != -1) {
    mode = "multicast";  // ส่งให้หลายคน
    String* userArray;
    int numUsers = splitString(user, ',', userArray);
    return sendStickerToMultiple(userArray, numUsers, packageId, stickerId);
  } else {
    mode = "push";  // ส่งให้คนเดียว
    return sendStickerToSingle(user, packageId, stickerId);
  }
}

// ฟังก์ชันส่งสติกเกอร์ให้คนเดียว
bool AllnewstepLine::sendStickerToSingle(String userId, String packageId, String stickerId) {
  HTTPClient http;
  http.begin("https://api.line.me/v2/bot/message/push");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"to\":\"" + userId + "\",\"messages\":[{\"type\":\"sticker\",\"packageId\":\"" + packageId + "\",\"stickerId\":\"" + stickerId + "\"}]}";
  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    http.end();
    return true;  // ส่งสำเร็จ
  }
  http.end();
  return false;  // ส่งไม่สำเร็จ
}

// ฟังก์ชันส่งสติกเกอร์ให้หลายคน
bool AllnewstepLine::sendStickerToMultiple(String* users, int numUsers, String packageId, String stickerId) {
  HTTPClient http;
  http.begin("https://api.line.me/v2/bot/message/multicast");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"to\":[";

  // สร้างอาร์เรย์ของ userIds ใน JSON
  for (int i = 0; i < numUsers; i++) {
    payload += "\"" + users[i] + "\"";
    if (i < numUsers - 1) payload += ",";
  }

  payload += "],\"messages\":[{\"type\":\"sticker\",\"packageId\":\"" + packageId + "\",\"stickerId\":\"" + stickerId + "\"}]}";

  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    http.end();
    return true;  // ส่งสำเร็จ
  }
  http.end();
  return false;  // ส่งไม่สำเร็จ
}

// ฟังก์ชันส่งสติกเกอร์ให้ทุกคน (Broadcast API)
bool AllnewstepLine::sendStickerToAll(String packageId, String stickerId) {
  HTTPClient http;
  http.begin("https://api.line.me/v2/bot/message/broadcast");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"messages\":[{\"type\":\"sticker\",\"packageId\":\"" + packageId + "\",\"stickerId\":\"" + stickerId + "\"}]}";

  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    http.end();
    return true;  // ส่งสำเร็จ
  }
  http.end();
  return false;  // ส่งไม่สำเร็จ
}

// ฟังก์ชันส่งข้อความพร้อมสติกเกอร์
bool AllnewstepLine::sendTextWithSticker(String data, String user, String packageId, String stickerId) {
  if (user == "") {
    mode = "broadcast";  // ส่งให้ทุกคน
    return sendTextWithStickerToAll(data, packageId, stickerId);
  } else if (user.indexOf(",") != -1) {
    mode = "multicast";  // ส่งให้หลายคน
    String* userArray;
    int numUsers = splitString(user, ',', userArray);
    return sendTextWithStickerToMultiple(userArray, numUsers, data, packageId, stickerId);
  } else {
    mode = "push";  // ส่งให้คนเดียว
    return sendTextWithStickerToSingle(user, data, packageId, stickerId);
  }
}

// ฟังก์ชันส่งข้อความพร้อมสติกเกอร์ให้คนเดียว
bool AllnewstepLine::sendTextWithStickerToSingle(String userId, String message, String packageId, String stickerId) {
  HTTPClient http;
  http.begin("https://api.line.me/v2/bot/message/push");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"to\":\"" + userId + "\",\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}, {\"type\":\"sticker\",\"packageId\":\"" + packageId + "\",\"stickerId\":\"" + stickerId + "\"}]}";
  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    http.end();
    return true;  // ส่งสำเร็จ
  }
  http.end();
  return false;  // ส่งไม่สำเร็จ
}

// ฟังก์ชันส่งข้อความพร้อมสติกเกอร์ให้หลายคน
bool AllnewstepLine::sendTextWithStickerToMultiple(String* users, int numUsers, String message, String packageId, String stickerId) {
  HTTPClient http;
  http.begin("https://api.line.me/v2/bot/message/multicast");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"to\":[";

  // สร้างอาร์เรย์ของ userIds ใน JSON
  for (int i = 0; i < numUsers; i++) {
    payload += "\"" + users[i] + "\"";
    if (i < numUsers - 1) payload += ",";
  }

  payload += "],\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}, {\"type\":\"sticker\",\"packageId\":\"" + packageId + "\",\"stickerId\":\"" + stickerId + "\"}]}";

  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    http.end();
    return true;  // ส่งสำเร็จ
  }
  http.end();
  return false;  // ส่งไม่สำเร็จ
}

// ฟังก์ชันส่งข้อความพร้อมสติกเกอร์ให้ทุกคน (Broadcast API)
bool AllnewstepLine::sendTextWithStickerToAll(String message, String packageId, String stickerId) {
  HTTPClient http;
  http.begin("https://api.line.me/v2/bot/message/broadcast");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + accessToken);

  String payload = "{\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}, {\"type\":\"sticker\",\"packageId\":\"" + packageId + "\",\"stickerId\":\"" + stickerId + "\"}]}";

  int httpCode = http.POST(payload);

  if (httpCode == 200) {
    http.end();
    return true;  // ส่งสำเร็จ
  }
  http.end();
  return false;  // ส่งไม่สำเร็จ
}


