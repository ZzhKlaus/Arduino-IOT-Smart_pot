#define Temp A2
#define Pump 13
double temp,data; //water level
const int read = A0; //Sensor A1 pin to Arduino pin A1 , water level
int value;          //Variable to store the incomming data
#define Moisture A1 //define pin AO as IO-A0  
#define DO 4 //7        //define pin DO as IO-7  LCD D7

char str[]="Mois:";
char con[]="WL:";

int LCD1602_RS=12;   
int LCD1602_RW=11;   
int LCD1602_EN=10;   
int DB[] = { 6, 7, 8, 9};
 char str1[]="Mois:";
char con1[]="WL: 0mm - Empty!";
char con2[]="WL: 0mm to 5mm";
char con3[]="WL: 5mm to 10mm";
char con4[]="WL: 10mm to 15mm";
char con5[]="WL: 15mm to 20mm";
char con6[]="WL: 20mm to 25mm";
char con7[]="WL: 25mm to 30mm";
char con8[]="WL: 30mm to 35mm";
char con9[]="WL: 35mm to 40mm";

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
    LCD_SET_XY( X, Y );    //set the address 
    while (*s)             //write the characters
    {
      LCD_Data_Write(*s);   
      s ++;
    }
}


 
void setup (void) 
{
  Serial.begin(9600);
  //pinMode(A1, INPUT);//set A1 as INPUT mode
  //pinMode(A0, INPUT);//set A0 as INPUT mode
  pinMode(Temp,OUTPUT);
  pinMode(Pump,OUTPUT);
  
  int i = 0;
  for (i=6; i <= 12; i++) 
   {
     pinMode(i,OUTPUT);
   }
  delay(100);
  LCD_Command_Write(0x28);// 5x7
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
 
void loop (void)
{
  int val;
  int dat;
  val=analogRead(A2);
  dat=val*0.488;
  Serial.print(dat);
  Serial.println(" centigrade");

   Serial.print("Moisture=");  
   Serial.print(analogRead(Moisture));
   Serial.print("|DO=");  
   Serial.println(digitalRead(DO)); 
   Serial.print("\n");

   value = analogRead(read); //Read data from analog pin and store it to value variable
  
  if (value <= 480){ 
    Serial.println("Water level: 0mm - Empty!"); 
  }
  else if (value>480 && value<=530){ 
    Serial.println("Water level: 0mm to 5mm"); 
  }
  else if (value>530 && value<=615){ 
    Serial.println("Water level: 5mm to 10mm"); 
  }
  else if (value>615 && value<=660){ 
    Serial.println("Water level: 10mm to 15mm"); 
  } 
  else if (value>660 && value<=680){ 
    Serial.println("Water level: 15mm to 20mm"); 
  }
  else if (value>680 && value<=690){ 
    Serial.println("Water level: 20mm to 25mm"); 
  }
  else if (value>690 && value<=700){ 
    Serial.println("Water level: 25mm to 30mm"); 
  }
  else if (value>700 && value<=705){ 
    Serial.println("Water level: 30mm to 35mm"); 
  }
  else if (value>705){ 
    Serial.println("Water level: 35mm to 40mm"); 
  }
  delay(1000);
  /*value = analogRead(read); //Read data from analog pin and store it to value variable
  temp=(long)analogRead(1);
  data=(temp/650)*4;
  Serial.print("the depth is:");
  Serial.print(data);
  Serial.println("cm");
  delay(1000);*/
  
  char d[100];
  dtostrf(data,1,2,d);   //jiang float/double data transfer to char
  
   char c[100];  
   int moi = analogRead(Moisture);
   float a = float(moi/1024);
   //itoa(analogRead(Moisture), c, 10);
   dtostrf(a,2,1,c);
   
   LCD_Command_Write(0x01);
   delay(50);
   LCD_Write_String(0,0,str);
   delay(50);
   LCD_Write_String(5,0,c);
   delay(50);
   LCD_Write_String(0,1,con);
   delay(50);
   LCD_Write_String(3,1,d);
   delay(5000);
  */
 
}
