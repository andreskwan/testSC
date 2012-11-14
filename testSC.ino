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

/* const int ledPin5 = 5; */
/* const int ledPin4 = 4; */
/* const int ledPin3 = 3; */
/* const int ledPin2 = 2;    */
/* pinMode(ledPin2,OUTPUT); */
/* pinMode(ledPin3,OUTPUT);  */
/* pinMode(ledPin4,OUTPUT);  */
/* pinMode(ledPin5,OUTPUT);  */

//////////////////////////////////////////////////////////////
// constants outputs

//Rotaciones Motores
const int oP13IzqOpen = 13;
const int oP12DerOpen = 12;

//cortar la corriente 
const int oP11IzqStop = 11;
const int oP10DerStop = 10;

const int oP9IzqClose = 9;
const int oP8DerClose = 8;

//Encendido Motores
//quitar corriente en los motores
const int oP7MoIzqOn = 7;
const int oP6MoDerOn = 6;

//constan inputs
//Analog pins used as digital outputs
//pilotos motor
const int iA0IzqOn = 23; //19 A5 o
const int iA1DerOn = 22; //18 A4 n

//pilotos de giro
const int iA2GiroIzq = 21; //17 A3 m
const int iA3GiroDer = 20; //16 A2 l

//Finales de carrera
const int iA4IzqClose = 19; //15 A1 k
const int iA5IzqOpen = 18; //14 A0 j

const int iTxDerOpen = 1; // TX
const int iRxDerClose = 0; // RX  

//////////////////////////////////////////////////////////////
// Variables will change:
int valor = 0;         // variable to store the data from the serial port

