#include <UTFT.h>
#include <UTouch.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 5

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
UTFT myGLCD(SSD1963_800480, 38, 39, 40, 41); //(byte model, int RS, int WR, int CS, int RST, int SER)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


UTouch  myTouch( 43, 42, 44, 45, 46);  //byte tclk, byte tcs, byte din, byte dout, byte irq


// Declare which fonts we will be using
extern uint8_t GroteskBold[];

int x, y;
bool rep = true , repback = false , calibrarever = true , repbackcal = false;
char stCurrent[20] = "";
int stCurrentLen = 0;
char stLast[20] = "";
int timp = -1;
int NUM_LIGHTS = 16;
int x1 = 0;
int c = 1, d = 0, e = 0 ;
int paharbuton = 0;

/*************************
**   Custom functions   **
*************************/
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  timp = Wire.read();    // receive byte as an integer
  Serial.println(timp);         // print the integer
}

void MeniuPrincipal()
{
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 0, 255);

  myGLCD.fillRoundRect (30, 30, 385, 225);//y x y x
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("Cocktails", 65, 95);
  myGLCD.drawRoundRect (30, 30, 385, 225);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (30 , 255, 385, 450);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Calibrare", 65, 320);
  myGLCD.drawRoundRect (30, 255, 385, 450);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (415 , 30, 770, 225);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Mod manual", 440, 95);
  myGLCD.drawRoundRect (415, 30, 770, 225);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (415 , 255, 770, 450);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Reset par.", 445, 320);
  myGLCD.drawRoundRect (415, 255, 770, 450);

}
void color (uint32_t c)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
void nocolor()
{
  for ( int i = 0; i < NUM_LIGHTS; i++) {
    strip.setPixelColor(i, 0);
    strip.show();
  }
}

void eroarepahar()
{
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("EROARE PAHAR", 65, 95);
}


void ledefect()
{
  color(strip.Color(70, 255, 0)); // Green
  delay(800);
  nocolor(); // Green
}

void Calibrare()
{
  Serial.print("CAL");
  Wire.beginTransmission(8);
  Wire.write(x1);              // sends one byte
  Wire.endTransmission(8);    // stop transmitting
}

void MeniuSec()
{
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (30, 30, 385, 225);//x y x y
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Cocktail1", 65, 95);
  myGLCD.drawRoundRect (30, 30, 385, 225);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (30 , 255, 385, 450);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Cocktail2", 65, 320);
  myGLCD.drawRoundRect (30, 255, 385, 450);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (415 , 30, 770, 225);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Cocktail3", 445, 95);
  myGLCD.drawRoundRect (415, 30, 770, 225);

  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (622 , 382, 770, 450);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("EXIT", 633, 385);
  myGLCD.drawRoundRect (622, 382, 770, 450);

}
void MeniuManual()
{
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (30, 30, 385, 225);//x y x y
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("STANGA", 110, 95);
  myGLCD.drawRoundRect (30, 30, 385, 225);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (30 , 255, 385, 450);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("DOZARE", 110, 320);
  myGLCD.drawRoundRect (30, 255, 385, 450);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (415 , 30, 770, 225);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("DREAPTA", 475 , 95);
  myGLCD.drawRoundRect (415, 30, 770, 225);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (622 , 382, 770, 450);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("GATA", 633, 385);
  myGLCD.drawRoundRect (622, 382, 770, 450);

}


void setup()
{
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  pinMode(8, OUTPUT);  //backlight
  digitalWrite(8, HIGH);//on
  pinMode(2, INPUT);

  // Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(GroteskBold);
  myGLCD.setBackColor(0, 0, 0);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  MeniuPrincipal();
  Serial.begin(9600);


}

