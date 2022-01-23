
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMPSENSORCOUNTS 10

String tempSensorsArr[TEMPSENSORCOUNTS];
String stringData;

const char* ssid = "";
const char* password = "";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://piec.herokuapp.com/postTemp/";
String sensor0 = "NA";
String sensor1 = "NA";
String dateTimeZone = "NA";
// Date time zone 
String dStr = "{\"dtm\":\"NA\"";


OneWire oneWire(D7); 
DallasTemperature sensors(&oneWire); 

String serverAnswer;


void setup() {
  Serial.begin(115200);
  sensors.begin();
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
}

void loop() {

    getTempFromSensor();
   
    dStr = "{\"dtm\":\"NA\"";
    
    for(int n = 0; n < TEMPSENSORCOUNTS; n++){
      dStr += ",\"sensor" + String(n) + "\":\"" + tempSensorsArr[n] + "\"";
    }
    
    dStr +=  "}";
    Serial.println(dStr);
    
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){

      serverAnswer = httpSendPost(serverName, dStr);
      Serial.println(serverAnswer);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    
  delay(300000);
}

void getTempFromSensor(){
  sensors.requestTemperatures();
  for(int a = 0; a < TEMPSENSORCOUNTS; a++){
    float t = sensors.getTempCByIndex(a);
      Serial.print("a= ");
      Serial.println(a);
      Serial.print("t= ");
      Serial.println(t);
      
    tempSensorsArr[a] = String(t);
    Serial.print("tempSensorsArr[a] = ");
    Serial.println(tempSensorsArr[a]);
    if(t <= -127){
      tempSensorsArr[a] = "NA";
    }
  }
}

String httpSendPost(const char* serverName, String dataStr) {

  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/json");
  Serial.print("{\"dtm\":\"PL\",\"sensor0\":" + tempSensorsArr[0] + "\"}");
  // Send HTTP POST request
  int httpResponseCode = http.POST(dStr);
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
  

}
  
