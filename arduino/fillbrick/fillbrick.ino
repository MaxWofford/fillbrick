#include <SPI.h>
#include <Ethernet.h>

// Mac address
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x12, 0x93 };

// URL
const char server[] = "3bed3e09.ngrok.io";

// GET Request
const char getReq[] = "GET /data HTTP/1.1";

// Default IP Adress
IPAddress ip(129, 21, 50, 69);

//Pin connected to ST_CP of 74HC595
const int LATCHPIN = 12;
//Pin connected to SH_CP of 74HC595
const int CLOCKPIN = 11;
// Pin connected to DS of 74HC595
const int DATAPIN = 13;
// Number of pins
const int BOARDHEIGHT = 5;
// Delay
const int DELAY = 200;
// Min Time between connections 
const unsigned long DISPLAY_BREAK_TIME = 40L*DELAY;

// The content length string used in parse responses
const char *CONTENT_LENGTH_STRING = "Content-Length:";
const int CONTENT_LENGTH_STRING_LENGTH = 15;

// The data length string used in parse responses
const char *LENGTH_FIELD = "\"length\":";
const int LENGTH_FIELD_LENGTH = 9;


// The data string used in parse responses
const char *DATA_FIELD = "\"bytes\":";
const int DATA_FIELD_LENGTH = 8;