void loop()
{
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      Serial.println(x);
      Serial.print(" ");
      Serial.println(y);



      if (rep)
      {
        c = 1;
        if ((x >= 30) && (x <= 385)) // Upper row
        {
          if ((y >= 30) && (y <= 225)) // Button: 1
          {
            //waitForIt(30, 30, 385, 225);
            rep = false;
            repback = true;
            Serial.print("DA");
            delay(100);
            MeniuSec();

            x = y = 0;
          }
        }
        if ((x >= 30) && (x <= 385)) // Upper row
        {
          if ((y >= 255) && (y <= 450)) // Button: 2
          {
            rep = false;
            x = y = 0;
            x1 = 2;
            Calibrare();
            Serial.println(timp);         // print the integer

            while (timp != 2)
            {
              ledefect();
              myGLCD.fillScr(0, 0, 0);
              myGLCD.setBackColor(0, 0, 255);
              myGLCD.print("CALIBRARE", 65, 95);
            }
            Serial.println(timp);         // print the integer

            if (timp == 2)
            {
              MeniuPrincipal();
              timp = -1;
              rep = true;
              delay(100);
            }
          }
        }
        if ((x >= 416) && (x <= 770)) // Upper row
        {
          if ((y >= 30) && (y <= 225)) // Button: 2
          {
            rep = false;
            x = y = 0;
            MeniuManual();
            c = 1;
            e = 0;
            repbackcal = true;
          }

        }
        if ((x >= 416) && (x <= 770)) // Upper row
        { //  myGLCD.drawRoundRect (415, 255, 770, 450);

          if ((y >= 225) && (y <= 450)) // Button: 2
          {
            Serial.print("yes");
            Wire.beginTransmission(8);
            Wire.write(10);              // sends one byte
            Wire.endTransmission(8);    // stop transmitting
            x = y = 0;
          }
        }
      }
      if (repbackcal)

      {
        if ((x >= 30) && (x <= 385)) // Upper row
        {
          if ((y >= 90) && (y <= 295)) // Button: 2
          {
            Serial.println("EEE");
            Serial.println(e);
            if (e < 10)
            {
              Serial.println(c);
              if (c)
              {
                x1 = 2;
                Calibrare();
                x1 = 3;

                paharbuton = digitalRead(2);
                while (paharbuton == 0)
                {
                  repbackcal = false;
                  paharbuton = digitalRead(2);
                  eroarepahar();
                  paharbuton = digitalRead(2);
                  ledefect();
                }

                while (timp != 2)
                {
                  ledefect();
                  myGLCD.fillScr(0, 0, 0);
                  myGLCD.setBackColor(0, 0, 255);
                  myGLCD.print("PREPARARE", 65, 95);
                }
                x1 = 3;
              }
              Serial.println(x1);
              color(strip.Color(70, 255, 0)); // Green

              c = 0;
              e++;
              Calibrare();
              x1 = 4;
              while (timp != 2)
              {
                ledefect();
                myGLCD.fillScr(0, 0, 0);
                myGLCD.setBackColor(0, 0, 255);
                myGLCD.print("PREPARARE", 65, 95);
              }
              MeniuManual();
              x = y = 0;
              repbackcal = true;

            }

          }

        }

        if ((x >= 415) && (x <= 770)) // Upper row
        {
          if ((y >= 30) && (y <= 225)) // Button: 2
          {
            if (e > 1)
            { repbackcal = false;
              x = y = 0;
              e--;
              Wire.beginTransmission(8);
              Wire.write(5);              // sends one byte
              Wire.endTransmission(8);
              while (timp != 2)
              {
                ledefect();
                myGLCD.fillScr(0, 0, 0);
                myGLCD.setBackColor(0, 0, 255);
                myGLCD.print("PREPARARE", 65, 95);
              }
              MeniuManual();
              repbackcal = true;

            }
          }
        }
        if ((x >= 30) && (x <= 385)) // Upper row
        {
          if ((y >= 225) && (y <= 450)) // Button: 2
          {
            repbackcal = false;

            x = y = 0;
            Wire.beginTransmission(8);
            Wire.write(6);              // sends one byte
            Wire.endTransmission(8);
            while (timp != 2)
            {
              ledefect();
              myGLCD.fillScr(0, 0, 0);
              myGLCD.setBackColor(0, 0, 255);
              myGLCD.print("PREPARARE", 65, 95);
            }
            MeniuManual();
            repbackcal = true;

          }
        }

        if ((x >= 622) && (x <= 770)) // Upper row
        {
          if ((y >= 382) && (y <= 450)) // Button: 2
          {
            repbackcal = false;

            x = y = 0;
            Wire.beginTransmission(8);
            Wire.write(2);              // sends one byte
            Wire.endTransmission(8);
            while (timp != 2)
            {
              ledefect();
              myGLCD.fillScr(0, 0, 0);
              myGLCD.setBackColor(0, 0, 255);
              myGLCD.print("PREPARARE", 65, 95);
            }
            MeniuPrincipal();
            nocolor();
            c = 1;
            e = 0;
            rep = true;
          }

        }
      }




      if (repback)
      {
        if ((y <= 255 ) && (y <= 450)) // Buton
        {
          if ((x >= 30) && (x <= 385)) // Button: 1
          {
            repback = false;
            Serial.println(timp);

            paharbuton = digitalRead(2);
            while (paharbuton == 0)
            {
              paharbuton = digitalRead(2);
              eroarepahar();
              paharbuton = digitalRead(2);
              ledefect();
            }
            if (paharbuton == 1)
            {
              x = y = 0;
              Serial.print("DA12");
              //Serial.write(45); // send a byte with the value 45
              x1 = 1;

              Calibrare();

              paharbuton = 0;

              while (timp != 2)
              {
                color(strip.Color(70, 255, 0)); // Green
                myGLCD.fillScr(0, 0, 0);
                myGLCD.setBackColor(0, 0, 255);
                myGLCD.print("PREPARARE", 65, 95);

              }
              Serial.println(timp);
              Serial.print("DA3312");

              for (int t = 1; t <= 4; t++)
              {
                ledefect();
                delay(70);
              }
              if (timp == 2)
              {
                delay(100);
                repback = false;
                timp = -1;
                delay(800);
                MeniuSec();
                repback = true;

              }
            }
          }
        }
        if ((x >= 30) && (x <= 385)) // Upper row
        {
          if ((y >= 225) && (y <= 450)) // Button: 2
          { repback = false;
            paharbuton = digitalRead(2);
            while (paharbuton == 0)
            {
              paharbuton = digitalRead(2);
              eroarepahar();
              paharbuton = digitalRead(2);
              ledefect();
            }
            if (paharbuton == 1)
            {
              x = y = 0;
              Serial.print("DA12");
              //Serial.write(45); // send a byte with the value 45
              x1 = 7;
              Calibrare();
              paharbuton = 0;
              while (timp != 2)
              {
                color(strip.Color(70, 255, 0)); // Green
                myGLCD.fillScr(0, 0, 0);
                myGLCD.setBackColor(0, 0, 255);
                myGLCD.print("PREPARARE", 65, 95);

              }
              Serial.print("DA3312");

              for (int t = 1; t <= 4; t++)
              {
                ledefect();
                delay(70);
              }
              if (timp == 2)
              {
                delay(100);
                timp = -1;
                delay(800);
                MeniuSec();
                repback = true;

              }
            }
          }
        }

        if ((x >= 415) && (x <= 770)) // Upper row
        {
          if ((y >= 30) && (y <= 225)) // Button: 2

          { repback = false;
            paharbuton = digitalRead(2);
            while (paharbuton == 0)
            {
              paharbuton = digitalRead(2);
              eroarepahar();
              paharbuton = digitalRead(2);
              ledefect();
            }
            if (paharbuton == 1)
            {
              x = y = 0;
              Serial.print("DA12");
              //Serial.write(45); // send a byte with the value 45
              x1 = 8;
              Calibrare();
              paharbuton = 0;
              while (timp != 2)
              {
                color(strip.Color(70, 255, 0)); // Green
                myGLCD.fillScr(0, 0, 0);
                myGLCD.setBackColor(0, 0, 255);
                myGLCD.print("PREPARARE", 65, 95);

              }
              Serial.print("DA3312");

              for (int t = 1; t <= 4; t++)
              {
                ledefect();
                delay(70);
              }
              if (timp == 2)
              {
                delay(100);
                timp = -1;
                delay(800);
                MeniuSec();
                repback = true;

              }
            }
          }
        }

        if ((y >= 382) && (y <= 450)) // Upper row Back
        {
          if ((x >= 622) && (x <= 770)) // Button: 1
          {
            repback = false;
            Serial.print("DA1");
            delay(100);
            MeniuPrincipal();
            rep = true;
            x = y = 0;

          }
        }

      }
    }
  }
}
