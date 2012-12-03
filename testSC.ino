///////////////////////////////////////////////////////////////////////////////////////////
// Open loop version  (No Imputs)
///////////////////////////////////////////////////////////////////////////////////////////

/** Just testing seria port communication and pins in the Leonardo board
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

///////////////////////////////////////
//ORDERS 
///////////////////////////////////////

//change motor state
const int OFF          = 0;
const int ON           = 1;

//change doors state
const int OPEN      = 2;
const int CLOSE     = 3;
const int STOP      = 4;
 
///////////////////////////////////////
//FEEDBACK
///////////////////////////////////////

//is not moving 
const int MIDDLE             = 5;

//switch door state
const int MOVING             = 6;

//SYSTEM ERRORS
//change error format err_1
const int ERR_OPEN           = 7;
const int ERR_CLOSE          = 8;
const int ERR_STOP           = 9;

const int ERR_ON             = 8;
const int ERR_OFF            = 9;
const int ERR_NOT_VALID      = 53;

const int NOT_MOVING        = 0xE2;
const int NOT_MOVING_LEFT   = 0xE2;
const int NOT_MOVING_RIGHT  = 0xE3;

const int MOTORS_MOVING     = 2;
const int MOTORS_NOT_MOVING = 2;

//////////////////////////////////////////////////////////////
// constants outputs




//ON Encendido Motores
//quitar corriente en los motores
int oP7MoLOn = 2;   //p1 == L  
int oP6MoROn = 3;   //p2 == R

//Stop cortar la corriente 
int oP11LStop = 4;
int oP10RStop = 5;

//Rotaciones Motores
int oP13LOpen = 6;//13;
int oP12ROpen = 9;//12;

//Close
int oP9LClose = 10; //11
int oP8RClose = 11; //10

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
  pinMode(iTx,INPUT);  //R_M_On    iTx
  pinMode(iRx,INPUT);  //L_M_On    

  //info de los pilotos
  //pilotos de giro
  pinMode(A2,INPUT);   //turnL
  pinMode(A3,INPUT);   //turnR
 
  //Right limit switch
  pinMode(A0,INPUT);  //RClose
  pinMode(A1,INPUT);  //ROpen

  //Left limit switch
  pinMode(A4,INPUT);   //LClose
  pinMode(A5,INPUT);   //LOpen

  Serial.begin(9600);        // connect to the serial port
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop () {
  Serial.println("Set order: " );
  order  = Serial.read();      // read the serial port
  order  = order  - 48;
  Serial.println();
  //////////////////////////////
  //test outputs
  //  openLoopControl(order);
  
  //////////////////////////////
  //feeback
  //////////////////////////////
  closeLoopControl(order);

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
    doorsCL(OPEN);
    delay(1000);
    break;

  case CLOSE://3
    doorsCL(CLOSE);
    delay(1000);
    break;

  case STOP://4
    doorsCL(STOP);//
    delay(1000);
    break;

  default:
    ;
   }
  delay(1000);

}

////////////////////////////////////////////////////////
// MOTOR Functions 
////////////////////////////////////////////////////////

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
  return false;
}


//DONE
boolean isR_Turning(){
  if((digitalRead(A3) == HIGH)){
    Serial.println("IS MOVING");
    Serial.println(MOVING);
    return true;
  }
  Serial.println("NOT_MOVING");
  Serial.println(NOT_MOVING);
  return false;
}

////////////////////////////////////////////////////////
// DOORS
////////////////////////////////////////////////////////
//openLoop

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
  }
}

void doorsCL(int order){
  switch(order){
  case OPEN:
    leftDoor(OPEN);
    delay(1000);
    rightDoor(OPEN);
    break;
  case CLOSE:
    leftDoor(CLOSE);
    delay(1000);
    rightDoor(CLOSE);
    break;
  case STOP:
    leftDoor(STOP);
    delay(1000);
    rightDoor(STOP);
    break;
  }
}

////////////////////////////////////////////////////////////////////////
// RIGHT door state
////////////////////////////////////////////////////////////////////////
int rightDoor(int order){
  switch(order){

  case OPEN:
    Serial.println("Opening right door");

    //detengo
    digitalWrite(oP10RStop,HIGH);

    //desactivo otras acciones
    digitalWrite(oP10RStop,LOW);
    digitalWrite(oP8RClose,LOW);

    //activo la orden
    digitalWrite(oP12ROpen,HIGH);

    //message for the server
    Serial.println("");
    break;

  case CLOSE:
    Serial.println("closimg right door");

    //detengo
    digitalWrite(oP10RStop,HIGH);

    //desactivo otras acciones
    digitalWrite(oP10RStop,LOW);
    digitalWrite(oP12ROpen,LOW);

    //activo la orden
    digitalWrite(oP8RClose,HIGH);

    //message for the server
    Serial.println("");
    break;

  case STOP:
    Serial.println("Stoping left door");
    //detengo
    digitalWrite(oP10RStop,HIGH);
    //desactivo otras acciones
    digitalWrite(oP10RStop,LOW);
    digitalWrite(oP12ROpen,LOW);
    //activo la orden
    digitalWrite(oP8RClose,LOW);

    //message for the server
    Serial.println("");
    break;
  default:
    Serial.println("Never should be here, DEFAULT rightDoor()");
  } 
}

boolean isR_Open(){
  Serial.println("************************");
  Serial.println("inside isR_Open() digitalRead(A0)");
  Serial.println(digitalRead(A1));
  if(digitalRead(A1) == LOW){
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
  Serial.println(digitalRead(A0));
  if(digitalRead(A0) == LOW){
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

////////////////////////////////////////////////////////////////////////////////////////////////////
// LEFT door state
////////////////////////////////////////////////////////////////////////////////////////////////////
int leftDoor(int order){
  switch(order){

  case OPEN:
    Serial.println("Opening left door");

    //detengo
    digitalWrite(oP11LStop,HIGH);

    //desactivo otras acciones
    digitalWrite(oP11LStop,LOW);
    digitalWrite(oP9LClose,LOW);

    //activo la orden
    digitalWrite(oP13LOpen,HIGH);

    //message for the server
    Serial.println("");
    break;

  case CLOSE:
    Serial.println("closimg left door");

    //detengo
    digitalWrite(oP11LStop,HIGH);

    //desactivo otras acciones
    digitalWrite(oP11LStop,LOW);
    digitalWrite(oP13LOpen,LOW);

    //activo la orden
    digitalWrite(oP9LClose,HIGH);

    //message for the server
    Serial.println("");
    break;

  case STOP:
    Serial.println("Stoping left door");
    //detengo
    digitalWrite(oP11LStop,HIGH);
    //desactivo otras acciones
    digitalWrite(oP11LStop,LOW);
    digitalWrite(oP13LOpen,LOW);
    //activo la orden
    digitalWrite(oP9LClose,LOW);

    //message for the server
    Serial.println("");
    break;
  default:
    Serial.println("Never should be here, DEFAULT leftDoor()");
  } 
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
boolean isL_Turning(){
  if((digitalRead(A2) == HIGH)){
    Serial.println("LEFT Door turning");
    Serial.println(MOVING);
    return true;
  }
  Serial.println("LEFT Door is not turning");
  Serial.println(NOT_MOVING);
  return false;
}

boolean isL_Open() {
  Serial.println("************************");
  Serial.println("inside isR_Open() digitalRead(A0)");
  Serial.println(digitalRead(A5));
  if(digitalRead(A5) == LOW){
    Serial.println("LEFT door Open");
    Serial.println(OPEN);
    Serial.println("************************");
    return true;
  }
  Serial.println("LEFT door is not open");
  Serial.println(CLOSE);
  Serial.println("************************");
  return false;
}

boolean isL_Close(){
  Serial.println("************************");
  Serial.println("inside isR_Close) digitalRead(A0)");
  Serial.println(digitalRead(A0));
  if(digitalRead(A0) == LOW){
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

int leftDoorState(){
  if(isL_Open()){
    return OPEN;
  }else
    if(isL_Close()) {
      return CLOSE;
    }else 
      if(isL_Turning()){
	return MOVING;
      }else{
      return MIDDLE;
    }
}


/*    digitalWrite(oP8RClose,LOW); */
/*     digitalWrite(oP10RStop,LOW); */
/*     digitalWrite(oP12ROpen,HIGH); */


////////////////////////////////////////////////////////////////////////////////////////////////////
// RIGHT door state
////////////////////////////////////////////////////////////////////////////////////////////////////

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

