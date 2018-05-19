
int pinRelay = 3;

void setup(){
  pinMode(pinRelay,OUTPUT);
}

void loop(){
  digitalWrite(pinRelay,HIGH);
  delay(1000);

  digitalWrite(pinRelay,LOW);
  delay(1000);
}
/*
int pinRelay = 3; //管脚D3连接到继电器模块的信号脚  
  
void setup() {  
  pinMode(pinRelay, OUTPUT); //设置pinRelay脚为输出状态  
}  
  
void loop() {   
   digitalWrite(pinRelay, HIGH);//输出HIGH电平,继电器模块闭合  
   delay(5000); //等待5000毫秒  

   digitalWrite (pinRelay, LOW); //输出LOW电平,继电器模块断开  
   delay(8000); //等待8000毫秒  
}*/
