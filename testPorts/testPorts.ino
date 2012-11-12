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

// //well organized
// //Analog pins used as digital outputs
// const int ledPin23 = 23; //19 A5 o
// const int ledPin22 = 22; //18 A4 n
// const int ledPin21 = 21; //17 A3 m
// const int pinA3p20 = 20; //16 A2 l
// const int pinA4p19 = 19; //15 A1 k
// const int pinA5p18 = 18; //14 A0 j

// //don know where are those pins?
// const int ledPin17 = 17;
// const int ledPin16 = 16;
// const int ledPin15 = 15;
// const int ledPin14 = 14;

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
const int ledPin1 = 1; // TX
const int ledPin0 = 0; // RX  

//constan inputs
//Analog pins used as digital outputs
const int pinA0p23 = 23; //19 A5 o
const int pinA1p22 = 22; //18 A4 n
const int pinA2p21 = 21; //17 A3 m
const int pinA3p20 = 20; //16 A2 l
const int pinA4p19 = 19; //15 A1 k
const int pinA5p18 = 18; //14 A0 j



//////////////////////////////////////////////////////////////
// Variables will change:
int valor = 0;         // variable to store the data from the serial port

//////////////////////////////////////////////////////////////
void setup() {

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
  
  /////////////////////////////////////
  //set inputs 
  pinMode(ledPin0,INPUT); //RX
  pinMode(ledPin1,INPUT); //TX

  //Analog pins used as digital outputs
  pinMode(pinA5p18,INPUT); //14
  pinMode(pinA4p19,INPUT); //15
  pinMode(pinA3p20,INPUT); //16
  pinMode(pinA2p21,INPUT); //17
  pinMode(pinA1p22,INPUT); //18
  pinMode(pinA0p23,INPUT); //19

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

/*   digitalWrite(pinA4p19, HIGH);   // turn the LED on (HIGH is the voltage level) */
/*   delay(1000);                    // wait for a second */
/*   digitalWrite(ledPin14, HIGH);    // turn the LED off by making the voltage LOW */
/*   delay(1000);      // wait for a second */

  switch (valor) {
    //o
  case 63:
        spPrintValue(valor);
    //do something when var equals 1
    Serial.println("o 63 pin23 == o");
    digitalRead(pinA0p23);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   
   //n 
  case 62:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("n 62 pin22 == n");
    digitalRead(pinA1p22);   // turn the LED on (HIGH is the voltage level)
    delay(1000);

    break;  
  //m  
  case 61:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("m 61 pin21 == m");
    digitalRead(pinA2p21);   // turn the LED on (HIGH is the voltage level)
    delay(1000);

    break; 
    //l
  case 60:
        spPrintValue(valor);
    //do something when var equals 1
    Serial.println("l 60 pin20 == l");
    digitalRead(pinA3p20);   // turn the LED on (HIGH is the voltage level)
    delay(1000);

    break;   
//k
  case 59:
        spPrintValue(valor);
    //do something when var equals 1
    Serial.println("k 59 pin19 == k");
    digitalRead(pinA4p19);   // turn the LED on (HIGH is the voltage level)
    delay(1000);

    break;   
   //j 
  case 58:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("j 58 pin18 == j");
    digitalRead(pinA5p18);   // turn the LED on (HIGH is the voltage level)
    delay(1000);

    break;  

  //e   
  case 53:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("e pin13 == e");
    digitalWrite(ledPin13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin13, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
    //d
  case 52:
        spPrintValue(valor);
    //do something when var equals 1
    Serial.println("d pin13 == d");
    digitalWrite(ledPin13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin13, LOW);   // turn the LED on (HIGH is the voltage level)
    break;   
   //c 
  case 51:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("c pin12 == c");
    digitalWrite(ledPin12, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin12, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
  //b  
  case 50:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("b pin11 == b");
    digitalWrite(ledPin11, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin11, LOW);   // turn the LED on (HIGH is the voltage level)
    break; 
  //a   
  case 49:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("a pin10 == a");
    digitalWrite(ledPin10, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin10, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case 9:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("9 == a");
    digitalWrite(ledPin9, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin9, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 8:
      spPrintValue(valor);
    //do something when var equals 2
    Serial.println("8 == b");
    digitalWrite(ledPin8, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin8, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 7:
      spPrintValue(valor);
    //do something when var equals 1
    Serial.println("7 == a");
    digitalWrite(ledPin7, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin7, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 6:
    //do something when var equals 1
      spPrintValue(valor);
    Serial.println("6 == a");
    digitalWrite(ledPin6, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin6, LOW);   // turn the LED on (HIGH is the voltage level)
    break;
  case 5:
    //do something when var equals 1
    Serial.println("5 == a");
    digitalWrite(ledPin5, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin5, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    
  case 4:
    //do something when var equals 1
    Serial.println("4 == a");
    digitalWrite(ledPin4, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin4, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    

  case 3:
    //do something when var equals 1
    Serial.println("3 == a");
    digitalWrite(ledPin3, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin3, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    

  case 2:
    //do something when var equals 1
    Serial.println(" 2 == a");
    digitalWrite(ledPin2, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin2, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 1:
    //do something when var equals 1
    Serial.println("1 TX == 1");
    digitalWrite(ledPin1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin1, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    

  case 0:
    //do something when var equals 1
    Serial.println("0 RX == 0");
    digitalWrite(ledPin0, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(ledPin0, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    


  default: 
    break;

    // if nothing else matches, do the default
    // default is optional
  }

}

void spPrintValue(int valor){
    Serial.print("data: ");
    Serial.println(valor);
    delay(1000);
}

void spWriteStateOutput(){

} 

void spWriteStateInput(int pinInput){
  if(digitalRead(pinInput)==HIGH){
    spPrintValue(1);
  }else{
    spPrintValue(0);
  }
} 

