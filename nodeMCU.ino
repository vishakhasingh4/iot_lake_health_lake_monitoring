#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
 
/* Set these to your desired credentials. */
const char *ssid = "insertUsername";  //ENTER YOUR WIFI SETTINGS
const char *password = "insertPassword";
 
//Web/Server address to read/write from 
const char *host = "ctrl-c.club";   //https://circuits4you.com website or IP address of server 

#define rled 5
#define gled 4

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    pinMode(rled, OUTPUT);
    pinMode(gled, OUTPUT);
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String ADCData, postData;
  float phvalue;
  int value = analogRead(A0);
  phvalue = (14.0/1024.0)*value;
  postData = "value:" + String(phvalue);
  Serial.println(value);
  http.begin("http://ctrl-c.club:4040");              //Specify request destination
  int httpCode = http.POST(postData);                 //Send the request
  Serial.println("Data sent = " + postData);
  http.end();  //Close connection
  if(phvalue>=6.5 && phvalue <=8.5)
  {
    digitalWrite(gled, HIGH);
    digitalWrite(rled, LOW);
  }
  else{
    digitalWrite(rled, HIGH);
    digitalWrite(gled, LOW);
  }
  
  delay(5000);  //Post Data at every 5 seconds
}
