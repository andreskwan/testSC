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

//NOTE
//JUST resturn error codes not messages. 
 
#include <SoftwareSerial.h>

//switch system state
const int OFF          = 0;
const int ON           = 1;

//switch door state
const int STOPPED      = 1;
const int MOVING       = 2;

//switch activating doors
const int CLOSE_DOOR   = 3;
const int OPEN_DOOR    = 4;
const int STOP_DOOR    = 5;

//SYSTEM ERRORS
//change error format err_1
const int ERR_CLOSE   = 6;
const int ERR_OPEN    = 7;
const int ERR_STOP    = 8;

const int ERR_ON    = 8;
const int ERR_OFF    = 9;

const int ERR_NOT_VALID = 53;

//const int DOORS_UNKNOW    = 3
//////////////////////////////////////////////////////////////
// constants outputs

//Rotaciones Motores
int oP13LOpen = 13;
int oP12ROpen = 12;

//cortar la corriente 
int oP11LStop = 11;
int oP10RStop = 10;

int oP9LClose = 9;
int oP8RClose = 8;

//Encendido Motores
//quitar corriente en los motores
int oP7MoLOn = 7;
int oP6MoROn = 6;

/////////////////////
//an inputs
/////////////////////
//Analog pins used as digital outputs
//pilotos motor
int iA0LOn = 23; //19 A5 o
int iA1ROn = 22; //18 A4 n

//pilotos de giro
int iA2TurnL = 21; //17 A3 m
int iA3TurnR = 20; //16 A2 l

//Finales de carrera
int iA4LClose = 19; //15 A1 k On in Low Off in High
int iA5LOpen = 18; //14 A0 j

int iTxROpen = 1; // TX
int iRxRClose = 0; // RX  

//////////////////////////////////////////////////////////////
// Variables will change:
int valor = 0;         // variable to store the data from the serial port
//if a left the value here it will keep the past value?
int order  = 0;

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

  identifyMotorsState();

  order  = Serial.read();      // read the serial port
  order  = order  - 48;
  //   order  = processUserOrder (valor);
  
  switch (doorsState()) {
  case STOPPED:
    activateDoors(order);
    break;
  case MOVING:
    stopDoors();
    break;
  default:
    Serial.print("Not valid DOORS STATE. ERR_NOT_VALID: " );
    Serial.println(ERR_NOT_VALID);
    Serial.print("Order: " );
    Serial.println(order);
  }
}

////////////////////////////////////////////////////////
// MOTORS
////////////////////////////////////////////////////////

//take in count
// if motors can't be started  
void identifyMotorsState(){
  switch (motorsState()){
  case ON:
    //system idle for too many time, turn off
    //for now, do nothing
    Serial.print("Motors are ON: " );
    break;
  case OFF:
    if(turnMotorsOn()){
      Serial.print("Motors has been Turn ON: " );
      Serial.println(ON);
    }else{
      Serial.print("Motors couldn't be started ERR_ON: " );
      Serial.println(ERR_ON);
    }
    break;
  default:
    Serial.print("Can't identify motor state. ERR_NOT_VALID: " );
    Serial.println(ERR_NOT_VALID);
  }
}

boolean turnMotorsOn(){
  digitalWrite(oP7MoLOn, HIGH);
  digitalWrite(oP6MoROn, HIGH);
  delay(500);
  if(isL_On() && isR_On()){
    return true;
  }
  return false;
}

int motorsState(){
  //motorsOn or Off
  /*     boolean isLOn = false; */
  /*     boolean isROn = false; */
  /*     if(isL_On() ){  */
  /*       isLOn = true; */
  /*     }else{ */
  /*       isLOn = false; */
  /*     } */

  /*     if(isR_On()){ */
  /*       isROn = true; */
  /*     }else{ */
  /*       isROn = false; */
  /*     } */
  //if true
  if(isL_On() && isR_On()){
    return ON;
  }else
    return OFF;
}


boolean isL_On(){
  if(iA0LOn == HIGH){
    Serial.println("Left motor ON");
    Serial.println(ON);
    return true;
  }
  Serial.println("Left motor OFF");
  return false;
}

boolean isR_On(){
  if(iA1ROn == HIGH){
    Serial.println("Righ motor ON");
    return true;
  }
  Serial.println("Righ motor OFF");
  return false;
}

////////////////////////////////////////////////////////
// DOORS
////////////////////////////////////////////////////////

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
  if((iA4LClose == HIGH) && (iA5LOpen == LOW)){
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
  if((iA4LClose == LOW) && (iA5LOpen == HIGH)){
    Serial.println("Left Door is OPEN");
    return true;
  }else{
    Serial.println("Left Door is NOT open");
    return false;
  }
}

void activateDoors(int order) {
  //deliver messsage to the server, so they could inform the user
  switch (order){
  case OPEN_DOOR:
    if(isOpeningDoors()){
      Serial.println("Doors is being opened. Order: " );
      Serial.println(order);
    }else{
      Serial.println("Doors can't be opened ERR_OPEN: " );
      Serial.println(ERR_OPEN);
    }
    break;
  case CLOSE_DOOR:
    if(isClosingDoors()){
	
    }else{
      Serial.println("Doors can't be closed ERR_CLOSE: " );
      Serial.println(ERR_CLOSE);
    }
    break;
  default:
    //not value order
    Serial.print("Not valid order ERR_NOT_VALID: " );
    Serial.println(ERR_NOT_VALID);
  }
}

void stopDoors() {
  //deliver messsage to the server, so they could inform the user
  if(isStopingDoors()){
	
  }else{
    Serial.println("Doors can't be opened ERR_OPEN: " );
    Serial.println(ERR_OPEN);
  }
}
  
boolean isOpeningDoors(){
  //pilotos inputs on
  //outputs HIGH
  return true;
}

boolean isClosingDoors(){
  return true;
}

boolean isStopingDoors(){
  return true;
}


void spPrintValue(int valor){
  Serial.print("data: ");
  Serial.println(valor);
  delay(1000);
}

void spWriteStateOutput(){

} 

void spWriteStateInput(int pinInput,String pinName){
  Serial.print(pinName+" : " );
  if(digitalRead(pinInput)==HIGH){
    spPrintValue(1);
  }else{
    spPrintValue(0);
  }
} 
//user order 

/* int processUserOrder(int valor){ */
/*   //from ascii number to one to one representation */
/*   valor = valor - 48; */

/*   switch (valor){ */
/*   case */
/*     } */
/*   return valor; */
/* } */

