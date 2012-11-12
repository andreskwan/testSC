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

const int ledPin23 = 23;
const int ledPin22 = 22;
const int ledPin21 = 21;
const int ledPin20 = 20;
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
  pinMode(ledPin20,OUTPUT); 
  pinMode(ledPin21,OUTPUT); 
  pinMode(ledPin22,OUTPUT); 
  pinMode(ledPin23,OUTPUT); 

  Serial.begin(9600);        // connect to the serial port
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop () {

  valor = Serial.read();      // read the serial port

  //Serial.println("Aqui inicia todo");
  //Serial.write(val); 
  //Serial.println(val);

  valor = valor - 48;

/*   digitalWrite(ledPin19, HIGH);   // turn the LED on (HIGH is the voltage level) */
/*   delay(1000);                    // wait for a second */
/*   digitalWrite(ledPin14, HIGH);    // turn the LED off by making the voltage LOW */
/*   delay(1000);      // wait for a second */

  switch (valor) {
    //o
  case 63:
        printSerialValue(valor);
    //do something when var equals 1
    Serial.println("o 63 pin23 == o");
    digitalWrite(ledPin23, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin23, LOW);   // turn the LED on (HIGH is the voltage level)
    break;   
   //n 
  case 62:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("n 62 pin22 == n");
    digitalWrite(ledPin22, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin22, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
  //m  
  case 61:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("m 61 pin21 == m");
    digitalWrite(ledPin21, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin21, LOW);   // turn the LED on (HIGH is the voltage level)
    break; 
    //l
  case 60:
        printSerialValue(valor);
    //do something when var equals 1
    Serial.println("l 60 pin20 == l");
    digitalWrite(ledPin20, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin20, LOW);   // turn the LED on (HIGH is the voltage level)
    break;   
//k
  case 59:
        printSerialValue(valor);
    //do something when var equals 1
    Serial.println("k 59 pin19 == k");
    digitalWrite(ledPin19, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin19, LOW);   // turn the LED on (HIGH is the voltage level)
    break;   
   //j 
  case 58:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("j 58 pin18 == j");
    digitalWrite(ledPin18, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin18, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
  //i  
  case 57:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("i 57 pin17 == i");
    digitalWrite(ledPin17, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin17, LOW);   // turn the LED on (HIGH is the voltage level)
    break; 
    //h
  case 56:
        printSerialValue(valor);
    //do something when var equals 1
    Serial.println("h 56 pin16 == h");
    digitalWrite(ledPin16, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin16, LOW);   // turn the LED on (HIGH is the voltage level)
    break;   
   //g 
  case 55:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("g 55 pin15 == g");
    digitalWrite(ledPin15, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin15, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
  //f  
  case 54:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("f pin14 == f");
    digitalWrite(ledPin14, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin14, LOW);   // turn the LED on (HIGH is the voltage level)
    break; 
  //e   
  case 53:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("e pin13 == e");
    digitalWrite(ledPin13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin13, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
    //d
  case 52:
        printSerialValue(valor);
    //do something when var equals 1
    Serial.println("d pin13 == d");
    digitalWrite(ledPin13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin13, LOW);   // turn the LED on (HIGH is the voltage level)
    break;   
   //c 
  case 51:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("c pin12 == c");
    digitalWrite(ledPin12, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin12, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
  //b  
  case 50:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("b pin11 == b");
    digitalWrite(ledPin11, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin11, LOW);   // turn the LED on (HIGH is the voltage level)
    break; 
  //a   
  case 49:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("a pin10 == a");
    digitalWrite(ledPin10, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin10, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case 9:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("9 == a");
    digitalWrite(ledPin9, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin9, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 8:
      printSerialValue(valor);
    //do something when var equals 2
    Serial.println("8 == b");
    digitalWrite(ledPin8, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin8, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 7:
      printSerialValue(valor);
    //do something when var equals 1
    Serial.println("7 == a");
    digitalWrite(ledPin7, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin7, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 6:
    //do something when var equals 1
      printSerialValue(valor);
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
    ;

    // if nothing else matches, do the default
    // default is optional
  }

}

void printSerialValue(int valor){
    Serial.print("data: ");
    Serial.println(valor);
    delay(1000);
}

