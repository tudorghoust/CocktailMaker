// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <EEPROM.h>

#include <Wire.h>

int sticla[10];
const int stepPin2 = 10;
const int dirPin2 = 9;
const int enPin2 = 8;
const int stepPin = 13;
const int dirPin = 12;
const int enPin = 11;
int valoarebuton = 1;
int valoarebuton2 = 1;
int distantadintredoz = 495;
int H = HIGH;
int x1, i, d = 0;


void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output

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


int doz(int a)

{
  digitalWrite(enPin, LOW);

  digitalWrite(dirPin, H); // Enables the motor to move in a particular direction
  for (int x = 0; x < a * distantadintredoz; x++) {
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
  digitalWrite(dirPin2, LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
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
void Calibrare2()
{
  digitalWrite(enPin, LOW);

  digitalWrite(dirPin, LOW); // Enables the motor to move in a particular direction
  while (valoarebuton) {
    valoarebuton = digitalRead(4);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(500);

  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction

  while (valoarebuton == 0)
  {
    valoarebuton = digitalRead(4);

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
  for (int x = 0; x <= 1590; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(enPin, HIGH);
  valoarebuton = 1;
}



void Calibrare()
{
  Serial.println("MOTOR");
  digitalWrite(enPin2, LOW);

  digitalWrite(dirPin2, HIGH); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
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

  digitalWrite(dirPin, LOW); // Enables the motor to move in a particular direction
  while (valoarebuton) {
    valoarebuton = digitalRead(4);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(500);


  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
  while (valoarebuton == 0)
  {
    valoarebuton = digitalRead(4);

    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
  for (int x = 0; x <= 700; x++) {
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
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(2);
  Wire.endTransmission(8);
}

void eroare()
{
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(3);
  Wire.endTransmission(8);
}

void parametri()
{

  sticla[0] = EEPROM.read(0);
  sticla[4] = EEPROM.read(4);
  sticla[1] = EEPROM.read(1);
  sticla[2] = EEPROM.read(2);
  sticla[3] = EEPROM.read(3);
  sticla[5] = EEPROM.read(5);
  sticla[6] = EEPROM.read(6);
  sticla[7] = EEPROM.read(7);
  sticla[8] = EEPROM.read(8);
  sticla[9] = EEPROM.read(9);

}

void motor1()
{
  parametri();
  if (sticla[0] >= 1 && sticla[4] >= 3)
  {
    Serial.println("MOTOR");
    H = HIGH;
    Calibrare2();// sticla nr 1;
    apas();
    doz(4);// sticla nr 5
    apas();
    apas();
    apas();
    Calibrare();
    EEPROM.write(0, sticla[0] - 1);
    EEPROM.write(4, sticla[4] - 3);

  }
  else eroare();
}

void motor2()
{
  parametri();
  if (sticla[2] && sticla[5] && sticla[9])
  {
    Serial.println("MOTOR");
    H = HIGH;

    Calibrare2();
    doz(2);//sticla 3
    apas();
    apas();
    doz(3);//sticla 6
    apas();
    doz(3);//sticla 9
    apas();
    Calibrare();
    EEPROM.write(2, sticla[2] - 2);
    EEPROM.write(5, sticla[5] - 1);
    EEPROM.write(8, sticla[8] - 1);
  }
  else eroare();
}

void motor3()
{ parametri();
  if (sticla[3] && sticla [6] && sticla[7] && sticla[9])
  {
    Serial.println("MOTOR");
    H = HIGH;

    Calibrare2();
    doz(3);//sticla 4
    apas();
    doz(3);//sticla 7
    apas();
    doz(1);//sticla 8
    apas();
    doz(2);//sticla 10
    apas();
    Calibrare();
    EEPROM.write(3, sticla[3] - 1);
    EEPROM.write(5, sticla[5] - 1);
    EEPROM.write(7, sticla[7] - 1);
    EEPROM.write(9, sticla[9] - 1);
  }
  else eroare();
}

void loop() {
  if (x1 == 1)
  {
    motor1();
    timp();
    x1 = 0;
  }
  if (x1 == 2)
  {
    Calibrare();
    timp();
    x1 = 0;
    d = 0;

  }
  if (x1 == 3)
  { H = HIGH;
    Calibrare2();
    timp();
    x1 = 0;
  }
  if (x1 == 4)
  { H = HIGH;
    doz(1);
    d++;
    timp();
    x1 = 0;
  }


  if (x1 == 5)
  {
    H = LOW;
    doz(1);
    timp();
    d--;
    x1 = 0;
  }
  if (x1 == 6)
  {
    parametri();
    if (sticla[d] > 0)
    {
      apas();
      timp();
      EEPROM.write(d, sticla[d] - 1);


      x1 = 0;
    }
  }
  if (x1 == 7)
  {
    motor2();
    timp();
    x1 = 0;
  }
  if (x1 == 8)
  {
    motor3();
    timp();
    x1 = 0;

  }
  if (x1 == 10)
  {
    EEPROM.write(0, 40);
    EEPROM.write(1, 40);
    EEPROM.write(2, 28);
    EEPROM.write(3, 28);
    EEPROM.write(4, 20);
    EEPROM.write(5, 20);
    EEPROM.write(6, 20);
    EEPROM.write(7, 20);
    EEPROM.write(8, 20);
    EEPROM.write(9, 20);
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
