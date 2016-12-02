// WiFi Simple Server


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid     = "ND-guest";
const char* password = "";

ESP8266WebServer server(80);
const int LED=2;

void handleRoot() {
  digitalWrite(LED, 1);
  delay(1000);
  server.send(200, "text/plain", "Hello from your ESP8266!");
  digitalWrite(LED, 0);
}

void handleNotFound(){
  digitalWrite(LED, 1);
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
  digitalWrite(LED, 0);
}

void setup() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println("Connecting to "+String(ssid)); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("+");
  }
  Serial.println("");
  Serial.println("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());  

  server.on("/", handleRoot);
  
  server.onNotFound(handleNotFound);
  
  server.begin();
  
  Serial.println("HTTP server started");
  Serial.flush();
}

void loop() {
  server.handleClient();
}























