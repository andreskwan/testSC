///////////////////////////////////////////////////////////////////////////////////////////
// Open loop version  (No Imputs)
///////////////////////////////////////////////////////////////////////////////////////////


/* Just testing seria port communication and pins in the Leonardo board
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

//switch activating doors
const int OPEN      = 2;
const int OPEN_L    = 2;
const int OPEN_R    = 2;

const int CLOSE     = 3;
const int CLOSE_L   = 3;
const int CLOSE_R   = 3;

const int STOP      = 4;
const int STOP_L    = 4;
const int STOP_R    = 4;

const int MIDDLE    = 5;
 
//FEEDBACK
//switch door state
const int STOPPED             = 1;
const int MOVING              = 2;
const int TURNING_LEFT        = 0x2;
const int TURNING_RIGHT       = 0x3;


//SYSTEM ERRORS
//change error format err_1
const int ERR_CLOSE          = 6;
const int ERR_OPEN           = 7;
const int ERR_STOP           = 8;

const int ERR_ON             = 8;
const int ERR_OFF            = 9;
const int ERR_NOT_VALID      = 53;

const int NOT_TURNING_LEFT   = 0xE2;
const int NOT_TURNING_RIGHT  = 0xE3;

const int MOTORS_TURNING = 2;
const int MOTORS_NOT_TURNING = 2;

//const int DOORSS_UNKNOW    = 3
//////////////////////////////////////////////////////////////
// constants outputs

//Rotaciones Motores
int oP13LOpen = 13;
int oP12ROpen = 12;

//cortar la corriente 
int oP11LStop = 4;
int oP10RStop = 5;

int oP9LClose = 11;
int oP8RClose = 10;

//Encendido Motores
//quitar corriente en los motores
int oP7MoLOn = 2;
int oP6MoROn = 3;

/////////////////////
//an inputs
/////////////////////
/** \brief iTx Right door close */
int iTx = 1; // TX iTxRClose = 1; // TX
/** \brief iTx Left door close */
int iRx = 0; // RX iTxROpen  = 0; // TX 

//////////////////////////////////////////////////////////////
// Variables will change:
int valor = 0;         // variable to store the data from the serial port
//if a left the value here it will keep the past value?
int order  = 0;

