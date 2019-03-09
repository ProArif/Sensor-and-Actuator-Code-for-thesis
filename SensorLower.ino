#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


void wifi_setup();
void json_format();

const char *WIFI_SSID = "Research_LAB";//"Research_LAB";
const char *WIFI_PASS = "diulab505";//"diulab505";
const char *api = "http://192.168.1.145:9000/api/lowersensors/";
const String MAC = "/S07LSWTC23"; 

int sensorValue = A0;

  
HTTPClient http;
StaticJsonBuffer<300> json_buff;
JsonObject &json_encoder = json_buff.createObject();
char json_message_buffer[300];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorValue,INPUT);
  setup_wifi();

}

void loop() {
  // put your main code here, to run repeatedly:

  json_format();
  
  http.begin(api);

  http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
  int httpCode = http.POST(json_message_buffer);   //Send the request
  String payload = http.getString();                                        //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
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

void json_format()
{
  json_encoder["topic"] = "Soil";
  json_encoder["value"]= "1011";
  json_encoder["time"] = "2019-01-24T13:35:24.246226Z";
  json_encoder["name"] = "Sayeed"; 
//  json_encoder["sensor_tag"] = "/S07LSWTC23";
//  json_encoder["value"] = sensorValue = analogRead(sensorValue);
  json_encoder.prettyPrintTo(json_message_buffer,sizeof(json_message_buffer));
  Serial.println(json_message_buffer);
}
