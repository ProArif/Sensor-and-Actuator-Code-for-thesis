#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


void setup_wifi();

const char *WIFI_SSID = "Research_LAB";//"Research_LAB";
const char *WIFI_PASS = "diulab505";//"diulab505";
const char *server = "http://192.168.1.145:9000/api/actuators/9/";
const String MAC = "/ac0wtc23"; 

int motor_output = 2;
int http_code;

HTTPClient http;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor_output,OUTPUT);
  setup_wifi();
  digitalWrite(motor_output,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  http.begin(server);

  http_code = http.GET();
  
  String payload = http.getString();
  
  Serial.print("Response Code: ");
  Serial.println(http_code);

  Serial.print("Returned data from server: ");
  Serial.println(payload);

  if (http_code == HTTP_CODE_OK)
  {
    //const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    const size_t capacity = JSON_OBJECT_SIZE(4) + 70;

    DynamicJsonBuffer jsonBuffer(capacity);
    const char* json = payload.c_str();
    
   // Parse JSON object
    
    JsonObject& root = jsonBuffer.parseObject(json);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return;
    }
    
    Serial.println(F("Response"));
    const char* topic = root["topic"]; // "mc101"
    const char* value = root["value"]; // "0"
    const char* time = root["time"]; // "2019-01-24T14:58:02.098448Z"
    const char* name = root["name"];
    //Serial.println(root["topic"].as<char*>());
    Serial.println(topic);
    Serial.println(value);
    Serial.println(time);
    Serial.println(name);

    if(value[0] == '1')
    {
      digitalWrite(motor_output,LOW);
    }else if(value[0] == '0')
    {
      digitalWrite(motor_output,HIGH);
    }
  }
  else
  {
    Serial.println("Error in response");
  }
  http.end();
  
}


void setup_wifi()
{
  Serial.print("Connecting to wifi.");
  WiFi.begin(WIFI_SSID,WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}