//////////////////////////////////////////////////////////////
void setup() {

  //Motores energizados          //       Pilotos activos     
  pinMode(oP6MoROn,OUTPUT); // 6  on A0 On if On
  pinMode(oP7MoLOn,OUTPUT); // 7  on iTxLOn On if On

  //finales de carrera con logica invertida
  //puertas cerrandose           //       Pilotos de giro activos  
  pinMode(oP8RClose,OUTPUT);   // 8  on iA3PilotoTurnR On
  pinMode(oP9LClose,OUTPUT);   // 9  on iA2PilotoTurnL On

  pinMode(oP10RStop,OUTPUT);   // 10 on 
  pinMode(oP11LStop,OUTPUT);   // 11 on 

  pinMode(oP12ROpen,OUTPUT);   // 12 on  
  pinMode(oP13LOpen,OUTPUT);   // 13 on 
  
  /////////////////////////////////////
  //info en los finales de carrera
  //  pinMode(iA1RClose,INPUT); //RX 0  

  //motors
  pinMode(A0,INPUT);  //R_M_On    
  pinMode(A1,INPUT);  //L_M_On    

  //info de los pilotos
  //pilotos de giro
  pinMode(A2,INPUT);   //turnL
  pinMode(A3,INPUT);   //turnR
 
  //Right limit switch
  pinMode(iTx,INPUT);  //RClose
  pinMode(iRx,INPUT);  //ROpen
  //Left limit switch
  pinMode(A4,INPUT);   //LClose
  pinMode(A5,INPUT);   //LOpen

  Serial.begin(9600);        // connect to the serial port
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop () {
  //  Serial.println("Set order: " );
  order  = Serial.read();      // read the serial port
  order  = order  - 48;

  //////////////////////////////
  //OpenLoop
  //////////////////////////////
  //test outputs
  //  openLoopControl(order);
  
  //////////////////////////////
  //feeback
  //////////////////////////////
  // closeLoopControl(order);

  //   identifyMotorsState();

  //////////////////////////////
  //test methods inputs
  //////////////////////////////
  //  working
  //  testMotorsOnOff();

  //  
  //test pilotos de giro
  //  working
  //  testTurning();
  //  delay(1000);

  //testLimitSwitch();
  delay(1200);
}
////////////////////////////////////////////////////////
//open loop control
////////////////////////////////////////////////////////
//falta 
//todo por separado
void  openLoopControl(int order) {
  //feeback
  switch (order){

  case OFF://0
    turnMotorsOff();
    delay(1000);
    break;

  case ON://1
    turnMotorsOn();
    delay(1000);
    break;

  case OPEN://2
    doors(OPEN);
    delay(1000);
    break;

/*   case OPEN_L://2 */
/*     doors(OPEN_L); */
/*     delay(1000); */
/*     break; */

/*   case OPEN_R://2 */
/*     doors(OPEN_R); */
/*     delay(1000); */
/*     break; */

  case CLOSE://3
    doors(CLOSE);
    delay(1000);
    break;

/*   case CLOSE_L://3 */
/*     doors(CLOSE_L); */
/*     delay(1000); */
/*     break; */

/*   case CLOSE_R://3 */
/*     doors(CLOSE_R); */
/*     delay(1000); */
/*     break; */

  case STOP://4
    doors(STOP);//
    delay(1000);
    break;

/*   case STOP_L://4 */
/*     doors(STOP);// */
/*     delay(1000); */
/*     break; */

/*   case STOP_R://4 */
/*     doors(STOP);// */
/*     delay(1000); */
/*     break; */

  default:
    ;
   }
  delay(1000);
}

////////////////////////////////////////////////////////
//close loop control
////////////////////////////////////////////////////////
void closeLoopControl(int order){

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
  default:
    Serial.print("Can't identify motor state. ERR_NOT_VALID: " );
    Serial.println(ERR_NOT_VALID);
  }
}

//DONE
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
  Serial.println("*******************************");
  Serial.println("inside motorsState()");
  if(isL_On() && isR_On()){
    Serial.println("Both motors ON");
    Serial.println("*******************************");
    return ON;
  }else{ 
    Serial.println("Both motors OFF");
    Serial.println("*******************************");
    return OFF;
  }
}

//DONE
boolean turnMotorsOn(){
  digitalWrite(oP7MoLOn, HIGH);
  digitalWrite(oP6MoROn, HIGH);
  delay(500);
  if(isL_On() && isR_On()){
    return true;
  }
  return false;
}

//DONE
boolean turnMotorsOff(){
  digitalWrite(oP7MoLOn, LOW);
  digitalWrite(oP6MoROn, LOW);
  delay(500);
  if(isL_On() && isR_On()){
    return true;
  }
  return false;
}

//DONE
boolean isL_On(){
  Serial.println("************************");
  Serial.println("inside isL_On()");

  if(digitalRead(A1) == HIGH){
    Serial.println("Left motor ON");
    Serial.println(ON);
    Serial.println("************************");
    return true;
  }
  Serial.println("Left motor OFF");
  Serial.println(OFF);
  Serial.println("************************");
  return false;
}
//DONE
boolean isR_On(){
  Serial.println("************************");
  Serial.println("inside isR_On() digitalRead(A0)");
  Serial.println(digitalRead(A0));
  if(digitalRead(A0) == HIGH){
    Serial.println("Righ motor ON");
    Serial.println(ON);
    Serial.println("************************");
    return true;
  }
  Serial.println("Righ motor OFF");
  Serial.println(OFF);
  Serial.println("************************");
  return false;}


//DONE
boolean isL_Turning(){
  if((digitalRead(A2) == HIGH)){
    Serial.println("IS TURNING_LEFT");
    Serial.println(TURNING_LEFT);
    return true;
  }
  Serial.println("NOT_TURNING_LEFT");
  Serial.println(NOT_TURNING_LEFT);
  return false;
}
//DONE
boolean isR_Turning(){
  if((digitalRead(A3) == HIGH)){
    Serial.println("IS TURNING_RIGHT");
    Serial.println(TURNING_RIGHT);
    return true;
  }
  Serial.println("NOT_TURNING_RIGHT");
  Serial.println(NOT_TURNING_RIGHT);
  return false;
}

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

