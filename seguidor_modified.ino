/*
    Proyecto para la materia de Desarrollo de proyectos de automatización


    En esta versión se cambiaron varias cosas: Para hacer girar y dejar de girar se dividieron las funciones en dos estados,
    en vez de tenerlas en 4 estados como antes para que solo existan 2 estados y no se combinen
    El beep es intermitente cada medio segundo, no es continuo.
    Se usa el módulo BT para poder leer la información desde el Putty mediante la conexión previa con la compu.
    Sólo falta crear un temporizador, definir cuándo empieza y termina un recorrido y poner a funcionar el módulo de carga.
*/
#include "AFMotor.h"

#define SensorUno A8
#define SensorDos A9
#define trig 22// cable azul
#define echo 24// cable verde
#define buzzer 40


AF_DCMotor MotorUno(1);// derecha adelante
AF_DCMotor MotorDos(2);// izquierda adelante
AF_DCMotor MotorTres(3);// derecha atras
AF_DCMotor MotorCuatro(4);// izquierda atras

int duration, distance,n;
byte LsensorU;
byte LsensorD;




void setup() {
  /* parte 1. sensores infrarrojos*/
  pinMode(SensorUno, INPUT);
  pinMode(SensorDos, INPUT);
  /*para ver el estado del carrito en las pruebas*/
  Serial3.begin(9600);
  Serial.begin(9600);
  /*Parte 2. Sensor ultrasónico*/
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  /*Parte 3. Buzzer*/
  pinMode(buzzer,OUTPUT);
  /*Parte 4. BT*/

}

void loop() {
  
  
  digitalWrite(trig, HIGH);
  delay(100);
  digitalWrite(trig, LOW); 
  duration = pulseIn(echo, HIGH);
  distance = duration / 59  ;
     
  if(distance>=10){
      digitalWrite(buzzer,LOW);
      state1();
    }
  
  if(distance <10){
    state2();
    n++;

  }
  
}



  void state1(){
  LsensorU = digitalRead(SensorUno);//A5 Sensor derecha cable naranja
  LsensorD = digitalRead(SensorDos);//A4 Sensor izquierda cable café
   if (LsensorU == HIGH && LsensorD == HIGH) {
    MotorUno.setSpeed(700);
    MotorDos.setSpeed(700);
    MotorTres.setSpeed(700);
    MotorCuatro.setSpeed(700);
    MotorUno.run(FORWARD); //para que vaya hacia adelante
    MotorDos.run(BACKWARD); // para que vaya hacia adelante
    MotorTres.run(BACKWARD); // hacia delante
    MotorCuatro.run(BACKWARD);// hacia delante
    Serial3.println("avanza"); //esto es para ver el estado
    }
  if (LsensorU == HIGH && LsensorD == LOW) {
    MotorUno.setSpeed(550);
    MotorDos.setSpeed(550);
    MotorTres.setSpeed(550);
    MotorCuatro.setSpeed(550);
    MotorUno.run(BACKWARD); //hacia atrás llanta DAdelante
    MotorDos.run(BACKWARD);//hacia delante llanta IAdelante
    MotorTres.run(BACKWARD); // hacia atrás DTrasera
    MotorCuatro.run(FORWARD);// hacia delante ITrasera
    Serial3.println("Derecha");
    }
  if (LsensorU == LOW && LsensorD == HIGH) {
   // para que se muva a la izquierda necesita detectar que el de la derecha esté en blanco
    Serial3.println("izquierda");
    MotorUno.setSpeed(450);
    MotorDos.setSpeed(450);
    MotorTres.setSpeed(450);
    MotorCuatro.setSpeed(450);
    MotorUno.run(FORWARD); //hacia delante llanta DAdelante
    MotorDos.run(FORWARD);//hacia atrás llanta IAdelante
    MotorTres.run(FORWARD); // hacia delante DTrasera
    MotorCuatro.run(BACKWARD);// hacia atrás ITrasera  
    }
  }

  void state2(){
    for(int c=0; c<1;c++){
      digitalWrite(buzzer,HIGH);
      delay(500);
    }
        //  Cuando se detecte un objeto a 10 cm de distancia con el ultrasónico el carrito deberá de parar, además se debe de emitir una alarma
    MotorUno.run(RELEASE);
    MotorDos.run(RELEASE);
    MotorTres.run(RELEASE);
    MotorCuatro.run(RELEASE);
    for(int c=0; c<1;c++){
      digitalWrite(buzzer,LOW);
      delay(500);
    }
    Serial3.println("Objeto detectado");
    
    
     }

    

    
