#define KP 10 
#define KD 10
#define ftrigPin 11
#define fechoPin 12
#define rtrigPin 5
#define rechoPin 6

#define ltrigPin 8
#define lechoPin 7

#define HIZ 100
static int son_hata = 0;
const int Enable_A = 9;
const int Enable_B = 10;
const int inputA1 = A2;
const int inputA2 = A3;
const int inputB1 = A4;
const int inputB2 = A5;

long sure, mesafe;

int c[5][5] = {{0, 0,99, 99, 0},
              {0, 0, 0, 99, 0},
              {0, 0,99,99, 0},
              {0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0}
};

void setup()
{
pinMode(ftrigPin, OUTPUT);
pinMode(fechoPin, INPUT);
pinMode(rtrigPin, OUTPUT);
pinMode(rechoPin, INPUT);
pinMode(ltrigPin, OUTPUT);
pinMode(lechoPin, INPUT);
pinMode(Enable_A, OUTPUT);
pinMode(Enable_B, OUTPUT);
pinMode(inputA1, OUTPUT);
pinMode(inputA2, OUTPUT);
pinMode(inputB1, OUTPUT);
pinMode(inputB2, OUTPUT);
Serial.begin(9600);

}

void loop()
{
  ileri();
Serial.print("right: ");
Serial.println(read_sensor(1));
Serial.print("left: ");
Serial.println(read_sensor(2));
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
  return mesafe;
}

int pid(int error) {
  float pidTerm;
  pidTerm = (error) * KP + (error - son_hata) * KD;
  son_hata = error;
  return (int(pidTerm));
}

int error(){
  return read_sensor(1) - read_sensor(2);
}

 
void ileri() {
int pid_pwm = pid(error());
digitalWrite(inputA1, LOW);
digitalWrite(inputA2, HIGH);
digitalWrite(inputB1 , LOW);
digitalWrite(inputB2, HIGH);
analogWrite(Enable_A, HIZ-pid_pwm);
analogWrite(Enable_B, HIZ+pid_pwm);

}
void dur(){
   digitalWrite(inputA1, HIGH);
digitalWrite(inputA2, HIGH);
digitalWrite(inputB1 , HIGH);
digitalWrite(inputB2, HIGH);
}

//void sag(){
//digitalWrite(inputA1, HIGH);
//digitalWrite(inputA2, LOW);
//digitalWrite(inputB1 , LOW);   
//digitalWrite(inputB2, HIGH);
//analogWrite(Enable_A, HIZ);
//analogWrite(Enable_B, HIZ);
//}
//
//void sol(){
//  
//digitalWrite(inputA1, LOW);
//digitalWrite(inputA2, HIGH);
//digitalWrite(inputB1 , HIGH);
//digitalWrite(inputB2, LOW);
//analogWrite(Enable_A, HIZ);
//analogWrite(Enable_B, HIZ);
//}
