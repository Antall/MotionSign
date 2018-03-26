#include "Internet.h"
#include <ESP8266WiFi.h>

const unsigned long UPDATE_TIME = (unsigned long)5*1000;

const char* ssid     = "Artisan's Asylum";
const char* password = "I won't download stuff that will get us in legal trouble.";
const char* host = "172.16.11.16";
const int httpPort = 4567;

void Internet::init(){
  lastRun = 0;

  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

}

void Internet::run(Data &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun < UPDATE_TIME){ return; }
  lastRun = currMillis;

  this->getReserved(data);
  this->postOccupied(data);
}

void Internet::getReserved(Data &data){

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/reserved/2";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(200);

  // Read all the lines of the reply from server and print them to Serial
  String line;
  while(client.available()){
    line = client.readStringUntil('\r');
  }
  Serial.print(line.toInt());
  data.isReserved = (line.toInt() == 1);
  Serial.println(data.isReserved);
  Serial.println("closing connection");
}

void Internet::postOccupied(Data &data){

  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String post;
  if(data.isOccupied){
    post = "1";
    //post = "{\"foo\":\"1\"}";
  }else{
    post = "0";
  }

  String url = "/occupied/2";

  client.println(String("POST ") + url + " HTTP/1.1");
  //client.println("Host: jsonplaceholder.typicode.com");
  client.println("Cache-Control: no-cache");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(post.length());
  client.println();
  client.println(post);

  delay(200);

  String line;
  while(client.available()){
    line = client.readStringUntil('\r');
    Serial.println(line);
  }
  

}
