#define trigPinf A0
#define echoPinf A1
#define trigPinr A2
#define echoPinr A3
#define trigPinl A4
#define echoPinl A5

                                                                                                             
//MOTOR A 
int enA = 5;
int in1 = 6;
int in2 = 7;

// Motor B

int enB = 10;
int in3 = 8;
int in4 = 9;


void setup() {
  // put your setup code here, to run once:
  pinMode(trigPinf,OUTPUT);
  pinMode(echoPinf,INPUT);
  pinMode(trigPinr,OUTPUT);
  pinMode(echoPinr,INPUT);
  pinMode(trigPinl,OUTPUT);
  pinMode(echoPinl,INPUT);
  pinMode(in3, OUTPUT);  //make initially all pins as output
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin (9600);
}

float frontdist(){
  float gapf;
  float ticktockf;
  digitalWrite(trigPinf,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinf,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinf,LOW);
  ticktockf=pulseIn(echoPinf,HIGH);
  gapf=ticktockf*0.0344/2;
  return gapf;
}

float rightdist(){
  float gapr;
  float ticktockr;
  digitalWrite(trigPinr,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinr,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinr,LOW);
  ticktockr=pulseIn(echoPinr,HIGH);
  gapr=ticktockr*0.0344/2;
  return gapr;
}

float leftdist(){
  float gapl;
  float ticktockl;
  digitalWrite(trigPinl,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinl,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinl,LOW);
  ticktockl=pulseIn(echoPinl,HIGH);
  gapl=ticktockl*0.0344/2;
  return gapl;  
}

float printmedian(float fp[20]){
  float mf,t;
  for (int i = 1 ; i <= 19 ; i++){
   for (int j = 1 ; j <= 20-i ; j++){
      if (fp[j] <= fp[j+1]){
         t = fp[j];
         fp[j] = fp[j+1];
         fp[j+1] = t;
      } else
      continue ;
   }
 }

   mf = (fp[10] + fp[11])/2.0 ;
 Serial.println(mf);
 return mf;
}

void moveStop(){  //stop motors 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
//  delay(30);
 Serial.println("stop");
}

void moveForward(){
    digitalWrite(in1, HIGH);
    digitalWrite(in3, HIGH);
    analogWrite(enA, 255); //the speed left
    
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enB, 255); //the speed  right
Serial.println("forward");
        delay(400);
}

void moveBackward(){
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 255); //the speed
  
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  analogWrite(enB, 255); //the speed
Serial.println("backward");
  delay(200);
}

void turnRight(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    

    analogWrite(enA, 255); //the speed
    analogWrite(enB, 100); //the speed  
Serial.println("slight right");
     delay(250);      
}

void turnLeft(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
   
    analogWrite(enA, 90);
    analogWrite(enB, 255);
Serial.println("slightleft");
        delay(150);
      
} 


void moveFwdslight(){
  
    digitalWrite(in1, HIGH);
    digitalWrite(in3, HIGH);
    analogWrite(enA, 255); //the speed left
    
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enB, 255); //the speed  right
Serial.println("slight forward");
  delay(150);
}
void uturn(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
   
    analogWrite(enA, 255);
    analogWrite(enB, 255);
Serial.println("uturn");
    delay(500); 
}

void exec(){
    float f[20], l[20], r[20], fm, lm, rm;

  for(int i=0;i<20;i++){
    f[i]=frontdist();
    delay(10);
  }
  for(int i=0;i<20;i++){
    l[i]=leftdist();
    delay(10);
  }
  
  for(int i=0;i<20;i++){
    r[i]=rightdist();
    delay(10);
  }
  fm = printmedian(f);
  lm = printmedian(l);
  rm = printmedian(r);   


    Serial.println("front distance");
    Serial.println(fm);
    Serial.println("left distance");
    Serial.println(lm);
    Serial.println("right distance");
    Serial.println(rm);



   if((lm>10)&&(fm>15)){
    turnLeft();
    moveFwdslight();
    moveStop();
    return;
   }
   else if((lm>8)&&(lm<14)&&(fm>15)){
    moveForward();
    moveStop();
    return;
   }
   else if((lm<9)&&(fm>15)){
    turnRight();
    moveFwdslight();
    moveStop();
    return;
   }

   else if(fm<15){
    moveBackward();
    moveBackward();
    moveBackward();
    moveStop();
    turnRight();
    moveFwdslight();
    turnRight();
    moveFwdslight();
    turnRight();
    turnRight();
    turnRight();
    moveFwdslight();
    moveStop();
    return;
   }

   else
   return;
}

void loop() {
  // put your main code here, to run repeatedly:
for(float i=0; i<99999; i=i+0.0001){
//while(1){
exec();
} 
}

