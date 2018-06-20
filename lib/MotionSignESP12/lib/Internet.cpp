#include "Internet.h"
#include "env.h"

const unsigned long UPDATE_TIME = (unsigned long)60*1000;

const int ROOM_NUMBER = 1;

void Internet::init(){
  lastRun = 0;
  currRequest = 0;

  // We start by connecting to a WiFi network
#ifdef DEBUG_PRINT
  Serial.print("Connecting to ");
  Serial.println(SSID);
  Serial.println(PASSWORD);
#endif

  delay(200);
  WiFi.begin(SSID, PASSWORD);

  uint8_t requestCount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef DEBUG_PRINT
    Serial.print(".");
    if (requestCount++ % 25 == 0){
      Serial.print("\n");
    }
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
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
#endif

}

void Internet::run(Data &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun < UPDATE_TIME){ return; }
  lastRun = currMillis;

  WiFiClientSecure client;
  if (!client.connect(HOST, PORT)) {
#ifdef DEBUG_PRINT
    Serial.println("connection failed");
#endif
    return;
  }

  switch(currRequest){
    case GET_RESERVED: this->getReserved(data, client); break;
    case GET_DISPLAY: this->getDisplay(data,client); break;
  }
  currRequest = (currRequest+1) % REQUEST_COUNT;

}

void Internet::getDisplay(Data &data, WiFiClient &client){

#ifdef DEBUG_PRINT
  Serial.print("connecting to ");
  Serial.println(HOST);
#endif

  String url = "/prod/MotionSign?room_id=" + String(ROOM_NUMBER) + "&method_name=display";

#ifdef DEBUG_PRINT
  Serial.print("Requesting URL: ");
  Serial.println(url);
#endif

  // This will send the request to the server
  client.print(String("GET ") + url +
      " HTTP/1.1\r\n" + "Host: " + HOST + "\r\n" +
      "Content-Type: application/json\r\n" +
      "x-api-key: " + API_KEY + "\r\n" +
      "Connection: close\r\n\r\n"
      );
  delay(200);

  // Read all the lines of the reply until we get to "DATA"
  String line;
  bool found = false;
  while(client.available()){
    line = client.readStringUntil('\n');
    line.trim();
#ifdef DEBUG_PRINT
    Serial.println(line);
#endif
    if(line == String("DATA")){
      found = true;
      break;
    }
  }

  // Then send everything to data
  data.wipeScreen();

  if(found){
    while(client.available()){
      char incomingByte = client.read();
#ifdef DEBUG_PRINT
      Serial.print(incomingByte);
#endif
      data.storeChar(incomingByte);
    }
  }else{ // User last line
    uint16_t length = line.length();
    char lastByte = ' ';
    char byte = ' ';

    for(int i=0; i<length; i++){
      lastByte = byte;
      byte = line.charAt(i);
      if(byte == '"'){
        continue;
      }else if(lastByte == '\\' && byte == 'n'){
        data.storeChar('\n');
      }else if(byte != '\\'){
        data.storeChar(byte);
      }
#ifdef DEBUG_PRINT
      Serial.print(byte);
#endif
    }
  }

#ifdef DEBUG_PRINT
  Serial.println();
#endif

}

void Internet::getReserved(Data &data, WiFiClient &client){

  String occupied;
  if(data.isOccupied){
    occupied = "1";
  }else{
    occupied = "0";
  }

#ifdef DEBUG_PRINT
  Serial.print("connecting to ");
  Serial.println(HOST);
#endif

  // We now create a URI for the request
  String request = "GET /prod/MotionSign?room_id=" + String(ROOM_NUMBER) + "&amp;occupied=" + occupied +
    " HTTP/1.1\r\n" +
    "Host: " + HOST + "\r\n" +
    "x-api-key: " + API_KEY + "\r\n" +
    "Content-Type: application/json\r\n" +
    "Cache-Control: no-cache\r\n" +
    "Connection: close\r\n\r\n";

#ifdef DEBUG_PRINT
  Serial.print("REQUEST: ");
  Serial.println(request);
#endif

  // This will send the request to the server
  client.print(request);
  delay(200);

  // Read all the lines of the reply from server and print them to Serial
  String line;
  while(client.available()){
    line = client.readStringUntil('\r');
#ifdef DEBUG_PRINT
    Serial.println(line);
#endif
  }
  data.isReserved = (line.toInt() == 1);


}
