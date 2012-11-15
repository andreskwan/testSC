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
const int UNSTABLE     = 1;

//switch door state
const int STOPPED             = 1;
const int MOVING              = 2;
const int TURNING_LEFT        = 2;
const int TURNING_RIGHT       = 2;

//switch activating doors
const int CLOSE_DOORS   = 3;
const int OPEN_DOORS    = 4;
const int STOP_DOORS    = 5;

//SYSTEM ERRORS
//change error format err_1
const int ERR_CLOSE          = 6;
const int ERR_OPEN           = 7;
const int ERR_STOP           = 8;

const int ERR_ON             = 8;
const int ERR_OFF            = 9;
const int ERR_NOT_VALID      = 53;

const int NOT_TURNING_LEFT   = 2;
const int NOT_TURNING_RIGHT  = 2;

const int MOTORS_TURNING = 2;
const int MOTORS_NOT_TURNING = 2;

//const int DOORSS_UNKNOW    = 3
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
//A0 = Tx
//A1 = Rx 
// asi lo quiero
//int iA0ROpen  = 23; //19 A5 o
//int iA1RClose = 22; //18 A4 n
/* int iTxLOn = 1; // TX */
/* int iRxROn = 0; // RX   */

//asi debo modificarlo para hacer las pruebas
// iRxROn por iA0ROn 23
// iTxLOn por iA1LOn 22
//y
int iTxLOn = 1; // TX

int iRxROn = 0; // RX  
//lugo de la prueba devolver
// iA0ROpen  = iA0ROn 23
// iA1RClose = iA1LOn 22

int iA0ROn  = 23; //19 A5 o

int iA1LOn  = 22; //18 A4 n


//pilotos de giro
int iA2TurnL = 21; //17 A3 m

int iA3TurnR = 20; //16 A2 l


//Finales de carrera
int iA4LClose = 19; //15 A1 k On in Low Off in High

int iA5LOpen = 18; //14 A0 j


//////////////////////////////////////////////////////////////
// Variables will change:
int valor = 0;         // variable to store the data from the serial port
//if a left the value here it will keep the past value?
int order  = 0;

//////////////////////////////////////////////////////////////
void setup() {

  //finales de carrera con logica invertida
  //Motores energizados          //       Pilotos activos     
  pinMode(oP6MoROn,OUTPUT); // 6  on iA0ROn On if On
  pinMode(oP7MoLOn,OUTPUT); // 7  on iTxLOn On if On

  //puertas cerrandose           //       Pilotos de giro activos  
  pinMode(oP8RClose,OUTPUT);   // 8  on iA3PilotoTurnR On
                                 
  //       FC en on cuando se cierra
  //      iA1LOn when On todos R a off                                   
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
  //  pinMode(iA1RClose,INPUT); //RX 0  
      
  pinMode(iA4LClose,INPUT);  //15 k 59   

  pinMode(iA0ROn,INPUT);  //TX 1    
  pinMode(iA1LOn,INPUT);  //RX 1    

  pinMode(iA5LOpen,INPUT);   //14 j    

  //info de los pilotos
  //pilotos de giro
  pinMode(iA2TurnL,INPUT); //17 m 61
  pinMode(iA3TurnR,INPUT); //16 l 60

  //pilotos energizar motores
  pinMode(iA0ROn,INPUT);     //18 n 62
  pinMode(iTxLOn,INPUT);     //19 o 63

/*   digitalWrite(iTxLOn,HIGH); */
/*   digitalWrite(iRxROn,HIGH); */
/*   digitalWrite(iA0ROn,HIGH); */
/*   digitalWrite(iA1LOn,HIGH); */
/*   digitalWrite(iA2TurnL,HIGH); */
/*   digitalWrite(iA3TurnR,HIGH); */
/*   digitalWrite(iA4LClose,HIGH); */
/*   digitalWrite(iA5LOpen,HIGH); */


  Serial.begin(9600);        // connect to the serial port
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop () {

  order  = Serial.read();      // read the serial port
  order  = order  - 48;

  identifyMotorsState();
  /*   //   order  = processUserOrder (valor); */
  /*   identifyDoorsState(); */

  /*   switch (doorsState()) { */
  /*   case STOPPED: */
  /*     activateDoors(order); */
  /*     break; */
  /*   case MOVING: */
  /*     stopDoors(); */
  /*     break; */
  /*   default: */
  /*     Serial.print("Not valid DOORSS STATE. ERR_NOT_VALID: " ); */
  /*     Serial.println(ERR_NOT_VALID); */
  /*     Serial.print("Order: " ); */
  /*     Serial.println(order); */
  /*   } */
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
    Serial.println("Motors are ON: " );
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
  case UNSTABLE:
    Serial.print("Can't identify motor state. UNSTABLE: " );
    Serial.println(UNSTABLE);
    break;
  default:
    Serial.print("NOT valid state. ERR_NOT_VALID: " );
    Serial.println(ERR_NOT_VALID);
  }
}
//DONE
int motorsState(){
  Serial.println("*******************************");
  Serial.println("inside motorsState()");
  if(areMotorsOn()){
    return ON;
  }else if(areMotorsOff()){
    return OFF;
  }else{
    return UNSTABLE;
  }
         
}

