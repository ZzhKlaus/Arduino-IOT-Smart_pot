#include <SoftwareSerial.h>
//channel's thingspeak API key
String apiKey = "HHNBSOP44SPJ5IBB";
// connect 2 to TX of Serial USB
// connect 3 to RX of serial USB
SoftwareSerial ser(2,3); 

unsigned long time0;  //present time
unsigned long time1;  //field1 time
unsigned long time2;  //field2 time
unsigned long time3;  //field3 time
unsigned long time4;  //water pump time
unsigned long time5;  //speaker time

#define Temp A2
#define Pump 13
#define Moisture A3 

const int read = A5; //Sensor A1 pin to Arduino pin A1 
#define DO 4       
#define Speaker 5
double temp,data; 

char str[]="Mois:";
char con[]="WL:";
char con1[]="WL: 0mm - Empty!";
char con2[]="WL: 0mm to 5mm";
char con3[]="WL: 5mm to 10mm";
char con4[]="WL: 10mm to 15mm";
char con5[]="WL: 15mm to 20mm";
char con6[]="WL: 20mm to 25mm";
char con7[]="WL: 25mm to 30mm";
char con8[]="WL: 30mm to 35mm";
char con9[]="WL: 35mm to 40mm";

int LCD1602_RS=12;   
int LCD1602_RW=11;   
int LCD1602_EN=10;
int DB[] = { 6, 7, 8, 9};

// this runs once
void setup() {                
  // enable debug serial
  Serial.begin(115200); 
  // enable software serial
  ser.begin(115200);
  // reset ESP8266
  ser.println("AT+RST");
  
   pinMode(Pump,OUTPUT);  //PUMP
   pinMode(Speaker,OUTPUT);  
  digitalWrite(Pump,LOW);
  digitalWrite(Speaker,LOW);
  
   int i = 0;
  for (i=6; i <= 12; i++) 
   {
     pinMode(i,OUTPUT);
   }

   delay(100);
    LCD_Command_Write(0x28);//2row 5x7
    delay(50); 
    LCD_Command_Write(0x06);
    delay(50); 
    LCD_Command_Write(0x0c);
    delay(50); 
    LCD_Command_Write(0x80);
    delay(50); 
    LCD_Command_Write(0x01);
    delay(50); 
}

// the loop 
void loop() {
  float val;  //
  float dat;  //centigrade
  float data; //water level _transformed
  float value; // water level
  float humid; // moisture
  
  val=analogRead(A2);
  dat=val*0.488;    //centigrade
  Serial.print(dat);
  Serial.println(" centigrade");

   Serial.print("Moisture=");   
   humid = 1024 - analogRead(Moisture);
   Serial.print(humid);  
   Serial.print("|DO=");  
   Serial.println(digitalRead(DO));  
   Serial.print("\n");
   
    value = analogRead(read); //Read data from analog pin and store it to value variable
    data = (value/650)*4;
    Serial.println(data);
    if(data <=1) data = data / 2;
    else if(data <=1.5) data = data *0.67;
    else if(data <=1.9) data = data *0.79;
    else if(data <=2.4) data = data *0.88;
    else if(data <=2.7) data = data *0.96;
    else if(data <=2.9) data = data *1.03;
    else if(data <=3.1) data = data *1.08;
    else if(data <=3.4) data = data * 1.21;
    Serial.print("Water level: "); 
    Serial.print(data);
    Serial.println(" cm");
    delay(1000);
    
controlSpeaker(data);
pumpWater(humid);
esp_8266_filed1(dat);
esp_8266_filed2(humid);
esp_8266_filed3(data);
}

void esp_8266_filed1(float a)    //centi  moisture water_level 
{
  time0 = millis();
  if(time0 - time1 >= 15000){
    time1 = time0;
    }
   else{
    return;
    }
 // convert to string
  char buf[32];
  String strVolt = dtostrf( a, 2, 1, buf);
  Serial.print(a);
  Serial.println(" Centigrade");
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149";      // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
   
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
//strVrepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(strVolt);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  } 
}

