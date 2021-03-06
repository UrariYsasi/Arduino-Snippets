/* Provides an HTML interface for 
 *  switching lights in my dorm room
 *  with ESP8266 WiFi module. Can be
 *  repurposed for other simple switching
 *  circuits.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <stdio.h>

MDNSResponder mdns;
ESP8266WebServer server(80);
WiFiClient client;

String webPage = "";

void setup(void){
  webPage += "<h1>NodeMCU LED Automation (Handle with Care)</h1><br/><h3><em><mark>This is a wireless test server to control the power to serveral LEDs.</mark></em></h3><p>Red LED <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Green LED <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  webPage += "<p> UV LED String <a href=\"UV_LEDs_On\"><button>ON</button></a>&nbsp;<a href=\"UV_LEDs_Off\"><button>OFF</button></a></p>";

  // prepare GPIOs
  pinMode(D8, OUTPUT);
  digitalWrite(D8, LOW);
  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW);
  pinMode(D6, OUTPUT);

  // Begin serial output
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ncsu);
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
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }


  // Linked button subroutines
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/redLEDOn", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(D8, HIGH);
    delay(1000);
  });
  server.on("/redLEDOff", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(D8, LOW);
    delay(1000); 
  });
  server.on("/greenLEDOn", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(D7, HIGH);
    delay(1000);
  });
  server.on("/greenLEDOff", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(D7, LOW);
    delay(1000); 
  });
  server.on("/UV_LEDs_On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(D6, HIGH);
  });
 server.on("/UV_LEDs_Off", [](){
 server.send(200, "text/html", webPage);
    digitalWrite(D6, LOW);
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();
} 

void resetClient() {
  client.stop();
  server.begin();
  server.handleClient();
}
