#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "....";
const char* password = "....";

ESP8266WebServer server(80);

const int led = 13;
bool relayOn = false;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "Relay status:" + ( relayOn ? String("ON") : String("OFF") ) );
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/enable", [](){
    turnOn();
    server.send(200, "text/plain", "Relay enabled");
  });
  server.on("/disable", [](){
    turnOff();
    server.send(200, "text/plain", "Relay disabled");
  });
  server.on("/toggle", [](){
    toggleRelay();
    if ( relayOn ) 
      server.send(200, "text/plain", "Relay enabled");
    else
      server.send(200, "text/plain", "Relay disabled");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

void turnOn(){
  digitalWrite(12, HIGH);
  relayOn = true;  
}

void turnOff(){
  digitalWrite(12, LOW);
  relayOn = false;  
}

void toggleRelay(){
  if ( relayOn ){
    digitalWrite(12, LOW);
    relayOn = false;
  }  else {
    digitalWrite(12, HIGH);
    relayOn = true;  
  }
}
