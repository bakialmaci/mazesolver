#define KP 1
#define KD 5
//#include <Servo.h>
#define HIZ 30
#define encoderPinA 3
#define encoderPinB 2
#define ftrigPin 12
#define fechoPin 4
#define rtrigPin 5
#define rechoPin 6
#define ltrigPin 8
#define lechoPin 7
//Servo motor1 , motor2;
int tourA,tourB = 0;
int ilerleA,ilerleB = 0;
static int son_hata = 0;
volatile  int encoderPosA = 0;
volatile  int encoderPosB = 0;
const int Enable_A = 10;
const int Enable_B = 11;
const int inputA1 = A2;
const int inputA2 = A3;
const int inputB1 = A4;
const int inputB2 = A5;
long sure, mesafe;
void setup()
{
pinMode(encoderPinA, INPUT_PULLUP); 
pinMode(encoderPinB, INPUT_PULLUP); 
pinMode(ftrigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(fechoPin, INPUT); // Sets the echoPin as an Input
pinMode(rtrigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(rechoPin, INPUT); // Sets the echoPin as an Input
pinMode(ltrigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(lechoPin, INPUT); // Sets the echoPin as an Input
pinMode(Enable_A, OUTPUT);
pinMode(Enable_B, OUTPUT);
pinMode(inputA1, OUTPUT);
pinMode(inputA2, OUTPUT);
pinMode(inputB1, OUTPUT);
pinMode(inputB2, OUTPUT);
attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, RISING);
attachInterrupt(digitalPinToInterrupt(encoderPinB), doEncoderB, RISING);
Serial.begin(9600);
//motor1.attach(5);
//motor2.attach(6);

}

void loop() {
  ileri();
  
  /*if(encoderPosA != 3 && encoderPosB != 3){
  ileri();
  }
if(encoderPosA == 3 && encoderPosB == 3){
  kilit();
  delay(50);
}*/
/*Serial.print("encoderA: ");
Serial.println(encoderPosA);
Serial.print("encoderB: ");
Serial.println(encoderPosB);
*/Serial.print("right: ");
Serial.println(read_sensor(1));
Serial.print("left: ");
Serial.println(read_sensor(2));
Serial.print("front: ");
Serial.println(read_sensor(0));

}

int read_sensor(int select){
  int trigPin;
  int echoPin;
  if (select == 0){
    trigPin = ftrigPin;
    echoPin = fechoPin;
  }else if (select == 1){
    trigPin = rtrigPin;
    echoPin = rechoPin;
  }
  else if (select == 2){
    trigPin = ltrigPin;
    echoPin = lechoPin;
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  mesafe = (sure/2) / 29.1;
  if(mesafe > 25){
    return 25;
  }
  return mesafe;
}
int pid(int error) {
  float pidTerm;
  pidTerm = (error) * KP + (error - son_hata) * KD;
  son_hata = error;
  return (int(pidTerm));
 //Serial.println(pid(error));
}

int error(){
  return read_sensor(1) - read_sensor(2);
}
void doEncoderA(){
  encoderPosA += 1;
  if(encoderPosA == 4){
    tourA += 1;
 encoderPosA = 0;
  }
  if(tourA ==10){
    ilerleA = 1;
    tourA = 0;
 }
}
void doEncoderB(){
  encoderPosB += 1;
  if(encoderPosB == 4){
    tourB += 1;
  encoderPosB = 0;
  }
  if(tourB ==10){
    ilerleB = 1;
    tourB = 0;
 }
}
void dur(){
digitalWrite(inputA1, HIGH);
digitalWrite(inputA2, HIGH);
digitalWrite(inputB1 , HIGH);
digitalWrite(inputB2, HIGH);
analogWrite(Enable_A, 255);
analogWrite(Enable_B, 255);
}
void ileri() {
int pid_pwm = pid(error());
digitalWrite(inputA1, LOW);
digitalWrite(inputA2, HIGH);
digitalWrite(inputB1 , LOW);
digitalWrite(inputB2, HIGH);
//motor1.write(HIZ);
//motor2.write(HIZ);
analogWrite(Enable_A, HIZ + pid_pwm);
analogWrite(Enable_B, HIZ - pid_pwm);
Serial.println(HIZ + pid_pwm/5);
if(read_sensor(0) < 6){
    dur();}
  }


void kilit(){
int pid_pwm = pid(error());
digitalWrite(inputA1, HIGH);
digitalWrite(inputA2, LOW);
digitalWrite(inputB1 , HIGH);
digitalWrite(inputB2, LOW);
analogWrite(Enable_A, HIZ);
analogWrite(Enable_B, HIZ);
}
