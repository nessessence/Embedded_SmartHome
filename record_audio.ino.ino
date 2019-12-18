const int analogInPin = A0; // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0; // value read from the port
int outputValue = 0; // value to output to a PWM pin
int i = 0, rec_len = 6000000, period = 125, recordcount=0;
unsigned long firstTime,prevTime,curTime;
uint8_t arr[50000];
int n = 0 ;

void setup() {
// initialize serial communication at 115200
Serial.begin(115200);
Serial.println("start record in :");
for(int j=5; j>0; j--){
Serial.printf("%d\n",j);
delay(1000);
}
firstTime = micros();
prevTime = firstTime;
Serial.println("Start Recording");

}

void loop() {
// read the analog in value
curTime = micros();
int dtime = curTime-prevTime;
//Serial.println(xtime);
if(curTime-firstTime > rec_len) {
if(n==0){
Serial.println("End Recording");
Serial.printf("Number of record = %d\n",recordcount);
Serial.println("raw data:");
}
if(n < recordcount){
Serial.printf("%d ",arr[n++]);
if(n%1000==0) Serial.println();
}
return;
}
if(dtime>period)
  {
  prevTime=curTime;
  sensorValue = analogRead(analogInPin);
  // map it to the range of the PWM out
  outputValue = map(sensorValue, 0, 1024, 0, 255);
  arr[recordcount++] = outputValue;

  }
}
void standby(){
Serial.println("start record in :");
for(int j=5; j>0; j--){
  Serial.printf("%d\n",j);
delay(1000);
}
return;
}
void read_sound(){



return;
}