////////////////////////////////////////////////////////
// DOORS
////////////////////////////////////////////////////////
//openLoop
/* void doors(int order){ */

/*   if(order == OPEN){ */
/*     digitalWrite(oP9LClose,LOW); */
/*     digitalWrite(oP8RClose,LOW); */

/*     digitalWrite(oP11LStop,LOW); */
/*     digitalWrite(oP10RStop,LOW); */

/*     digitalWrite(oP13LOpen,HIGH); */
/*     digitalWrite(oP12ROpen,HIGH); */
/*   }else if(order == CLOSE){ */
/*     digitalWrite(oP13LOpen,LOW); */
/*     digitalWrite(oP12ROpen,LOW); */

/*     digitalWrite(oP11LStop,LOW); */
/*     digitalWrite(oP10RStop,LOW); */

/*     digitalWrite(oP9LClose,HIGH); */
/*     digitalWrite(oP8RClose,HIGH); */
/*   }else{ */
/*     digitalWrite(oP13LOpen,LOW); */
/*     digitalWrite(oP12ROpen,LOW); */

/*     digitalWrite(oP9LClose,LOW); */
/*     digitalWrite(oP8RClose,LOW); */

/*     digitalWrite(oP11LStop,HIGH); */
/*     digitalWrite(oP10RStop,HIGH); */

/*   } */
/* } */

void doors(int order){
  switch(order){
  case OPEN:
    digitalWrite(oP9LClose,LOW);
    digitalWrite(oP8RClose,LOW);

    digitalWrite(oP11LStop,LOW);
    digitalWrite(oP10RStop,LOW);

    digitalWrite(oP13LOpen,HIGH);
    digitalWrite(oP12ROpen,HIGH);
    break;
  case CLOSE:
    digitalWrite(oP13LOpen,LOW);
    digitalWrite(oP12ROpen,LOW);

    digitalWrite(oP11LStop,LOW);
    digitalWrite(oP10RStop,LOW);

    digitalWrite(oP9LClose,HIGH);
    digitalWrite(oP8RClose,HIGH);
    break;
  case STOP:
    digitalWrite(oP13LOpen,LOW);
    digitalWrite(oP12ROpen,LOW);

    digitalWrite(oP9LClose,LOW);
    digitalWrite(oP8RClose,LOW);

    digitalWrite(oP11LStop,HIGH);
    digitalWrite(oP10RStop,HIGH);
    break;
/*   case OPEN_L: */
/*     digitalWrite(oP9LClose,LOW); */
/*     break; */
/*   case OPEN_R: */
    
/*     break; */
  }
/*   case CLOSE_L: */
    
/*     break; */
/*   case CLOSE_R: */
    
//    break;
}

/* void openDoors(int order){ */
/*   if(order == OPEN){ */
/*     openDoors(order); */
/*     digitalWrite(oP13LOpen,HIGH); */
/*     digitalWrite(oP12ROpen,HIGH); */
/*   }else if(order == CLOSE){ */
/*     digitalWrite(oP13LOpen,LOW); */
/*     digitalWrite(oP12ROpen,LOW); */
/*   } */
/* } */

/* void closeDoors(int order){ */
/*     if(order == CLOSE){ */
/*       openDoors(order); */
/*       digitalWrite(oP9LClose,HIGH); */
/*       digitalWrite(oP8RClose,HIGH); */

/*     }else if(order == OPEN){ */
/*       digitalWrite(oP9LClose,LOW); */
/*       digitalWrite(oP8RClose,LOW); */
/*     } */

/* } */

////////////////////////////////////////////////////////////////////////
// Identify doors state
////////////////////////////////////////////////////////////////////////


/* //Return: STOPPED, DOORSS_CLOSE, DOORSS_UNKNOW */
/* int doorsState(){ */
/*   areDoorsCompletelyOpen(); */
/*   areDoorsCompletelyClose(); */
/*   } */

