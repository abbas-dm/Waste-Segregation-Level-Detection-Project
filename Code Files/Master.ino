/*======================================================================================*/
                                /*MASTER code*/
/*======================================================================================*/

/*DRY waste dustbin CODE*/
#include<SoftwareSerial.h>
#include<Servo.h>

//------------Defining pins to each sensor-----------//
#define ir 13
#define moisture 10
#define motor 7
#define trig 8 
#define echo 9
//--------------------------------------------------//

//--------Declaring instance and variables----------//
SoftwareSerial s(5, 6); // RX and TX pins
Servo myservo;
int out,out2,level;
//-------------------------------------------------//

void setup() {
  // put your setup code here, to run once:
  pinMode(ir, INPUT);
  pinMode(moisture, INPUT);
  pinMode(motor, OUTPUT);

  Serial.begin(9600);
  s.begin(9600);
  myservo.attach(motor);
  Serial.flush();
}

void irsensor(){
  out = digitalRead(ir);
}

void moisturesensor(){
  out2 = digitalRead(moisture);
}

long check_level(){
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}

void Open_door(){
  
  while(Serial.available()){
    char state = Serial.read();
    Serial.println(state);
    if(state == 'D'){
      myservo.write(-90);
      delay(3000);         // Opening the top of dustbin for 3 seconds, when it gets signal from bluetooth.
      myservo.write(180);
    }
  }
  
  irsensor();           // Reading output of ir sensor and printing it 
  moisturesensor();     // Reading output of moisture sensor and printing it
  delay(500);

  if(out == 0){
      delay(500);
      if(out2 == 0){
        Serial.write("W");    // Sending signal to wet waste dustbin
      }
      else{
        myservo.write(-90);
        delay(3000);          // Opening the top of dustbin for 3 seconds, when it detects dry waste.
        myservo.write(180);
      }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  level = 0.0173*check_level();    // Checking the level of dustbin in each iteration (in cm)  
  Open_door();
  s.write(level);
  delay(1000);
}