const int CHARACTER_WIDTH = 4;
const char ch_lookup[] = // Every 4 indeces corresponds to the ascii lookup
{
// 0x00
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x00, 0x00, 0x00, // Null
// 0x20
  0x00, 0x00, 0x00, 0x00, // Null
  0x00, 0x17, 0x00, 0x00, // !
  0x03, 0x00, 0x03, 0x00, // "
  0x1F, 0x0A, 0x1F, 0x0A, // #
  0x12, 0x1F, 0x09, 0x00, // $
  0x19, 0x04, 0x13, 0x00, // %
  0x1F, 0x1F, 0x1F, 0x1F, // Don't use ampersand.
  0x00, 0x03, 0x00, 0x00, // '
  0x0E, 0x11, 0x00, 0x00, // (
  0x00, 0x11, 0x0E, 0x00, // )
  0x05, 0x02, 0x05, 0x00, // *
  0x04, 0x0E, 0x04, 0x00, // + 
  0x00, 0x10, 0x08, 0x00, // ,
  0x04, 0x04, 0x04, 0x00, // - 
  0x00, 0x10, 0x00, 0x00, // .
  0x18, 0x04, 0x03, 0x00, // /
  0x0E, 0x11, 0x0E, 0x00, // 0
  0x12, 0x1F, 0x10, 0x00, // 1
  0x11, 0x15, 0x12, 0x00, // 2
  0x15, 0x15, 0x0A, 0x00, // 3
  0x07, 0x04, 0x1F, 0x00, // 4
  0x17, 0x05, 0x1D, 0x00, // 5
  0x1F, 0x15, 0x17, 0x00, // 6
  0x01, 0x01, 0x1F, 0x00, // 7
  0x1F, 0x15, 0x1F, 0x00, // 8
  0x17, 0x15, 0x1F, 0x00, // 9 
  0x00, 0x0A, 0x00, 0x00, // :
  0x10, 0x0A, 0x00, 0x00, // ;
  0x04, 0x0A, 0x11, 0x00, // <
  0x0A, 0x0A, 0x0A, 0x00, // = 
  0x11, 0x0A, 0x04, 0x00, // > 
  0x01, 0x15, 0x02, 0x00, // ?
  
// 0x40
  0x0E, 0x17, 0x0E, 0x0A, // @ Don't use the at.
  0x1E, 0x05, 0x1E, 0x01, // A
  0x1F, 0x15, 0x0A, 0x00, // B
  0x0E, 0x11, 0x11, 0x00, // C
  0x1F, 0x11, 0x0E, 0x00, // D
  0x1F, 0x15, 0x15, 0x00, // E
  0x1F, 0x05, 0x05, 0x00, // F
  0x1F, 0x11, 0x1D, 0x00, // G
  0x1F, 0x04, 0x1F, 0x00, // H
  0x11, 0x1F, 0x11, 0x00, // I
  0x09, 0x11, 0x0F, 0x00, // J
  0x1F, 0x04, 0x1B, 0x00, // K
  0x1F, 0x10, 0x10, 0x00, // L
  0x1F, 0x06, 0x1F, 0x00, // M
  0x1F, 0x01, 0x1F, 0x00, // N
  0x0E, 0x11, 0x0E, 0x00, // O
  0x1F, 0x05, 0x02, 0x00, // P
  0x0E, 0x19, 0x1E, 0x00, // Q
  0x1F, 0x05, 0x1A, 0x00, // R
  0x12, 0x15, 0x09, 0x00, // S
  0x01, 0x1F, 0x01, 0x00, // T
  0x1F, 0x10, 0x1F, 0x00, // U
  0x0F, 0x10, 0x0F, 0x00, // V
  0x1F, 0x1C, 0x1F, 0x00, // W
  0x1B, 0x04, 0x1B, 0x00, // X
  0x03, 0x1C, 0x03, 0x00, // Y
  0x19, 0x15, 0x13, 0x00, // Z
  0x1F, 0x11, 0x11, 0x00, // [
  0x03, 0x04, 0x18, 0x00, // backslash
  0x11, 0x11, 0x1F, 0x00, // ]
  0x02, 0x01, 0x02, 0x00, // ^
  0x10, 0x10, 0x10, 0x00, // _
  
// 0x60
  0x00, 0x01, 0x02, 0x00, // `
  0x1E, 0x05, 0x1E, 0x00, // A (lowercase start)
  0x1F, 0x15, 0x0A, 0x00, // B
  0x0E, 0x11, 0x11, 0x00, // C
  0x1F, 0x11, 0x0E, 0x00, // D
  0x1F, 0x15, 0x15, 0x00, // E
  0x1F, 0x05, 0x05, 0x00, // F
  0x1F, 0x11, 0x1D, 0x00, // G
  0x1F, 0x04, 0x1F, 0x00, // H
  0x11, 0x1F, 0x11, 0x00, // I
  0x09, 0x11, 0x0F, 0x00, // J
  0x1F, 0x04, 0x1B, 0x00, // K
  0x1F, 0x10, 0x10, 0x00, // L
  0x1F, 0x06, 0x1F, 0x00, // M
  0x1F, 0x01, 0x1F, 0x00, // N
  0x0E, 0x11, 0x0E, 0x00, // O
  0x1F, 0x05, 0x02, 0x00, // P
  0x0E, 0x19, 0x1E, 0x00, // Q
  0x1F, 0x05, 0x1A, 0x00, // R
  0x12, 0x15, 0x09, 0x00, // S
  0x01, 0x1F, 0x01, 0x00, // T
  0x1F, 0x10, 0x1F, 0x00, // U
  0x0F, 0x10, 0x0F, 0x00, // V
  0x1F, 0x1C, 0x1F, 0x00, // W
  0x1B, 0x04, 0x1B, 0x00, // X
  0x03, 0x1C, 0x03, 0x00, // Y
  0x19, 0x15, 0x13, 0x00, // Z (lowercase end)
  0x0A, 0x15, 0x11, 0x00, // {
  0x00, 0x1B, 0x00, 0x00, // |
  0x11, 0x15, 0x0A, 0x00, // }
  0x02, 0x01, 0x02, 0x01, // ~
  0x00, 0x00, 0x00, 0x00
};

// Client used for connections
EthernetClient client;

// Last time display to client
unsigned long lastDisplayTime = 0;

// All the current data
byte* data;
int dataLength;

void diagonalLines() {
  // count from 1 (0x00001) to 32 (0x10000)
  // note: the furthest right pin is disconnected; drop the right most digit in binary
  for (byte a = 1; a < 8; a++) {
    // sendData(a);
    shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, a);
    delay(DELAY);
  }
}

byte* stringToBytes(const char* s, int sLength){
  byte* tempy = new byte[sLength*CHARACTER_WIDTH];
  for(int a = 0; a < sLength; a++)
  {
    int ascii = s[a];
    for(int b = 0; b < CHARACTER_WIDTH ; b++)
    {
      tempy[(sLength-1-a)*CHARACTER_WIDTH+(CHARACTER_WIDTH-1-b)] = ch_lookup[ascii*CHARACTER_WIDTH+b];
    }
  }
  return tempy;
}

void setupServer(){

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  
  // give the Ethernet shield a second to initialize and then update data orginally
  delay(1000);
  Serial.println("Web connected!");
  updateData(true);
}

