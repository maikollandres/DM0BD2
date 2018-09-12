#include <OBD2UART.h>
#include <LiquidCrystal.h>

#define Tiempo 210 //Ir aumentando a medida que se aumenten las instrucciones de la interrupción--Hacer pruebas con c=0 para que de 20 khz

COBD obd;
int value; //Valor leido

//Contadores Timer
int a=0; //Para la velocidad
int b=0; //Para las RPM
int c=0; //Para el consumo

double vel=20;
int param_vel=0;
double rpm=20;
int param_rpm=0;
double consumo=0;
int param_consumo=0;

void setup()
{

//Configuración de salidas
   DDRB = B11110000;

//Interrupción por timer2
   SREG = (SREG & 0b01111111); //Desabilitar interrupciones
   TIMSK2 = TIMSK2|0b00000001; //Habilita la interrupcion por desbordamiento
   TCCR2B = 1; //Configura preescala para que FT2 sea de 7812.5Hz
   SREG = (SREG & 0b01111111) | 0b10000000; //Habilitar interrupciones //Desabilitar interrupciones 
   TCNT2=Tiempo;
  
  // start communication with OBD-II adapter
  obd.begin();
  // initiate OBD-II connection until success
  while (!obd.init());
}

void loop(){  
  // save engine RPM in variable 'value', return true on success
  if (obd.readPID(PID_SPEED, value)){
    vel=value;
  }
  if (obd.readPID(PID_RPM, value)){
    rpm=value;
  }
  if (obd.readPID(PID_MAF_FLOW, value)){
    consumo=value;
  }
  
  //Convirtiendo las señales en señales de frecuencia 
  param_vel=(int)20359.96/(10*vel/36)-0.01523;
  param_rpm=(int)20359.96/(rpm/20)-0.01523;
  param_consumo=(int)0;
}

//Interrupción Timer2
ISR(TIMER2_OVF_vect){ 
      a++;     
      b++;
      c++; 
      if(a>=param_vel) //Contador velocidad
      {        
        a=0;        
        PORTB = PORTB^B00100000;        
      }   
      if(b>=param_rpm) //Contador RPM
      {
        b=0;        
        PORTB = PORTB^B01000000;        
      } 
      if(c>=param_consumo) //Contador consumo
      {
        c=0;        
        PORTB = PORTB^B10000000;        
      }    
      TCNT2=Tiempo;
}
