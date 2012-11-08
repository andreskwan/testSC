/* Just testing serial port communication
 * Serial Read Blink
 * -----------------
 * Turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The LED will blink the number of times given by a 
 * single-digit ASCII number read from the serial port.
 *
 * Created 18 October 2006
 * copyleft 2006 Tod E. Kurt <tod@todbot.com>
 * http://todbot.com/
 * 
 * Test Branch
 * based on "serial_read_advanced" example
 */
#include <SoftwareSerial.h>
//////////////////////////////////////////////////////////////
// constants
int ledPin13 = 13;   //12 select the pin for the LED
int ledPin12 = 12;
int ledPin11 = 11;
int ledPin10 = 10;
int ledPin9 = 9;
int ledPin8 = 8;
int ledPin7 = 7;
int ledPin6 = 6;
int ledPin5 = 5;
int ledPin4 = 4;
int ledPin3 = 3;
int ledPin2 = 2;   

//input
int pin0motor1 = 0;    
int pin1motor2 = 0;    

int valor = 0;         // variable to store the data from the serial port

//////////////////////////////////////////////////////////////
// Variables will change:
int estadoMotor1 = 0;         // current state of the button
int estadoMotor2 = 0;         // current state of the button
int ultimoEstadoM1 = 0;     // previous state of the button
int ultimoEstadoM2 = 0;     // previous state of the button

void setup() {
  pinMode(pin0motor1,INPUT);    // declare the LED's pin as input
  pinMode(pin1motor2,INPUT);    // declare the LED's pin as input  

  pinMode(ledPin2,OUTPUT);    // declare the LED's pin as output
  pinMode(ledPin3,OUTPUT); 
  pinMode(ledPin4,OUTPUT); 
  pinMode(ledPin5,OUTPUT); 
  pinMode(ledPin6,OUTPUT); 
  pinMode(ledPin7,OUTPUT); 
  pinMode(ledPin8,OUTPUT); 
  pinMode(ledPin9,OUTPUT); 
  pinMode(ledPin10,OUTPUT); 
  pinMode(ledPin11,OUTPUT); 
  pinMode(ledPin12,OUTPUT); 

  Serial.begin(9600);        // connect to the serial port
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop () {


  valor = Serial.read();      // read the serial port

  Serial.println("Aqui inicia todo");
  //Serial.write(val); 
  //Serial.println(val);

  valor = valor - 48;

  digitalWrite(ledPin12, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                    // wait for a second
  digitalWrite(ledPin12, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);      // wait for a second

  switch (valor) {

  case d:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case c:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case b:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case a:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case 9:
    //do something when var equals 1
    Serial.println("9 == a");
    digitalWrite(ledPin9, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin9, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 8:
    //do something when var equals 2
    Serial.println("8 == b");
    digitalWrite(ledPin8, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin8, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 7:
    //do something when var equals 1
    Serial.println("7 == a");
    digitalWrite(ledPin7, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin7, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 6:
    //do something when var equals 1
    Serial.println("6 == a");
    digitalWrite(ledPin6, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin6, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 5:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case 4:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    

  case 3:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    

  case 2:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    

  case 1:
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    


  default: 
    Serial.print("dato no valido: ");
    Serial.println(valor);
    delay(1000);
    // if nothing else matches, do the default
    // default is optional
  }

  // if the stored value is a single-digit number, blink the LED that number
  // if (val > '0' && val <= '9' ) {
  //   val = val - '0';          // convert from character to number
  //   for(int i=0; i<val; i++) {
  //     Serial.println("blink!");
  //     digitalWrite(ledPin,HIGH);
  //     delay(150);
  //     digitalWrite(ledPin, LOW);
  //     delay(150);
  //   }
  //   //Serial.println();
  // }
}

