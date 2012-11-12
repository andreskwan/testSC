/* Just testing serial port communication and pins in the Leonardo board
 * Serial Read Blink in any pin with order send from pc 
 * -----------------
 * Turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The LED will blink the number of times given by a 
 * single-digit ASCII number read from the serial port.
 *
 * Created 12/11/12 
 * copyleft 2012 Tod A. Kwan <andreskwan@gmail.com>
 * 
 * based on "serial_read_advanced" example
 */
#include <SoftwareSerial.h>
//////////////////////////////////////////////////////////////
// constants outputs
// all pins as outputs

const int ledPin19 = 19;
const int ledPin18 = 18;
const int ledPin17 = 17;
const int ledPin16 = 16;
const int ledPin15 = 15;
const int ledPin14 = 14;
const int ledPin13 = 13;
const int ledPin12 = 12;
const int ledPin11 = 11;
const int ledPin10 = 10;
const int ledPin9 = 9;
const int ledPin8 = 8;
const int ledPin7 = 7;
const int ledPin6 = 6;
const int ledPin5 = 5;
const int ledPin4 = 4;
const int ledPin3 = 3;
const int ledPin2 = 2;   
const int ledPin1 = 1;   
const int ledPin0 = 0;   

//constan inputs



//////////////////////////////////////////////////////////////
// Variables will change:
int valor = 0;         // variable to store the data from the serial port

//////////////////////////////////////////////////////////////
void setup() {
  pinMode(ledPin0,OUTPUT); 
  pinMode(ledPin1,OUTPUT); 
  pinMode(ledPin2,OUTPUT);
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
  pinMode(ledPin13,OUTPUT);  //LED 
  pinMode(ledPin14,OUTPUT); 
  pinMode(ledPin15,OUTPUT); 
  pinMode(ledPin16,OUTPUT); 
  pinMode(ledPin17,OUTPUT); 
  pinMode(ledPin18,OUTPUT); 
  pinMode(ledPin19,OUTPUT); 

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

/*   digitalWrite(ledPin19, HIGH);   // turn the LED on (HIGH is the voltage level) */
/*   delay(1000);                    // wait for a second */
/*   digitalWrite(ledPin14, HIGH);    // turn the LED off by making the voltage LOW */
/*   delay(1000);      // wait for a second */

  switch (valor) {

  case 'd':
    //do something when var equals 1
    Serial.println("pin19 == d");
    digitalWrite(ledPin19, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin19, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case 'c':
    //do something when var equals 1
    Serial.println("pin 18 == c");
    digitalWrite(ledPin18, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin18, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case 'b':
    //do something when var equals 1
    Serial.println("pin14 == b");
    digitalWrite(ledPin14, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin14, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case 'a':
    //do something when var equals 1
    Serial.println(" == a");
    digitalWrite(ledPin13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin13, LOW);   // turn the LED on (HIGH is the voltage level)
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
//   case 5:
//     //do something when var equals 1
//     Serial.println(" == a");
//     digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//     delay(1000);
//     digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
//     break;    
//   case 4:
//     //do something when var equals 1
//     Serial.println(" == a");
//     digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//     delay(1000);
//     digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
//     break;    

//   case 3:
//     //do something when var equals 1
//     Serial.println(" == a");
//     digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//     delay(1000);
//     digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
//     break;    

//   case 2:
//     //do something when var equals 1
//     Serial.println(" == a");
//     digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//     delay(1000);
//     digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
//     break;    

//   case 1:
//     //do something when var equals 1
//     Serial.println(" == a");
//     digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//     delay(1000);
//     digitalWrite(ledPin, LOW);   // turn the LED on (HIGH is the voltage level)
//     break;    


  default: 
    Serial.print("dato no valido: ");
    Serial.println(valor);
    delay(1000);
    // if nothing else matches, do the default
    // default is optional
  }

}

