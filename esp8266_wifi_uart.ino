#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D2, D1); // RX | TX
ESP8266WiFiMulti WiFiMulti;

const int analogInPin = A0; // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0; // value read from the port
int outputValue = 0; // value to output to a PWM pin
int rec_len = 3000000, period = 125, recordcount = 0, counting = 0,dtime;
unsigned long firstTime, prevTime, curTime;
char arr[6100];
uint8_t arr_8[25000];
int n = 0 ;
int shouldstop = 0;
String payload;

void setup() {
  // initialize serial communication at 115200
  Serial.begin(115200);
 
  mySerial.begin(9600);
  pinMode(D2, INPUT);
  pinMode(D1, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("focusss", "ffffffff");
  Serial.println("Wifi...connecting");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("\nstart record in :");
  for(int j=5; j>0; j--){
    Serial.printf("%d\n",j);
    delay(1000);
  }
  firstTime = micros();
  prevTime = firstTime;
  arr[counting++] = '{';
  arr[counting++] = '"';
  arr[counting++] = 'f';
  arr[counting++] = '"';
  arr[counting++] = ':';
  arr[counting++] = '\"';
  
  Serial.println("Start Recording");
}

void loop() {
  if(shouldstop == 0){
    // read the analog in value
    
    curTime = micros();
    dtime = curTime-prevTime;
    
    if(curTime-firstTime > rec_len || recordcount>= 24000) {
        shouldstop = 1;
        Serial.println("End Recording");
        Serial.printf("Number of record = %d\n",recordcount);

        for(int i=0;i<8;i++){
          counting = 6;
          for(int j=i*3000; j<(i+1)*3000 && j<recordcount; j++)
            addData(arr_8[j]);
          sendRequest();
        }
        //uart_send
        int write_size;
        char buf[5];
        Serial.println(payload);
        for(int i=0;i<4;i++)buf[i] = payload[i];
        buf[4]='\0';
        
        Serial.printf("[UART] begin...");
        write_size = mySerial.write(buf);
        Serial.printf("\n[UART] done length = %d...\n",write_size);
        //----------
    }
    if(dtime>=period) {
      prevTime=curTime;
      sensorValue = analogRead(analogInPin);
      
      // map it to the range of the PWM out
      arr_8[recordcount++] = map(sensorValue, 0, 1024, 0, 255);
     }
  }
}

void sendRequest(){
  Serial.println("Wifi...connecting");
   while (WiFiMulti.run() != WL_CONNECTED){delay(100);}
  Serial.println("Wifi...connected");
  
  HTTPClient http;
  
  Serial.print("[HTTP] begin...\n");
  
  http.begin("http://0a603569.ngrok.io/");
  http.addHeader("Content-Type", "application/json");
  
  Serial.print("[HTTP] POST...\n");
  arr[counting++] = '\"';
  arr[counting++] = '}';
  arr[counting++] = '\0';
//  Serial.print(arr);
  
  int httpCode = http.POST(arr);
  if (httpCode > 0) {
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
void addData(int d){
  arr[counting++] = (char)((d/10) + 97);
  arr[counting++] = ((String)(d%10))[0];
}
