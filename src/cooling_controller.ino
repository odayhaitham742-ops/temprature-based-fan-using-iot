#define BLYNK_TEMPLATE_ID "TMPL2kNqU_oel"
#define BLYNK_TEMPLATE_NAME "ds18b20"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// 📌 تعريفات الأجهزة والثوابت
#define ONE_WIRE_BUS 4
#define RELAY1 18 // مخرج الريلاي 1
#define RELAY2 19 // مخرج الريلاي 2

// 🌐 معلومات شبكة WiFi
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// ⏱️ متغيرات Blynk و Timer
BlynkTimer timer;

// 🌡️ تعريف كائنات الحساسات في النطاق العام (Global Scope)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ⚙️ حدود التشغيل والتحكم (الثوابت)
const float FAN1_ON = 30.0;
const float FAN2_ON = 40.0;
const float FIRE_ALARM = 55.0; // الحد الذي يشغل الإنذار والإشعار

// 💡 حالات الريلاي وعلم الإنذار (للتتبع وضمان إشعار واحد)
bool fan1State = false;
bool fan2State = false;
bool fireAlarm = false; // علم حالة الإنذار

// ---------------------------------------------

// 📤 دالة إرسال درجة الحرارة إلى Blynk والتحكم في الريلاي
void sendTemperature() {
  // 1. القراءة من الحساس
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  float tempF = sensors.toFahrenheit(tempC);

  // 2. إرسال القيم إلى Blynk (V0: Celsius, V1: Fahrenheit)
  Blynk.virtualWrite(V0, tempC); 
  Blynk.virtualWrite(V1, tempF); 
  Serial.print("Blynk Temp C: ");
  Serial.println(tempC);

  // 3. منطق التحكم بالريلاي والإشعارات
  
  // 🔥 حالة الحريق (الإنذار)
  if (tempC >= FIRE_ALARM) { 
    if (!fireAlarm) {
      // 🚨 إرسال الحدث إلى Blynk (يجب إعداده مسبقاً في Blynk Console)
      Blynk.logEvent("fire_alert", String("⚠️ الحرارة تجاوزت الحد! القراءة: ") + tempC + " °C");
      
      Serial.println("🚨🔥 إنذار حريق! تم إرسال إشعار Blynk 🔥🚨");
      fireAlarm = true; // نضبط العلم لضمان الإرسال مرة واحدة
    }
    
    // إطفاء (أو تشغيل) جميع المراوح في حالة الإنذار (حسب منطقك السابق)
    digitalWrite(RELAY1, LOW); 
    digitalWrite(RELAY2, LOW);
    fan1State = false;
    fan2State = false;
  }
  
  // 🔹 الحالة العادية (أقل من الإنذار)
  else { 
    // 💡 إعادة تعيين حالة الإنذار (لتمكين إرسال تنبيه جديد لاحقاً)
    if (fireAlarm) {
        fireAlarm = false;
        Serial.println("✅ تم إعادة تعيين نظام الإنذار.");
    }

    // التحكم في المروحة 1
    if (tempC >= FAN1_ON && !fan1State) {
      digitalWrite(RELAY1, HIGH); // تشغيل
      fan1State = true;
      Serial.println("✅ تشغيل المروحة 1");
    } else if (tempC < FAN1_ON && fan1State) {
      digitalWrite(RELAY1, LOW); // إيقاف
      fan1State = false;
      Serial.println("🟡 إيقاف المروحة 1");
    }

    // التحكم في المروحة 2
    if (tempC >= FAN2_ON && !fan2State) {
      digitalWrite(RELAY2, HIGH); // تشغيل
      fan2State = true;
      Serial.println("✅ تشغيل المروحة 2");
    } else if (tempC < FAN2_ON && fan2State) {
      digitalWrite(RELAY2, LOW); // إيقاف
      fan2State = false;
      Serial.println("🟡 إيقاف المروحة 2");
    }
  }
}

// ---------------------------------------------

void setup() {
  // 🔴 الإعداد التسلسلي
  Serial.begin(115200);
  
  // 🌡️ إعداد الحساسات
  sensors.begin();

  // ⚡ إعداد الريلاي كمخارج
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  // الحالة الأولية للريلاي (إيقاف تشغيل)
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);

  // 🌐 إعداد Blynk والاتصال بالـ WiFi
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // ⏰ جدولة دالة إرسال الحرارة والتحكم كل 2000 ميللي ثانية (2 ثانية)
  timer.setInterval(2000L, sendTemperature); 

  Serial.println("🔥 نظام Blynk ومراقبة الحرارة جاهز 🔥");
}

// ---------------------------------------------

void loop() {
  // 🏃 تشغيل خدمات Blynk
  Blynk.run();
  // ⏰ تشغيل الـ Timer لجدولة الدالة
  timer.run();
}