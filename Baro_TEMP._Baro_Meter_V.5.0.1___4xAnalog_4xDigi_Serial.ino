// Maddy => Barometer Test 5.01 Arduino 328 nano LCD 2x16
// 4 x Analog  4x Digi 
// 2024/2025


//LCD = 2x16 Zeichen
//LiquidCrystal: Arduino  Pins ==> (13, 12, 11, 10, 9, 8) LCD ==> (RS,EN,D4,D5,D6,D7)
//
//BOSCH BPM180 I²C: Arduino  Pins ==> (5V=VCC, GND=GND,A4=SDA, A5=SCL)
//
//Serielle Datenausgabe mit 9600 Baud ca. alle 200 s
//
//  Digital Eingänge 5V ==> Anzeige 0 - 1
//  Eingang 1 = Digial Eingang D2 (Arduino 2 Pin)
//  Eingang 2 = Digial Eingang D3 (Arduino 3 Pin)
//  Eingang 3 = Digial Eingang D4 (Arduino 4 Pin)
//  Eingang 4 = Digial Eingang D5 (Arduino 5 Pin)
//
//  Analog Eingänge 0 - 5 V==> Anzeige 0,00 - 5,00 V
//  Eingang 1 = Analog Eingang A0 (Arduino A0 Pin)
//  Eingang 2 = Analog Eingang A1 (Arduino A1 Pin)
//  Eingang 3 = Analog Eingang A2 (Arduino A2 Pin)
//  Eingang 4 = Analog Eingang A3 (Arduino A3 Pin)


#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_BMP085.h>

//int l; // variable loop res.
//int s; // variable Senden res.

int i = 0; // ariable ==> Schleifen-Counter Daten Senden Verzögerung
int x = 0; // variable ==> TX Daten Counter Serial ==> Anzahl der Sendungen
int z = 0; // variable ==> Blink Fehlermeldung Prüfung BMP180 Ausgabe LCD


int Eingang1 = 2; // Digial Eingang D2
int Eingang2 = 3; // Digial Eingang D3
int Eingang3 = 4; // Digial Eingang D4
int Eingang4 = 5; // Digial Eingang D5

//setup for the LCD 2x16  Anschlüsse deklarieren.
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //RS,EN,D4,D5,D6,D7

Adafruit_BMP085 bmp;

void setup()

