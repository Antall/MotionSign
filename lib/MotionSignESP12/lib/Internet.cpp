#include "Internet.h"

const unsigned long UPDATE_TIME = (unsigned long)5*1000;

const char* SSID     = "Artisan's Asylum";
const char* PASSWORD = "I won't download stuff that will get us in legal trouble.";
const char* HOST = "172.16.11.16";
const int PORT = 4567;
const int ROOM_NUMBER = 2;

void Internet::init(){
  lastRun = 0;
  currRequest = 0;

  // We start by connecting to a WiFi network
#ifdef DEBUG_PRINT
  Serial.print("Connecting to ");
  Serial.println(SSID);
#endif

  delay(100);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG_PRINT
    Serial.print(".");
#endif
  }

#ifdef DEBUG_PRINT
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
#endif

}

void Internet::run(Data &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun < UPDATE_TIME){ return; }
  lastRun = currMillis;

  WiFiClient client;
  if (!client.connect(HOST, PORT)) {
#ifdef DEBUG_PRINT
    Serial.println("connection failed");
#endif
    return;
  }

  switch(currRequest){
    case GET_RESERVED: this->getReserved(data, client); break;
    case POST_OCCUPIED: this->postOccupied(data, client); break;
    case GET_DISPLAY: this->getDisplay(data,client); break;
  }
  currRequest = (currRequest+1) % REQUEST_COUNT;

}

void Internet::getDisplay(Data &data, WiFiClient &client){
  String url = "/display/" + String(ROOM_NUMBER);

  // This will send the request to the server
  client.print(String("GET ") + url +
      " HTTP/1.1\r\n" + "Host: " +
      HOST + "\r\n" +
      "Connection: close\r\n\r\n"
      );
  delay(200);

  // Read all the lines of the reply until we get to "DATA"
  /*
  String line;
  while(client.available()){
    line = client.readStringUntil('\r');
    Serial.println(line);
    line.trim();
    if(line == String("DATA")){
      Serial.println("BREAK");
      break;
    }
  }
  */

  // Then send everything to data
  data.wipeScreen();
  while(client.available()){
    char incomingByte = client.read();
    Serial.write(incomingByte);
    data.storeChar(incomingByte);
  }

}

void Internet::getReserved(Data &data, WiFiClient &client){

#ifdef DEBUG_PRINT
  Serial.print("connecting to ");
  Serial.println(HOST);
#endif

  // We now create a URI for the request
  String url = "/reserved/" + String(ROOM_NUMBER);
#ifdef DEBUG_PRINT
  Serial.print("Requesting URL: ");
  Serial.println(url);
#endif

  // This will send the request to the server
  client.print(String("GET ") + url +
      " HTTP/1.1\r\n" + "Host: " +
      HOST + "\r\n" +
      "Connection: close\r\n\r\n"
      );
  delay(200);

  // Read all the lines of the reply from server and print them to Serial
  String line;
  while(client.available()){
    line = client.readStringUntil('\r');
  }
  data.isReserved = (line.toInt() == 1);
}

void Internet::postOccupied(Data &data, WiFiClient &client){

  String post;
  if(data.isOccupied){
    post = "1";
  }else{
    post = "0";
  }

  String url = "/occupied/" + String(ROOM_NUMBER);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" + "Host: " + HOST + "\r\n" +
      "Cache-Control: no-cache\r\n" +
      "Content-Type: application/json\r\n" +
      "Content-Length: " + post.length() + "\r\n" +
      "Connection: close\r\n\r\n"
      );
  client.println(post);

  delay(200);

  String line;
  while(client.available()){
    line = client.readStringUntil('\r');
    Serial.println(line);
  }


}