/* boolean areDoorsCompletelyOpen(){ */

/* } */

/* boolean isL_Open(){ */
/*   digitalRead(A5); */
/* } */

boolean isR_Open(){

  Serial.println("************************");
  Serial.println("inside isR_Open() digitalRead(A0)");
  Serial.println(digitalRead(iTx));
  if(digitalRead(iRx) == LOW){
    Serial.println("Righ door Open");
    Serial.println(OPEN);
    Serial.println("************************");
    return true;
  }
  Serial.println("Righ door is not open");
  Serial.println(CLOSE);
  Serial.println("************************");
  return false;

}

boolean isR_Close(){
  Serial.println("************************");
  Serial.println("inside isR_Close) digitalRead(A0)");
  Serial.println(digitalRead(iTx));
  if(digitalRead(iTx) == LOW){
    Serial.println("Righ door is Close");
    Serial.println(CLOSE);
    Serial.println("************************");
    return true;
  }
  Serial.println("Righ door is not close ");
  Serial.println(OPEN);
  Serial.println("************************");
  return false;

}

int rightDoorState(){
  if(isR_Open()){
    return OPEN;
  }else
    if(isR_Close()){
      return CLOSE;
    }else{
      return MIDDLE;
    }
}

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
////////////////////////////////////////////////////////////////////////////////////////////////////
// Left door states
////////////////////////////////////////////////////////////////////////////////////////////////////

//Do: check if left door is open
//
//Prerrequisites: system on
/* boolean isLDoorOpen(){ */
/*   //maybe missing digitalRead() */

/*   if((digitalRead(A5) == LOW) && (digitalRead(A4) == HIGH)){ */
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
/*   if( (digitalRead(A5) == HIGH) && (digitalRead(A4) == LOW)){ */
/*     Serial.println("Left Door is OPEN"); */
/*     return true; */
/*   }else{ */
/*     Serial.println("Left Door is NOT open"); */
/*     return false; */
/*   } */
/* } */

////////////////////////////////////////////////////////////////////////////////////////////////////
// Right door
////////////////////////////////////////////////////////////////////////////////////////////////////
//Do: check if left door is open
//
//Prerrequisites: system on
/* boolean isLDoorOpen(){ */
/*   //maybe missing digitalRead() */

/*   if((A4 == HIGH) && (A5 == LOW)){ */
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


/* void activateDoors(int order){ */
/*   //deliver messsage to the server, so they could inform the user */
/*   switch (order){ */
/*   case OPEN: */
/*     if(isOpeningDoors()){ */
/*       Serial.println("Doors is being opened. Order: " ); */
/*       Serial.println(order); */
/*     }else{ */
/*       Serial.println("Doors can't be opened ERR_OPEN: " ); */
/*       Serial.println(ERR_OPEN); */
/*     } */
/*     break; */
/*   case CLOSE: */
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
/*   //must return false */
/*   return areMotorsTurning(); */
/* } */


/////////////////////////////////
/* //serial functions */
/* void spPrintValue(int valor){ */
/*   Serial.print("data: "); */
/*   Serial.println(valor); */
/*   delay(1000); */
/* } */

/* void spWriteStateOutput(){ */

/* } */

/* void spWriteStateInput(int pinInput,String pinName){ */
/*   Serial.print(pinName+" : " ); */
/*   if(digitalRead(pinInput)==HIGH){ */
/*     spPrintValue(1); */
/*   }else{ */
/*     spPrintValue(0); */
/*   } */
/* } */
//user order

/* int processUserOrder(int valor){ */
/*   //from ascii number to one to one representation */
/*   valor = valor - 48; */

/*   switch (valor){ */
/*   case */
/*     } */
/*   return valor; */
/* } */

////////////////////////////////////////////////////////////////////////
// Motors
////////////////////////////////////////////////////////////////////////
void testMotorsOnOff(){
  isL_On();
  isR_On();
}

void   testTurning(){
  isL_Turning();
  isR_Turning();
}

////////////////////////////////////////////////////////////////////////
// limir switch
////////////////////////////////////////////////////////////////////////
/* void testLimitSwitch(){ */


/* }  */