{
  pinMode(Eingang1, INPUT);
  pinMode(Eingang2, INPUT);
  pinMode(Eingang3, INPUT);
  pinMode(Eingang4, INPUT);

  lcd.begin(16, 2); //lcd.begin(16, 2) Festlegen des Display-Typs. (2x16 Zeichen).
  lcd.setCursor(0, 0); // Cursor am Anfang der Zeile setzen.
  lcd.print ("Madeleine V.5.01"); // Print a info message to the LCD.
  lcd.setCursor(0, 1);// Cursor am Anfang zweiten Zeile setzen.
  lcd.print("26.04.2023");


  delay (2500);

  lcd.begin(16, 2);

  lcd.print(" BMP180 Sensor"); // Print a logo message to the LCD.
  lcd.setCursor(0, 1);
  lcd.print("Temp. & Pressure");
  lcd.setCursor(0, 2);
  delay (3000);

  lcd.clear();//clear display

  lcd.print("4xAnalog in V"); // Print a logo message to the LCD.
  lcd.setCursor(0, 1);
  lcd.print("4xDigital in 0-1");
  lcd.setCursor(0, 2);
  delay (3000);

  lcd.clear();//clear display


  //init serial for some debug
  Serial.begin(9600);

  // Print Serial a info message to the Serial Port (9600baud).

  Serial.println("BOSCH BMP180 Sensor-Daten");
  Serial.println("TX Daten Counter");
  Serial.println("Temperature in °C");
  Serial.println("Pressure in Pa");
  Serial.println("Pressure in mbar");
  Serial.println("Altitute in Meter");
  Serial.println("(Calculate altitude in meters)");
  Serial.println("4 Anzeigen Analog 0,00 - 5,00 V / DC");
  Serial.println("4 Anzeigen Digital-Status  0 - 1");
  Serial.println("");

  Serial.println("Sende Daten alle 200s/9600Baud");
  Serial.println("");

  //init bmp180
  if (bmp.begin()) // Sensor OK Meldung
  {
    Serial.println("BOSCH BMP180 Sensor OK"); //  Information über Sensor BPM180  Serial Ausgabe
    Serial.println("Starte die Übertragung"); //  Information über Sensor BPM180 Serial Ausgabe
    Serial.println("");
    lcd.begin(16, 2);  //init LCD
    lcd.setCursor(0, 0);
    lcd.print("BOSCH BMP180 OK "); // Information über Sensor BPM180 ==> Ausgabe LCD
    lcd.setCursor(0, 1);
    lcd.print("Sensor gefunden");
    delay(2500);
    lcd.clear();//clear display
  }

  //if nicht bmp ==> Fehlermeldung - Schleife für Serial 9600 & LCD !

  if (!bmp.begin()) // !==> seht für "nicht" bmp (Abfrage negiert)

  {
    Serial.println("      !! A C H T U N G !!"); // Fehler Information über Sensor BPM180 bei nicht Erreichbarkeit. => Serial Ausgabe

    Serial.println("! BOSCH BMP180 Sensor not found !"); // Fehler Information über Sensor BPM180 bei nicht Erreichbarkeit. Serial Ausgabe

    delay (500);

  }

  if (!bmp.begin()) // !==> seht für "nicht" bmp (Abfrage negiert)


    while (1)

      // while Schleife ==> LCD Display Fehlermeldung blinken mit (on 800 ms / off 350 ms)
    {
      lcd.begin(16, 2);  //init LCD
      lcd.setCursor(0, 0);

      lcd.print("! BOSCH BMP180 !"); // Fehler Information über Sensor BPM180 bei nicht Erreichbarkeit. LCD Ausgabe
      lcd.setCursor(0, 1);
      lcd.print("Sensor not found");
      delay (800);
      lcd.clear();
      delay(350);

    }



  // lcd.begin(16, 2);  //init LCD
  //line 1 - temperature
  // lcd.setCursor(0, 0);
  // lcd.print("Temp C = ");   ====> ALT nicht mehr benutzt nur zur INFO !!
  //line 2 - humidity
  //lcd.setCursor(0, 1);
  // lcd.print("P.  Pa = ");

}
void loop()

