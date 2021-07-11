#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
#define Relay D8
#define led D5
void setup() 
{
  Serial.begin(9600);
  String SS_ID = "JioFiber-24_GHz";
  String PASS = "9814826244";
  WiFi.begin(SS_ID,PASS);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("..");
    delay(200);
  }
  Serial.println();
  Serial.print("NODE MCU is connected to ");
  Serial.println(SS_ID);
  Serial.println(WiFi.localIP());
  server.begin();
  pinMode(Relay,OUTPUT);
}


void loop()
{
  client = server.available();
  if (client == 1)
  {
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if (request == "GET /A HTTP/1.1" || request == "GET /forward HTTP/1.1" || request == "GET /right HTTP/1.1")
    {
      digitalWrite(Relay,LOW);
    }
    if (request == "GET /a HTTP/1.1" || request == "GET /back HTTP/1.1" || request == "GET /left HTTP/1.1")
    {
      digitalWrite(Relay,HIGH);
    }
  }
}
