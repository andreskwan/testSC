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
const int oP7MoIzqOnOff = 7;
const int oP6MoDerOnOff = 6;

//constan inputs
//Analog pins used as digital outputs
const int iA0PilotoIzq = 23; //19 A5 o
const int iA1PilotoDer = 22; //18 A4 n
const int iA2PilotoGiroIzq = 21; //17 A3 m
const int iA3PilotoGiroDer = 20; //16 A2 l
const int iA4DoorIzqClose = 19; //15 A1 k
const int iA5DoorIzqOpen = 18; //14 A0 j

const int inTxDoorDerOpen = 1; // TX
const int inRxDoorDerClose = 0; // RX  

//////////////////////////////////////////////////////////////
// Variables will change:
int valor = 0;         // variable to store the data from the serial port

//////////////////////////////////////////////////////////////
void setup() {

//finales de carrera con logica invertida

  //Motores energizados          //       Pilotos activos     
  pinMode(oP6MoDerOnOff,OUTPUT); // 6  on iA1PilotoDer On if On
  pinMode(oP7MoIzqOnOff,OUTPUT); // 7  on iA0PilotoIzq On if On

  //puertas cerrandose           //       Pilotos de giro activos  
  pinMode(oP8DerClose,OUTPUT);   // 8  on iA3PilotoGiroDer On
                                 
                                 //       FC en on cuando se cierra
                                 //       inRxDoorDerClose when On todos Der a off                                   
                                 //               en off cuando los otros en on  
  pinMode(oP9IzqClose,OUTPUT);   // 9  on iA2PilotoGiroIzq On
                                 //       inTxDoorIzqClose when On todos Izq a off                                   
                                 //               en off cuando los otros en on  

  pinMode(oP10DerStop,OUTPUT);   // 10 on 
  pinMode(oP11IzqStop,OUTPUT);   // 11 on 

  pinMode(oP12DerOpen,OUTPUT);   // 12 on  
  pinMode(oP13IzqOpen,OUTPUT);   // 13 on 
  
  /////////////////////////////////////
  //info en los finales de carrera
  pinMode(inRxDoorDerClose,INPUT); //RX 0        
  pinMode(inTxDoorDerOpen,INPUT);  //TX 1    
  pinMode(iA5DoorIzqOpen,INPUT);   //14 j    
  pinMode(iA4DoorIzqClose,INPUT);  //15 k 59   

  //info de los pilotos
  //pilotos de giro
  pinMode(iA3PilotoGiroDer,INPUT); //16 l 60
  pinMode(iA2PilotoGiroIzq,INPUT); //17 m 61
  //pilotos energizar motores
  pinMode(iA1PilotoDer,INPUT);     //18 n 62
  pinMode(iA0PilotoIzq,INPUT);     //19 o 63

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
    spWriteStateInput(iA0PilotoIzq,"iA0PilotoIzq");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   
    //n 

  case 62:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("n 62 pin22 == n");
    spWriteStateInput(iA1PilotoDer,"iA1PilotoDer");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;  
    //m  

  case 61:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("m 61 pin21 == m");
    spWriteStateInput(iA2PilotoGiroIzq,"iA2PilotoGiroIzq");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break; 
    //l

  case 60:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("l 60 pin20 == l");
    spWriteStateInput(iA3PilotoGiroDer,"iA3PilotoGiroDer");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   
    //k

  case 59:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("k 59 pin19 == k");
    spWriteStateInput(iA4DoorIzqClose,"iA4DoorIzqClose");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   

    //j 
  case 58:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("j 58 pin18 == j");
    spWriteStateInput(iA5DoorIzqOpen,"iA5DoorIzqOpen");   // turn the LED on (HIGH is the voltage level)
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
    digitalWrite(oP7MoIzqOnOff, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP7MoIzqOnOff, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 6:
    //do something when var equals 1
    spPrintValue(valor);
    Serial.println("6 == a");
    digitalWrite(oP6MoDerOnOff, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP6MoDerOnOff, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 1:
    //do something when var equals 1
    //do something when var equals 1
    Serial.println("1 pin1 == 1");
    spWriteStateInput(inTxDoorDerOpen,"inTxDoorDerOpen");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;    

  case 0:
    //do something when var equals 1
    Serial.println("0 pin0 == 0");
    spWriteStateInput(inRxDoorDerClose,"inRxDoorDerClose");   // turn the LED on (HIGH is the voltage level)
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