boolean areMotorsOn(){
  if(isR_On() && isL_On()){
    Serial.println("Both motors ON");
    //    Serial.println("*******************************");
    return true;
  }else{ 
    Serial.println("NOT Both motors ON");
    Serial.println("*******************************");
    return false;
  }
}

boolean areMotorsOff(){
  if(!isR_On() && !isL_On()){
    Serial.println("Both motors OFF");
    Serial.println("*******************************");
    return true;
  }else{ 
    Serial.println("NOT Both motors OFF");
    Serial.println("*******************************");
    return false;
  }
}

//DONE
boolean isL_On(){
  Serial.println("************************");
  Serial.println("inside isL_On()");

  if(digitalRead(iA1LOn) == HIGH){
    Serial.println("Left motor ON");
    Serial.println(ON);
    Serial.println("************************");
    return true;
  }
  Serial.println("Left motor OFF");
  Serial.println("************************");
  return false;
}
//DONE
boolean isR_On(){
  Serial.println("************************");
  Serial.println("inside isR_On()");

  if(digitalRead(iA0ROn) == HIGH){
    Serial.println("Righ motor ON");
    Serial.println("************************");
    return true;
  }
  Serial.println("Righ motor OFF");
  Serial.println("************************");
  return false;
}

//DONE
boolean turnMotorsOn(){
  digitalWrite(oP7MoLOn, HIGH);
  digitalWrite(oP6MoROn, HIGH);
  delay(500);
  if(isR_On() && isL_On()){
    return true;
  }
  return false;
}

/* //DONE */
/* boolean isL_Turning(){ */
/*   if((digitalRead(iA2TurnL) == HIGH)){ */
/*     Serial.println("TURNING_LEFT"); */
/*     Serial.println(TURNING_LEFT); */
/*     return true; */
/*   } */
/*   Serial.println("NOT_TURNING_LEFT"); */
/*   Serial.println(NOT_TURNING_LEFT); */
/*   return false; */
/* } */
/* //DONE */
/* boolean isR_Turning(){ */
/*   if((digitalRead(iA2TurnL) == HIGH)){ */
/*     Serial.println("TURNING_RIGHT"); */
/*     Serial.println(TURNING_RIGHT); */
/*     return true; */
/*   } */
/*   Serial.println("NOT_TURNING_RIGHT"); */
/*   Serial.println(NOT_TURNING_RIGHT); */
/*   return false; */
/* } */

/* boolean areMotorsTurning(){ */
/*   if(isL_Turning() && isR_Turning()){ */
/*     Serial.println("MOTORS_TURNING"); */
/*     Serial.println(MOTORS_TURNING); */
/*     return true; */
/*   } */
/*   Serial.println("MOTORS_NOT_TURNING"); */
/*   Serial.println(MOTORS_NOT_TURNING); */

/*   return false; */
/* } */

/* //////////////////////////////////////////////////////// */
/* // DOORSS */
/* //////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////////// */
/* // Identify doors state */

/* //Return: STOPPED, DOORSS_CLOSE, DOORSS_UNKNOW */
/* int doorsState(){ */
/*   areDoorsCompletelyOpen(); */
/*   areDoorsCompletelyClose(); */
/*   } */

/* boolean areDoorsCompletelyOpen(){ */

/* } */
/* boolean isL_Open(){ */
/*   digitalRead(iA5LOpen); */
/* } */

/* boolean isR_Open(){ */

/* } */


/* //prerrequisitos */
/* //- la puerta debe estar cerrada o indeterminada */
/* //- los motores deben estar energizados */
/* int open(){ */
/*   if(isDoorOpen()){ */
/*     Serial.println(STOPPED); */
/*   } */
/* } */



/* //Do: revisa los estados de los finales de carrera para identificar si */
/* //    esta abierta, */
/* //verifica: las dos puertas. */
/* boolean isDoorOpen(){ */

/*   return true; */
/* } */
/* //////////////////////////////////////////////////////////////////////////////////////////////////// */
/* // Left door states */
/* //////////////////////////////////////////////////////////////////////////////////////////////////// */

/* //Do: check if left door is open */
/* // */
/* //Prerrequisites: system on */
/* boolean isLDoorOpen(){ */
/*   //maybe missing digitalRead() */

/*   if((digitalRead(iA5LOpen) == LOW) && (digitalRead(iA4LClose) == HIGH)){ */
/*     Serial.println("Left Door is OPEN"); */
/*     return true; */
/*   }else{ */
/*     Serial.println("Left Door is NOT open"); */
/*     return false; */
/*   } */
/* } */

