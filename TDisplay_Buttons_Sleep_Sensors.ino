#include "Button2.h";
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Arduino.h>
#include "BME.h"      // BME Include
#include <Wire.h>     // I2C library
#include "ccs811.h"   // CCS811 library
#include <WiFi.h>
#include <WiFiMulti.h>
#include <PubSubClient.h>
// Include Graphics
#include "keenScreen.h"
#include "wifiicon.h"
#include "batticon.h"
#include "tempicon.h"
#include "humicon.h"
#include "pressicon.h"
#include "co2icon.h"
#include "tvocicon.h"
#include "sleepimg.h"

/////////////////////////////////////////////////////////////////

// wifi + mqtt
WiFiMulti wifiMulti;
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long wificonnected = 0;

// battery monitor
const uint8_t blue = 2;
const uint8_t vbatPin = 34;
float VBAT = 0;

// stuff for the screen
TFT_eSPI tft = TFT_eSPI(135, 240); 
#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif
#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif

// Start sensor ccss
CCS811 ccs811; 

// Buttons
#define BUTTON_A_PIN  0
#define BUTTON_B_PIN  35
Button2 buttonA = Button2(BUTTON_A_PIN);
Button2 buttonB = Button2(BUTTON_B_PIN);

// loop timing
const unsigned long eventInterval = 10000;
unsigned long previousTime = 0;

// MQTT Details
#define mqtt_server "192.168.1.100"  // server name or IP
#define mqtt_user "happyplants"      // username
#define mqtt_password "XXXXX"   // password

#define temperature_topic "ttgo/temp"        //Topic temperature
#define pressure_topic "ttgo/pressure"       //Topic pressure
#define humidity_topic "ttgo/humidity"       //Topic humidity
#define tvoc_topic "ttgo/tvoc"               //Topic tvoc
#define eco2_topic "ttgo/eco2"               //Topic eco2

////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("");
  Serial.println("Starting up");
  Wire.begin();
  
  // Setup Screen
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  pinMode(blue, OUTPUT);
  pinMode(vbatPin, INPUT);
  // Load bootImage
  
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 135, 240, keenScreen);

  //start CCS811 Sensor
    
  ccs811.set_i2cdelay(50); // Needed for ESP8266 because it doesn't handle I2C clock stretch correctly
  bool ok= ccs811.begin();
  if( !ok ) Serial.println("setup: CCS811 begin FAILED");  
  ok= ccs811.start(CCS811_MODE_1SEC);
  if( !ok ) Serial.println("setup: CCS811 start FAILED");

  // Connect to wifi
  wifiMulti.addAP("De_Vliegende_Hollander", "XXXXX");
  wifiMulti.addAP("btelecom_4A1BAE", "XXXXX");
  wifiMulti.addAP("CommanderK33N", "XXXXX");
  wifiMulti.addAP("TENDA_", "Pa55word"); 
  
  Serial.println("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        wificonnected = 1;
    }
    
  // Connect MQTT
  client.setServer(mqtt_server, 1883);  
  if (!client.connected()) {
    reconnect();
  }
  
  // setup battery
  pinMode(blue, OUTPUT);
  pinMode(vbatPin, INPUT);
  
  //start BME280 Sensor

  if (!bme280_init()) {
    Serial.println("CRITICAL: Failed to start BME280");
    while (1);
  }

/////////////////////////////////////////////////////////////////

buttonA.setClickHandler(click);
buttonB.setClickHandler(click);
buttonB.setLongClickHandler(longpress);

}

/////////////////////////////////////////////////////////////////