{
  // for Schleife ==> LCD Display Fehlermeldung blinken mit (on 800 ms / off 350 ms)

  if (!bmp.begin()) // !==> seht für "nicht" bmp (Abfrage negiert)


    for (int z = 0; z < 7; z++) // 7 x Zähler Schleife für Blinken

    {
      lcd.begin(16, 2);  //init LCD
      lcd.setCursor(0, 0);

      lcd.print("! BOSCH BMP180 !"); // Fehler Information über Sensor BPM180 bei nicht Erreichbarkeit. LCD Ausgabe
      lcd.setCursor(0, 1);
      lcd.print("Sensor not found");
      delay (800);
      lcd.clear();
      delay(350);

    }


  // Temeratur & Druck serial senden mit 9600 (°C + Pa)Serial.begin(9600);
  //Serial.begin(9600);


  for (int i = 0; i < 7; i++) // 7 x Zähler Schleife Daten Sende Verzögerung 200s

  {

    //if  bmp ==> WENN BOSCH OK ist DATEN am LCD Anzeigen !

    if (bmp.begin()) // !==> Abrage BPM180 OK ?

    {



      // put your main code here, to run repeatedly:

      //display temperature and altitude on lcd
      // you can get a more precise measurement of altitude
      // if you know the current sea level pressure which will
      // vary with weather and such. If it is 1015 millibars
      // that is equal to 101500 Pascals.

      lcd.setCursor(0, 0);
      lcd.print("Temp.= ");
      lcd.print(bmp.readTemperature());
      lcd.print(" C");
      lcd.setCursor(0, 1);
      lcd.print("Druck= ");
      lcd.print(bmp.readPressure());
      lcd.print(" Pa");
      delay(5000); // Anzeige-Zeit obiger Text==> 5000ms
      lcd.clear();//clear display

      float Pressure = float(bmp.readPressure()); // Umrechnung mit Variable float (float mit Kommastellen !!)
      float Pmbar = Pressure * (1.0 / 100.0); // Umrechnung 1,0/100,0 mit float !

      lcd.setCursor(0, 0);
      lcd.print("Temp.=  ");
      lcd.print(bmp.readTemperature());
      lcd.print("  C");
      lcd.setCursor(0, 1);
      lcd.print("P.= ");
      lcd.print(Pmbar);
      lcd.print(" mbar");

      delay(5000); // Anzeige-Zeit obiger Text==> 5000ms
      lcd.clear();//clear display

      // Calculate altitude assuming 'standard' barometric
      // pressure of 1013.25 millibar = 101325 Pascal
      //    lcd.setCursor(0.0);

      lcd.print("Alt = ");
      lcd.print(bmp.readAltitude());
      lcd.println(" m.   ");
      lcd.setCursor(0, 1);
      lcd.print("R.Altitude Meter ");



      delay(5000);// Anzeige-Zeit obiger Text==> 5000ms
      lcd.clear();//clear display
      //    lcd.setCursor(0.0);

      lcd.print("Druck= ");
      lcd.print(bmp.readSealevelPressure());
      lcd.println(" Pa   ");
      lcd.setCursor(0, 1);
      lcd.print("readSealevelPressure");

      delay (5000);// Anzeige-Zeit obiger Text==> 5000ms
      lcd.clear();//clear display

      // you can get a more precise measurement of altitude
      // if you know the current sea level pressure which will
      // vary with weather and such. If it is 1015 millibar
      // that is equal to 101500 Pascals.

      //  lcd.setCursor(0.0);
      lcd.print("R.Alt = ");
      lcd.print(bmp.readAltitude(101500));
      lcd.println(" m.  ");
      lcd.setCursor(0, 1);
      lcd.print("Sea level Meter");

      delay(5000); // Anzeige-Zeit obiger Text==> 5000ms
      lcd.clear();//clear display

    }


    lcd.setCursor(0, 0);
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = sensorValue * (5.0 / 1023.0);
    // print out the value you read:
    lcd.print("1:");
    lcd.print(voltage);
    lcd.print("V");



    lcd.setCursor(8, 0);
    int sensorValue2 = analogRead(A1);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage2 = sensorValue2 * (5.0 / 1023.0);
    // print out the value you read:
    lcd.print(" 2:");
    lcd.print(voltage2);
    lcd.print("V");



    // read the input on analog pin 3:
    int sensorValue3 = analogRead(A2);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage3 = sensorValue3 * (5.0 / 1023.0);
    // print out the value you read:
    lcd.setCursor(0, 1);
    lcd.print("3:");
    lcd.print(voltage3);
    lcd.print("V");



    lcd.setCursor(8, 1);
    int sensorValue4 = analogRead(A3);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage4 = sensorValue4 * (5.0 / 1023.0);
    // print out the value you read:
    lcd.print(" 4:");
    lcd.print(voltage4);
    lcd.print("V");

    delay (5000);
    lcd.clear();//clear display


    lcd.setCursor(0, 0);
    // read the input pin:
    int status1 = digitalRead(Eingang1);
    // print out the state of the button:
    lcd.print("D 1:= ");
    lcd.print(status1);


    lcd.setCursor(9, 0);
    // read the input pin:
    int status2 = digitalRead(Eingang2);
    // print out the state of the button:
    lcd.print("D 2:= ");
    lcd.print(status2);


    lcd.setCursor(0, 1);
    // read the input pin:
    int status3 = digitalRead(Eingang3);
    // print out the state of the button:
    lcd.print("D 3:= ");
    lcd.print(status3);


    lcd.setCursor(9, 1);
    // read the input pin:
    int status4 = digitalRead(Eingang4);
    // print out the state of the button:
    lcd.print("D 4:= ");
    lcd.print(status4);


    delay (5000);
    lcd.clear();//clear display



    delay (150); // Wartezeit nach dem LCD löschen
    lcd.print ("Sende Daten alle");
    lcd.setCursor(0, 1);
    lcd.print ("200s-9600 Baud");

    delay (3000);
    lcd.clear();//clear display

    lcd.print ("Counter bis TX"); // Warte Intervall bis Senden x/7
    lcd.setCursor(0, 1);
    lcd.print (i);
    lcd.print (" / 6");
    delay (3000);

  }




  // Alle 200s ein Status Serial mit 9600 Baud

  Serial.print("Counter = ");

  x = x + 1;  // Counter Variable (x) Erhöhung +1 vom Zählerstand

  Serial.println(x); // Serial Print der Counter-Variable mit Wert von (x)



  //if nicht bmp ==> Fehlermeldung BPM180 - Schleife für Serial 9600 !

  if (!bmp.begin()) // !==> seht für "nicht" bmp (Abfrage negiert)
  {
    Serial.println("");
    Serial.println("      !! A C H T U N G !!"); // Fehler Information über Sensor BPM180 bei nicht Erreichbarkeit. Serial Ausgabe

    Serial.println("! BOSCH BMP180 Sensor not found !"); // Fehler Information über Sensor BPM180 bei nicht Erreichbarkeit. Serial Ausgabe

    Serial.println("! ES WERDEN KEINE DATEN GESENDET !"); // Fehler Information über Sensor BPM180 bei nicht Erreichbarkeit. Serial Ausgabe


    Serial.println("");
  }

  if (bmp.begin()) // BPM180 OK Sende seine Daten Serial !
  {

    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    float Pressure = float(bmp.readPressure()); // Umrechnung mit Variable float (float mit Kommastellen !!)
    float Pmbar = Pressure * (1.0 / 100.0); // Umrechnung 1,0/100,0 mit float !

    Serial.print("Pressure = ");
    Serial.print(Pmbar);
    Serial.println(" mbar");



    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" m");
    Serial.println("");
    Serial.println(" Analog:");

  }


  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print(" 1: ");
  Serial.print(voltage);
  Serial.println(" V");


  int sensorValue2 = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage2 = sensorValue2 * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print(" 2: ");
  Serial.print(voltage2);
  Serial.println(" V");


  int sensorValue3 = analogRead(A2);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage3 = sensorValue3 * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print(" 3: ");
  Serial.print(voltage3);
  Serial.println(" V");

  int sensorValue4 = analogRead(A3);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage4 = sensorValue4 * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print(" 4: ");
  Serial.print(voltage4);
  Serial.println(" V");

  Serial.println("");
  Serial.println(" Digital:");


  // read the input pin:
  int status1 = digitalRead(Eingang1);
  // print out the state of the status1:
  Serial.print(" Digi.1:= ");
  Serial.println(status1);

  // read the input pin:
  int status2 = digitalRead(Eingang2);
  // print out the state of the status2:
  Serial.print(" Digi.2:= ");
  Serial.println(status2);

  // read the input pin:
  int status3 = digitalRead(Eingang3);
  // print out the state of the status3:
  Serial.print(" Digi.3:= ");
  Serial.println(status3);

  // read the input pin:
  int status4 = digitalRead(Eingang4);
  // print out the state of the status4:
  Serial.print(" Digi.4:= ");
  Serial.println(status4);


  Serial.println("");
  Serial.println("");

  delay(1500); // Wartezeit/Haltezeit 1500ms für obigen Text am LCD Display

  lcd.clear();//clear display

  lcd.setCursor(0, 0);
  lcd.print("Counter = ");
  lcd.print(x);
  lcd.setCursor(0, 1);
  lcd.print("!Daten Gesendet!");


  delay (2000); // Wartezeit/Haltezeit 2000ms für Textausgabe Counter+ Anzeige Daten Gesendet ==> am LCD Display
  lcd.clear();//clear display

}