void esp_8266_filed2(float a)    //centi  moisture water_level 
{
  time0 = millis();
  if(time0 - time2 >= 15000){
    time2 = time0;
    }
  else{
   return;
   }
     
 // convert to string
  char buf[32];
  String strVolt = dtostrf( a, 2, 1, buf);
  Serial.print(a);
  Serial.println(" Moisture");
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
   
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
//strVrepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field2=";
  getStr += String(strVolt);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
 
}
   //hingspeak needs 15 sec delay between updates
   
void esp_8266_filed3(float a)    //centi  moisture water_level 
{
  time0 = millis();
  if(time0 - time3 >= 15000){
    time3 = time0;
    }
  else{
   return;
   }
 // convert to string
  char buf[32];
  String strVolt = dtostrf( a, 2, 1, buf);
  Serial.print(a);
  Serial.println(" mm");
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
   
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
//strVrepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field3=";
  getStr += String(strVolt);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
}


void LCD_Command_Write(int command)
{
 int i,temp;
 digitalWrite( LCD1602_RS,LOW);
 digitalWrite( LCD1602_RW,LOW);
 digitalWrite( LCD1602_EN,LOW);
 
 temp=command & 0xf0;
 for (i=DB[0]; i <= 9; i++)
 {
   digitalWrite(i,temp & 0x80);
   temp <<= 1;
 }
 
 digitalWrite( LCD1602_EN,HIGH);
 delayMicroseconds(1);
 digitalWrite( LCD1602_EN,LOW);
 
 temp=(command & 0x0f)<<4;
 for (i=DB[0]; i <= 9; i++)
 {
   digitalWrite(i,temp & 0x80);
   temp <<= 1;
 }
 
 digitalWrite( LCD1602_EN,HIGH);
 delayMicroseconds(1); 
 digitalWrite( LCD1602_EN,LOW);
}
 
void LCD_Data_Write(int dat)
{
 int i=0,temp;
 digitalWrite( LCD1602_RS,HIGH);
 digitalWrite( LCD1602_RW,LOW);
 digitalWrite( LCD1602_EN,LOW);
 
 temp=dat & 0xf0;
 for (i=DB[0]; i <= 9; i++)
 {
   digitalWrite(i,temp & 0x80);
   temp <<= 1;
 }
 
 digitalWrite( LCD1602_EN,HIGH);
 delayMicroseconds(1);
 digitalWrite( LCD1602_EN,LOW);
 
 temp=(dat & 0x0f)<<4;
 for (i=DB[0]; i <= 9; i++)
 {
   digitalWrite(i,temp & 0x80);
   temp <<= 1;
 }
 
 digitalWrite( LCD1602_EN,HIGH);
 delayMicroseconds(1); 
 digitalWrite( LCD1602_EN,LOW);
}
 
void LCD_SET_XY( int x, int y )
{
  int address;
  if (y ==0)    address = 0x80 + x;
  else          address = 0xC0 + x;
  LCD_Command_Write(address); 
}
 
void LCD_Write_Char( int x,int y,int dat)
{
  LCD_SET_XY( x, y ); 
  LCD_Data_Write(dat);
}
 
void LCD_Write_String(int X,int Y,char *s)
{
    LCD_SET_XY( X, Y );    //设置地址 
    while (*s)             //写字符串
    {
      LCD_Data_Write(*s);   
      s ++;
    }
}

void pumpWater(float a)
{
  time0 = millis();
  if(time0 - time4 >= 10000){
    time4 = time0;
    }
  else{
    return;
   }
  if(int(a) < 251) //moisture
  { 
    Serial.println("No water in soil!");
    digitalWrite(13,HIGH);
    delay(2500);
    digitalWrite(13,LOW);
  }
}

void controlSpeaker( float wLevel)
{
  time0 = millis();
  if(time0 - time5 >= 10000){
    time5 = time0;
    }
  else{
    return;
   }
if(wLevel <= 0.5){
   Serial.println("Add water!");
    digitalWrite(5,HIGH);
    delay(4000);
    digitalWrite(5,LOW);
}
}