// updates the data from the database
void updateData(bool first) {

  // If not first connection wait for data from server, processes data, and close connection.
  if(!first){
    client.stop();
  }

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    
    // send the HTTP GET request:
    client.println(getReq);
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // Get the data from the client
    getCurrentData(first);
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

void getCurrentData(bool first){
  // Get the body of the current response
  while(client.connected() && !client.available());
    int contentLength = 0;
    char* body;
    while(client.available()){
      char c = client.read();
      if(contentLength==0){
        bool found = true;
        if(c==CONTENT_LENGTH_STRING[0]){
          for(int i=1;i<CONTENT_LENGTH_STRING_LENGTH && found;i++)
            if((c=client.read())!=CONTENT_LENGTH_STRING[i])
              found = false;
        }
        else
          found = false;
        if(found){
          while((c = client.read())!='\n')
            if((c-'0')>=0 && (c-'0')<10)
              contentLength = contentLength*10+(c-'0');
        }
      }
      else{
        if(c<=32){
          body = new char[contentLength+1];
          c = client.read();
          for(int i=0;i<contentLength;i++, c = client.read())
            body[i] = c;
          body[contentLength] = 0;
          break;
        }
      }
      while(c!='\n' && c!=-1)
        c = client.read();
    }Serial.println(body);

    // Get the length of the new data
    dataLength = 0;
    for(int i=0;i<contentLength;i++){
      
      // skip escaped characters
      while(body[i]=='\\')
        i+=2;

      // Find where length is and grab it
      bool found = true;
      if(body[i]==',' || body[i]=='{'){
        for(int j=0;j<LENGTH_FIELD_LENGTH && found;j++)
          if(body[i+j+1]!=LENGTH_FIELD[j])
            found = false;
      }
      else
        found = false;
      if(found){
        for(int j=i+LENGTH_FIELD_LENGTH+1;body[j]>=32 && body[j]!=',' && body[j]!='}';j++)
          if((body[j]-'0')>=0 && (body[j]-'0')<10)
            dataLength = dataLength*10+(body[j]-'0');
        break;
      }
    }Serial.println(dataLength);

    // Reset the data array to empty with the new size
    if(!first)
      free(data);
    data = new byte[dataLength];


    // Get all the data from the body
    int curData = 0;
    for(int i=0;i<contentLength;i++){
       // Find where the bytes are and grab them
      bool found = true;
      if(body[i]==',' || body[i]=='{'){
        for(int j=0;j<DATA_FIELD_LENGTH && found;j++)
          if(body[i+j+1]!=DATA_FIELD[j])
            found = false;
      }
      else
        found = false;
      if(found){
        for(int j=i+DATA_FIELD_LENGTH+2;body[j]!=']' && body[j+1]>=32;j++){
          if(body[j]=='\"'){
            j++;
            int k = j;
            for(;body[j]!='\"';j++){
              // skip esacped characters and quoted text
              while(body[j]=='\\')
                j+=2;
              while(body[j]=='\"'){
                while(body[j]!='\"'){
                  j++;
                  while(body[j]=='\\')
                    j+=2;
                }
              }
            }
            k = j-k;
            char* newString = new char[k];
            newString[k-1] = 0;
            for(int l=0;l<k-1;l++)
              newString[l] = data[j+l];
            byte* newData = stringToBytes(newString, k);
            for(int l=0;l<(k-1)*CHARACTER_WIDTH;l++)
              data[curData++] = newData[l];
            free(newString);
            free(newData);
          }
          else{
            int newData = 0;
            for(;body[j]!=',' && body[j]!=']';j++)
              if((body[j]-'0')>=0 && (body[j]-'0')<10)
                newData = newData*10+(body[j]-'0');
            data[curData++] = newData;
          }
        }
        break;
      }
    }
    for(int i=0;i<dataLength;i++)
      Serial.println(data[i]);
}

void setup() {
  setupServer();
  pinMode(LATCHPIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(DATAPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(millis() - lastDisplayTime > DISPLAY_BREAK_TIME){
    updateData(false);
    for(int a = 0 ; a < dataLength; a++)
    {
      digitalWrite(LATCHPIN, LOW);
      shiftOut(DATAPIN, CLOCKPIN, LSBFIRST, data[a] << 2);
      Serial.print(a);
      digitalWrite(LATCHPIN, HIGH);
      delay(DELAY);
    }
    lastDisplayTime = millis();
  }
}
