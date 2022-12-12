int i=55;
int a=110;
int port=3;
void setup() {
  // put your setup code here, to run once:
pinMode(port,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

while(i>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
i--;
}
i=55;

digitalWrite(port,LOW);
delayMicroseconds(880);

while(a>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
a--;
}
a=110;

digitalWrite(port,LOW);
delayMicroseconds(880);

while(i>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
i--;
}
i=55; 

digitalWrite(port,LOW);
delayMicroseconds(880);

while(i>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
i--;
}
i=55; 

digitalWrite(port,LOW);
delayMicroseconds(1750);

while(a>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
a--;
}
a=110;

digitalWrite(port,LOW);
delayMicroseconds(880);

while(i>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
i--;
}
i=55;

digitalWrite(port,LOW);
delayMicroseconds(880);

while(i>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
i--;
}
i=55;

digitalWrite(port,LOW);
delayMicroseconds(1750);

while(i>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
i--;
}
i=55; 

digitalWrite(port,LOW);
delayMicroseconds(880);

while(i>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
i--;
}
i=55;

digitalWrite(port,LOW);
delayMicroseconds(880);

while(a>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
a--;
}
a=110;

digitalWrite(port,LOW);
delayMicroseconds(880);

while(i>=0){
digitalWrite(port,HIGH);
delayMicroseconds(16);
digitalWrite(port,LOW);
delayMicroseconds(16);
i--;
}
i=55;

digitalWrite(port,LOW);
delay(91);
}