//////////////////////////////////////////////////////////////
void setup() {

//finales de carrera con logica invertida

  //Motores energizados          //       Pilotos activos     
  pinMode(oP6MoDerOn,OUTPUT); // 6  on iA1DerOn On if On
  pinMode(oP7MoIzqOn,OUTPUT); // 7  on iA0IzqOn On if On

  //puertas cerrandose           //       Pilotos de giro activos  
  pinMode(oP8DerClose,OUTPUT);   // 8  on iA3PilotoGiroDer On
                                 
                                 //       FC en on cuando se cierra
                                 //       iRxDerClose when On todos Der a off                                   
                                 //               en off cuando los otros en on  
  pinMode(oP9IzqClose,OUTPUT);   // 9  on iA2PilotoGiroIzq On
                                 //       iTxIzqClose when On todos Izq a off                                   
                                 //               en off cuando los otros en on  

  pinMode(oP10DerStop,OUTPUT);   // 10 on 
  pinMode(oP11IzqStop,OUTPUT);   // 11 on 

  pinMode(oP12DerOpen,OUTPUT);   // 12 on  
  pinMode(oP13IzqOpen,OUTPUT);   // 13 on 
  
  /////////////////////////////////////
  //info en los finales de carrera
  pinMode(iRxDerClose,INPUT); //RX 0        
  pinMode(iA4IzqClose,INPUT);  //15 k 59   

  pinMode(iTxDerOpen,INPUT);  //TX 1    
  pinMode(iA5IzqOpen,INPUT);   //14 j    


  //info de los pilotos
  //pilotos de giro
  pinMode(iA3GiroDer,INPUT); //16 l 60
  pinMode(iA2GiroIzq,INPUT); //17 m 61
  //pilotos energizar motores
  pinMode(iA1DerOn,INPUT);     //18 n 62
  pinMode(iA0IzqOn,INPUT);     //19 o 63

  Serial.begin(9600);        // connect to the serial port
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop () {

  valor = Serial.read();      // read the serial port
  valor = valor - 48;

  switch (valor) {
    //Inputs

  case 63:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("o 63 pin23 == o");
    spWriteStateInput(iA0IzqOn,"iA0IzqOn");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   
    //n 

  case 62:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("n 62 pin22 == n");
    spWriteStateInput(iA1DerOn,"iA1DerOn");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;  
    //m  

  case 61:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("m 61 pin21 == m");
    spWriteStateInput(iA2GiroIzq,"iA2GiroIzq");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break; 
    //l

  case 60:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("l 60 pin20 == l");
    spWriteStateInput(iA3GiroDer,"iA3GiroDer");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   
    //k

  case 59:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("k 59 pin19 == k");
    spWriteStateInput(iA4IzqClose,"iA4IzqClose");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   

    //j 
  case 58:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("j 58 pin18 == j");
    spWriteStateInput(iA5IzqOpen,"iA5IzqOpen");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;  

    //d
  case 52:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("d pin13 == d");
    digitalWrite(oP13IzqOpen, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP13IzqOpen, LOW);   // turn the LED on (HIGH is the voltage level)
    break;   
    //c 

  case 51:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("c pin12 == c");
    digitalWrite(oP12DerOpen, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP12DerOpen, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
    //b  

  case 50:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("b pin11 == b");
    digitalWrite(oP11IzqStop, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP11IzqStop, LOW);   // turn the LED on (HIGH is the voltage level)
    break; 
    //a   

  case 49:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("a pin10 == a");
    digitalWrite(oP10DerStop, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP10DerStop, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    

  case 9:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("9 == a");
    digitalWrite(oP9IzqClose, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP9IzqClose, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 8:
    spPrintValue(valor);
    //do something when var equals 2
    Serial.println("8 == b");
    digitalWrite(oP8DerClose, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP8DerClose, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 7:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("7 == a");
    digitalWrite(oP7MoIzqOn, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP7MoIzqOn, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 6:
    //do something when var equals 1
    spPrintValue(valor);
    Serial.println("6 == a");
    digitalWrite(oP6MoDerOn, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP6MoDerOn, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 1:
    //do something when var equals 1
    //do something when var equals 1
    Serial.println("1 pin1 == 1");
    spWriteStateInput(iTxDerOpen,"iTxDerOpen");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;    

  case 0:
    //do something when var equals 1
    Serial.println("0 pin0 == 0");
    spWriteStateInput(iRxDerClose,"iRxDerClose");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;    

  default: 
    break;
  }

}

void spPrintValue(int valor){
  Serial.print("data: ");
  Serial.println(valor);
  delay(1000);
}

void spWriteStateOutput(){

} 

void spWriteStateInput(int pinInput,String pinName){
  Serial.print(pinName+" :");
  if(digitalRead(pinInput)==HIGH){
    spPrintValue(1);
  }else{
    spPrintValue(0);
  }
} 



/*   case 5: */
/*     //do something when var equals 1 */
/*     Serial.println("5 == a"); */
/*     digitalWrite(ledPin5, HIGH);   // turn the LED on (HIGH is the voltage level) */
/*     delay(1000); */
/*     digitalWrite(ledPin5, LOW);   // turn the LED on (HIGH is the voltage level) */
/*     break;     */
/*   case 4: */
/*     //do something when var equals 1 */
/*     Serial.println("4 == a"); */
/*     digitalWrite(ledPin4, HIGH);   // turn the LED on (HIGH is the voltage level) */
/*     delay(1000); */
/*     digitalWrite(ledPin4, LOW);   // turn the LED on (HIGH is the voltage level) */
/*     break;     */

/*   case 3: */
/*     //do something when var equals 1 */
/*     Serial.println("3 == a"); */
/*     digitalWrite(ledPin3, HIGH);   // turn the LED on (HIGH is the voltage level) */
/*     delay(1000); */
/*     digitalWrite(ledPin3, LOW);   // turn the LED on (HIGH is the voltage level) */
/*     break;     */

/*   case 2: */
/*     //do something when var equals 1 */
/*     Serial.println(" 2 == a"); */
/*     digitalWrite(ledPin2, HIGH);   // turn the LED on (HIGH is the voltage level) */
/*     delay(1000); */
/*     digitalWrite(ledPin2, LOW);   // turn the LED on (HIGH is the voltage level) */
/*     break; */
