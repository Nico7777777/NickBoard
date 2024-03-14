#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <DHT11.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
#define DHT11_PIN 2 // D4 == GPIO2
#define BMP180_SDA 0 // D3 == GPIO0
#define BMP180_SCL 10 // S3 == GPIO10


/* Put your SSID & Password */
const char* ssid = "SSID";  // Enter SSID here
const char* password = "password";  //Enter Password here
/* Put IP Address details */
IPAddress local_ip(192,168,1,4);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);
DHT11 dht11(DHT11_PIN);

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  delay(100);
  server.begin();
  Serial.println("HTTP server started");
  if (!bmp.begin())
  	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
}
void loop() {
  server.handleClient();
  Serial.println();
  dht_();
  Serial.println();
  bmp_();
  delay(3000);
}

void dht_() {
  Serial.print("DHT11:\n---------------------\n");
  int humi, tempC;
  dht11.readTemperatureHumidity(tempC, humi);

  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    Serial.print("Humidity: "); Serial.print(humi); Serial.print("%");
    Serial.print("  |  "); 
    Serial.print("Temperature: "); Serial.print(tempC); Serial.println(" °C");
  }
}
void bmp_() {
  Serial.print("BMP180:\n---------------------\n");
  Serial.print("Temperature = "); Serial.print(bmp.readTemperature()); Serial.println(" °C");
  Serial.print("Pressure = "); Serial.print(bmp.readPressure()); Serial.println(" Pa");
  Serial.print("Altitude = "); Serial.print(bmp.readAltitude()); Serial.println( " m");
  Serial.print("Altitude(sealevel calculated) = "); Serial.print(bmp.readAltitude(bmp.readSealevelPressure())); Serial.println(" m");
}
String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>NickBoard Home</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}