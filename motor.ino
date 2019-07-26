
#include <Wire.h>

const int stepPin2 = 7;
const int dirPin2 = 6;
const int enPin2 = 5;
const int stepPin = 10;
const int dirPin = 9;
const int enPin = 8;
int valoarebuton = 1;
int valoarebuton2 = 1;
int dist = 932;
int distantadintredoz=527;
int H=HIGH;
int x1;


void setup() {
  Wire.begin(8);                
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);           

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, HIGH);

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  pinMode(enPin2, OUTPUT);
  digitalWrite(enPin2, HIGH);

  pinMode(4, INPUT);
  pinMode(3, INPUT);

  Calibrare();
}

void unudoz()
{

  digitalWrite(enPin, LOW);

  digitalWrite(dirPin, H); 
  for (int x = 0; x < dist; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

  digitalWrite(enPin, HIGH);


}
void doz()

{
  digitalWrite(enPin, LOW);

  digitalWrite(dirPin, H); 
  for (int x = 0; x < dist + distantadintredoz; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

  digitalWrite(enPin, HIGH);


}


void apas()
{
  digitalWrite(enPin2, LOW);
  delay(200);
  digitalWrite(dirPin2, LOW); 

  for (int x = 0; x < 700; x++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(4000);
  digitalWrite(dirPin2, HIGH);

  while (valoarebuton2)
  {
    valoarebuton2 = digitalRead(3);

    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(500);
  digitalWrite(dirPin2, LOW);

  for (int z = 1; z <= 50; z++)
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }

  digitalWrite(enPin2, HIGH);
  valoarebuton2 = 1;
}


void Calibrare()
{
  Serial.println("MOTOR");
  digitalWrite(enPin2, LOW);

  digitalWrite(dirPin2, HIGH); 
  while (valoarebuton2) {
    valoarebuton2 = digitalRead(3);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(250);

  digitalWrite(dirPin2, LOW);

  for (int z = 1; z <= 50; z++)
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }

  digitalWrite(enPin2, HIGH);
  valoarebuton2 = 1;

  digitalWrite(enPin, LOW);

  digitalWrite(dirPin, LOW); 
  while (valoarebuton) {
    valoarebuton = digitalRead(4);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(500);


  digitalWrite(dirPin, HIGH); 
  while (valoarebuton == 0)
  {
    valoarebuton = digitalRead(4);

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin, HIGH);
  for (int x = 0; x < 700; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(enPin, HIGH);
  valoarebuton = 1;
}
void timp()
{
  Wire.beginTransmission(8); 
  Wire.write(2);
  Wire.endTransmission(8);
}

void motor1()
{
  Serial.println("MOTOR");
  H=HIGH;
  Calibrare();
  delay(10);
  unudoz();
  apas();
      dist = 0;
  doz();
  doz();
  doz();
  apas();
  doz();
  apas();
  doz();
  apas();
  doz();
  apas();
  dist = 932;
  Calibrare();
}

void motor2()
{
  Serial.println("MOTOR");
    H=HIGH;

  Calibrare();
  delay(10);
  unudoz();
      dist = 0;
  doz();
  apas();
  doz();
  doz();
  apas();
  doz();
  apas();
  apas();
  doz();
  apas();
  dist = 932;
  Calibrare();
}

void motor3()
{
 Serial.println("MOTOR");
    H=HIGH;

  Calibrare();
  delay(10);
  unudoz();
      dist = 0;
  doz();
  doz();
  doz();
  doz();
  doz();
  doz();
  doz();
  apas();
  doz();
  apas();
  doz();
  apas();
  
    dist = 932;
  Calibrare();
  
}

void loop() {
  if (x1 == 1)
  {
    motor1();
    timp();
    x1=0;
  }
  if (x1 == 2)
  {
    Calibrare();
        timp();
        x1=0;

  }
  if(x1 == 3)
  {    H=HIGH;

        unudoz();
        timp();
        x1=0;
  }
   if(x1 == 4)
  {    H=HIGH;

  dist = 0;
  doz();
   timp();
  dist = 932;
  x1=0;
  }


  if(x1==5)
  {
    H=LOW;
    dist = 0;
    distantadintredoz=493;
  doz();
          timp();

  distantadintredoz=527;
  dist = 932;
  x1=0;
  }
  if(x1==6)
  {
    apas();
            timp();

    x1=0;
    }
      if (x1 == 7)
  {
    motor2();
    timp();
    x1=0;
  }
        if (x1 == 8)
  {
        distantadintredoz=510;
    motor3();
    timp();
    x1=0;
            distantadintredoz=527;

  }
  
}
// Wire Slave Receiver
// funcția execută atunci când sunt primite date de la master
//această funcție este inregistrată ca un event, vezi setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // buclă prin toate fară ultimul
    char c = Wire.read(); // primește octetul ca un caracter
    Serial.print(c);         // afișează caracterul
  }
  x1 = Wire.read();    // primește octetul ca un întreg
  Serial.println(x1);         // afișează întregul
}
