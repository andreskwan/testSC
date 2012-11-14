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

const int STOPPED      = 1;
const int MOVING       = 2;

const int CLOSE_DOOR   = 3;
const int OPEN_DOOR    = 4;

  //const int DOORS_UNKNOW    = 3
//////////////////////////////////////////////////////////////
// constants outputs

//Rotaciones Motores
const int oP13LOpen = 13;
const int oP12ROpen = 12;

//cortar la corriente 
const int oP11LStop = 11;
const int oP10RStop = 10;

const int oP9LClose = 9;
const int oP8RClose = 8;

//Encendido Motores
//quitar corriente en los motores
const int oP7MoLOn = 7;
const int oP6MoROn = 6;

//constan inputs
//Analog pins used as digital outputs
//pilotos motor
const int iA0LOn = 23; //19 A5 o
const int iA1ROn = 22; //18 A4 n

//pilotos de giro
const int iA2TurnL = 21; //17 A3 m
const int iA3TurnR = 20; //16 A2 l

//Finales de carrera
const int iA4LClose = 19; //15 A1 k On in Low Off in High
const int iA5LOpen = 18; //14 A0 j

const int iTxROpen = 1; // TX
const int iRxRClose = 0; // RX  

//////////////////////////////////////////////////////////////
// Variables will change:
int valor = 0;         // variable to store the data from the serial port

//////////////////////////////////////////////////////////////
void setup() {

//finales de carrera con logica invertida

  //Motores energizados          //       Pilotos activos     
  pinMode(oP6MoROn,OUTPUT); // 6  on iA1ROn On if On
  pinMode(oP7MoLOn,OUTPUT); // 7  on iA0LOn On if On

  //puertas cerrandose           //       Pilotos de giro activos  
  pinMode(oP8RClose,OUTPUT);   // 8  on iA3PilotoTurnR On
                                 
                                 //       FC en on cuando se cierra
                                 //       iRxRClose when On todos R a off                                   
                                 //               en off cuando los otros en on  
  pinMode(oP9LClose,OUTPUT);   // 9  on iA2PilotoTurnL On
                                 //       iTxLClose when On todos L a off                                   
                                 //               en off cuando los otros en on  

  pinMode(oP10RStop,OUTPUT);   // 10 on 
  pinMode(oP11LStop,OUTPUT);   // 11 on 

  pinMode(oP12ROpen,OUTPUT);   // 12 on  
  pinMode(oP13LOpen,OUTPUT);   // 13 on 
  
  /////////////////////////////////////
  //info en los finales de carrera
  pinMode(iRxRClose,INPUT); //RX 0        
  pinMode(iA4LClose,INPUT);  //15 k 59   

  pinMode(iTxROpen,INPUT);  //TX 1    
  pinMode(iA5LOpen,INPUT);   //14 j    


  //info de los pilotos
  //pilotos de giro
  pinMode(iA3TurnR,INPUT); //16 l 60
  pinMode(iA2TurnL,INPUT); //17 m 61
  //pilotos energizar motores
  pinMode(iA1ROn,INPUT);     //18 n 62
  pinMode(iA0LOn,INPUT);     //19 o 63

  Serial.begin(9600);        // connect to the serial port
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop () {

  valor = Serial.read();      // read the serial port
  valor = valor - 48;

  
  switch (doorsState()) {
  case STOPPED:
    //deliver messsage to the server, so they could inform the user
    switch (orden){
    case OPEN_DOOR:
      break;
    case CLOSE_DOOR:
      break;
    default 
      ;  
    }

    break;
  case MOVING:
    //deliver messsage to the server, so they could inform the user
    break;
  default:
    //this should never happen
  }
  switch (valor) {
    //Inputs

  case 63:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("o 63 pin23 == o");
    spWriteStateInput(iA0LOn,"iA0LOn");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   
    //n 

  case 62:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("n 62 pin22 == n");
    spWriteStateInput(iA1ROn,"iA1ROn");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;  
    //m  

  case 61:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("m 61 pin21 == m");
    spWriteStateInput(iA2TurnL,"iA2TurnL");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break; 
    //l

  case 60:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("l 60 pin20 == l");
    spWriteStateInput(iA3TurnR,"iA3TurnR");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   
    //k

  case 59:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("k 59 pin19 == k");
    spWriteStateInput(iA4LClose,"iA4LClose");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;   

    //j 
  case 58:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("j 58 pin18 == j");
    spWriteStateInput(iA5LOpen,"iA5LOpen");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;  

    //d
  case 52:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("d pin13 == d");
    digitalWrite(oP13LOpen, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP13LOpen, LOW);   // turn the LED on (HIGH is the voltage level)
    break;   
    //c 

  case 51:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("c pin12 == c");
    digitalWrite(oP12ROpen, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP12ROpen, LOW);   // turn the LED on (HIGH is the voltage level)
    break;  
    //b  

  case 50:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("b pin11 == b");
    digitalWrite(oP11LStop, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP11LStop, LOW);   // turn the LED on (HIGH is the voltage level)
    break; 
    //a   

  case 49:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("a pin10 == a");
    digitalWrite(oP10RStop, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP10RStop, LOW);   // turn the LED on (HIGH is the voltage level)
    break;    

  case 9:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("9 == a");
    digitalWrite(oP9LClose, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP9LClose, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 8:
    spPrintValue(valor);
    //do something when var equals 2
    Serial.println("8 == b");
    digitalWrite(oP8RClose, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP8RClose, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 7:
    spPrintValue(valor);
    //do something when var equals 1
    Serial.println("7 == a");
    digitalWrite(oP7MoLOn, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP7MoLOn, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 6:
    //do something when var equals 1
    spPrintValue(valor);
    Serial.println("6 == a");
    digitalWrite(oP6MoROn, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(oP6MoROn, LOW);   // turn the LED on (HIGH is the voltage level)
    break;

  case 1:
    //do something when var equals 1
    //do something when var equals 1
    Serial.println("1 pin1 == 1");
    spWriteStateInput(iTxROpen,"iTxROpen");   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    break;    

  case 0:
    //do something when var equals 1
    Serial.println("0 pin0 == 0");
    spWriteStateInput(iRxRClose,"iRxRClose");   // turn the LED on (HIGH is the voltage level)
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
////////////////////////////////////////////////////////////////////////
// Identify doors state

//Return: STOPPED, DOORS_CLOSE, DOORS_UNKNOW
int doorsState(){

}


//prerrequisitos
//- la puerta debe estar cerrada o indeterminada
//- los motores deben estar energizados
int open(){
  if(isDoorOpen()){
    Serial.println(STOPPED);
 }

  //Do: revisa los estados de los finales de carrera para identificar si 
  //    esta abierta,
  //verifica: las dos puertas.  
  boolean isDoorOpen(){

    return true;
  } 

  //Do: check if left door is open
  //
  //Prerrequisites: system on   
  boolean isDoorLeftOpen(){
    if((iA4LClose == HIGH) && (iA5LOpen == LOW){
	Serial.println("Left Door is OPEN");
	return true;
      }else{
	Serial.println("Left Door is NOT open");
	return false;
      }
  } 

  //Do: check if left door is open
  //
  //Prerrequisites: system on   
  boolean isDoorLeftClose(){
    //
    if((iA4LClose == LOW) && (iA5LOpen == HIGH){
	Serial.println("Left Door is OPEN");
	return true;
      }else{
	Serial.println("Left Door is NOT open");
	return false;
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