void loop() {
   unsigned long currentTime = millis();
   if (currentTime - previousTime >= eventInterval) {

   buttonA.loop();
   buttonB.loop();

   tft.fillScreen(TFT_BLACK);
   tft.setTextDatum(MC_DATUM);
   tft.setTextSize(1);
    
   // if wifi connected, show Icon
    
    if(wificonnected == 1) {
      tft.setSwapBytes(true);
      tft.pushImage(0, 0, 21, 15, wifiicon);
      Serial.println("wifi ok icon");
    } else {
      Serial.println("no wifi icon");
    }
    

    //if voltage < 4.76 show battery icon + voltage indicator
    //    read voltage
    
    VBAT = (float)(analogRead(vbatPin)) * 3600 / 4095 * 2;
    float VBATOK = VBAT / 1000;
    if (VBATOK < 4.76){
      tft.setCursor(80,5);
      tft.setTextColor(TFT_BLUE,TFT_BLACK);tft.setTextFont(1);
      tft.println(VBATOK); 
      tft.pushImage(107, 0, 23, 15, batticon);
      Serial.println("batt icon");
    } else {
      Serial.println("no batt icon");
    }
    
    //show temp Icon
    tft.pushImage(4, 42, 23, 23, tempicon);
    //Show Hum Icon
    tft.pushImage(4, 73, 23, 23, humicon);
    //Show Press Icon
    tft.pushImage(4, 104, 23, 23, pressicon);
    //show co2 icon
    tft.pushImage(4, 160, 23, 23, co2icon);
    //show tvoc icon
    tft.pushImage(4, 195, 23, 23, tvocicon);

    // read ccs811

    uint16_t eco2, etvoc, errstat, raw;
    ccs811.read(&eco2,&etvoc,&errstat,&raw); 

    tft.setTextColor(TFT_WHITE, TFT_BLACK); tft.setTextFont(2);

    float temp = NAN;
    float hum = NAN;
    float pres = NAN;
    if (bme280_read(&temp, &hum, &pres)) {
    tft.setTextSize(2);
    tft.setCursor(40, 40);
    tft.println(temp);
    tft.setCursor(40, 70);
    tft.println(hum);
    tft.setCursor(40, 100);
    tft.println(pres);
    
    // Publish to mqtt
    
    client.publish(temperature_topic, String(temp).c_str(), true);    
    client.publish(pressure_topic, String(pres).c_str(), true); 
    client.publish(humidity_topic, String(hum).c_str(), true); 
  }
 
    if( errstat==CCS811_ERRSTAT_OK ) { 
      tft.setCursor(40, 175);
      tft.setTextSize(2);
      tft.setCursor(40, 160);
      if (eco2 < 600) 
        {
            tft.setTextColor(TFT_WHITE);
          }
          else if ((eco2 >=600) && (eco2<= 1000)) {
            tft.setTextColor(TFT_GREEN);
          }
          else if ((eco2 >=1000) && (eco2<= 1500)) {
            tft.setTextColor(TFT_YELLOW);
          }
          else if ((eco2 >=1500) && (eco2<= 1800)) {
            tft.setTextColor(TFT_ORANGE);
          }
          else if (eco2 >=1800) {
            tft.setTextColor(TFT_RED);
        }
      tft.println(eco2);

      if (etvoc < 65) 
        {
          tft.setTextColor(TFT_WHITE);
        }
        else if ((etvoc >=65) && (etvoc<= 220)) {
          tft.setTextColor(TFT_GREEN);
        }
        else if ((etvoc >=220) && (etvoc<= 660)) {
          tft.setTextColor(TFT_YELLOW);
        }
        else if ((etvoc >=660) && (etvoc<= 2200)) {
          tft.setTextColor(TFT_ORANGE);
        }
        else if (etvoc >=2200) {
          tft.setTextColor(TFT_RED);
      }
  
      tft.setCursor(40, 190);
      tft.println(etvoc);
  
      // Publish to mqtt
  
      client.publish(tvoc_topic, String(etvoc).c_str(), true);     
      client.publish(eco2_topic, String(eco2).c_str(), true);

     
   } else if( errstat==CCS811_ERRSTAT_OK_NODATA ) {
      Serial.println("CCS811: waiting for (new) data");
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(5, 5);
      tft.setTextColor(TFT_GREEN);tft.setTextFont(2);
      tft.println("waiting data");
  } else if( errstat & CCS811_ERRSTAT_I2CFAIL ) { 
      Serial.println("CCS811: I2C error");
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(5, 5);
      tft.setTextColor(TFT_RED);tft.setTextFont(2);
      tft.println("I2C error");
  } else {
      Serial.print("CCS811: errstat="); Serial.print(errstat,HEX); 
      Serial.print("="); Serial.println( ccs811.errstat_str(errstat) ); 
  }
    previousTime = currentTime;
  }

   buttonA.loop();
   buttonB.loop();
}

/////////////////////////////////////////////////////////////////

void click(Button2& btn) {
  if (btn == buttonA) {
    // Left Button A Pressed
    Serial.println("A clicked");
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.pushImage(0, 0, 135, 240, keenScreen);
        

  } else if (btn == buttonB) {

    Serial.println("B clicked");
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.pushImage(0, 0, 135, 240, keenScreen);
}
}

void longpress(Button2& btn) {
  Serial.println("Bye bye");
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 135, 240, sleepimg);

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 0);
  delay(10000);
  esp_deep_sleep_start();
}

/////////////////////////////////////////////////////////////////

void reconnect() {
 
  if (!client.connected()) {
    Serial.print("Connecting to MQTT broker ...");
    if (client.connect("wifiMulti", mqtt_user, mqtt_password)) {
      Serial.println("OK");
    }
  }
}

/////////////////////////////////////////////////////////////////
