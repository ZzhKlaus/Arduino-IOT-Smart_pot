double temp,data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp=(long)analogRead(5);
  data=(temp/650)*4;
  Serial.print("the depth is:");
  Serial.print(data);
  Serial.println("cm");
  delay(1000);
}
/*
0.5 1
1 1.5
1.5 1.9
2 2.4
2.5 2.7
3 2.9
3.5 3.1
4 3.3*/