/* //Do: check if left door is open */
/* // */
/* //Prerrequisites: system on */
/* boolean isLDoorClose(){ */
/*   // */
/*   if( (digitalRead(iA5LOpen) == HIGH) && (digitalRead(iA4LClose) == LOW)){ */
/*     Serial.println("Left Door is OPEN"); */
/*     return true; */
/*   }else{ */
/*     Serial.println("Left Door is NOT open"); */
/*     return false; */
/*   } */
/* } */

/* //////////////////////////////////////////////////////////////////////////////////////////////////// */
/* // Right door */
/* //////////////////////////////////////////////////////////////////////////////////////////////////// */
/* //Do: check if left door is open */
/* // */
/* //Prerrequisites: system on */
/* boolean isLDoorOpen(){ */
/*   //maybe missing digitalRead() */

/*   if((iA4LClose == HIGH) && (iA5LOpen == LOW)){ */
/*     Serial.println("Left Door is OPEN"); */
/*     return true; */
/*   }else{ */
/*     Serial.println("Left Door is NOT open"); */
/*     return false; */
/*   } */
/* } */


/* //Do: check if left door is open */
/* // */
/* //Prerrequisites: system on */
/* boolean isRDoorClose(){ */
/*   // */
/*   if((iA LClose == LOW) && (iA5 Open == HIGH)){ */
/*     Serial.println("Left Door is OPEN"); */
/*     return true; */
/*   }else{ */
/*     Serial.println("Left Door is NOT open"); */
/*     return false; */
/*   } */
/* } */

/* int  identifyDoorsState() { */
/*   if(areDoors){ */
/*   } */
/*   switch (doorsState()) { */
/*   case STOPPED: */
/*     activateDoors(order); */
/*     break; */
/*   case MOVING: */
/*     stopDoors(); */
/*     break; */
/*   default: */
/*     Serial.print("Not valid DOORSS STATE. ERR_NOT_VALID: " ); */
/*     Serial.println(ERR_NOT_VALID); */
/*     Serial.print("Order: " ); */
/*     Serial.println(order); */
/*   } */
/* } */

/* void activateDoors(int order) { */
/*   //deliver messsage to the server, so they could inform the user */
/*   switch (order){ */
/*   case OPEN_DOORS: */
/*     if(isOpeningDoors()){ */
/*       Serial.println("Doors is being opened. Order: " ); */
/*       Serial.println(order); */
/*     }else{ */
/*       Serial.println("Doors can't be opened ERR_OPEN: " ); */
/*       Serial.println(ERR_OPEN); */
/*     } */
/*     break; */
/*   case CLOSE_DOORS: */
/*     if(isClosingDoors()){ */
	
/*     }else{ */
/*       Serial.println("Doors can't be closed ERR_CLOSE: " ); */
/*       Serial.println(ERR_CLOSE); */
/*     } */
/*     break; */
/*   default: */
/*     //not value order */
/*     Serial.print("Not valid order ERR_NOT_VALID: " ); */
/*     Serial.println(ERR_NOT_VALID); */
/*   } */
/* } */

/* void stopDoors() { */
/*   //deliver messsage to the server, so they could inform the user */
/*   if(isStopingDoors()){ */
	
/*   }else{ */
/*     Serial.println("Doors can't be opened ERR_OPEN: " ); */
/*     Serial.println(ERR_OPEN); */
/*   } */
/* } */
  
/* boolean isOpeningDoors(){ */
/*   digitalWrite(oP13LOpen, HIGH); */
/*   digitalWrite(oP12ROpen, HIGH); */
/*   delay(500); */
/*   return areMotorsTurning(); */
/* } */

/* boolean isClosingDoors(){ */
/*   digitalWrite(oP9LClose, HIGH); */
/*   digitalWrite(oP8RClose, HIGH); */
/*   delay(500); */
/*   //must return true */
/*   return areMotorsTurning(); */
/* } */

/* boolean wereDoorsStopped(){ */
/*   digitalWrite(oP11LStop, HIGH); */
/*   digitalWrite(oP10RStop, HIGH); */
/*   delay(500); */
/*   //must return false  */
/*   return areMotorsTurning(); */
/* } */


/* ///////////////////////////////// */
/* //serial functions */
/* void spPrintValue(int valor){ */
/*   Serial.print("data: "); */
/*   Serial.println(valor); */
/*   delay(1000); */
/* } */

/* void spWriteStateOutput(){ */

/* }  */

/* void spWriteStateInput(int pinInput,String pinName){ */
/*   Serial.print(pinName+" : " ); */
/*   if(digitalRead(pinInput)==HIGH){ */
/*     spPrintValue(1); */
/*   }else{ */
/*     spPrintValue(0); */
/*   } */
/* }  */
/* //user order  */

/* /\* int processUserOrder(int valor){ *\/ */
/* /\*   //from ascii number to one to one representation *\/ */
/* /\*   valor = valor - 48; *\/ */

/* /\*   switch (valor){ *\/ */
/* /\*   case *\/ */
/* /\*     } *\/ */
/* /\*   return valor; *\/ */
/* /\* } *\/ */

