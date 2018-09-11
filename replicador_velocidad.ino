
volatile unsigned int cuenta = 0;

bool ESTADO = false;
//#define Tiempo 216 //Para la base de tiempo (20 kHz)
#define Tiempo 210 //Ir aumentando a medida que se aumenten las instrucciones de la interrupción--Hacer pruebas con c=0 para que de 20 khz

int a=0; //Para la velocidad
int b=0; //Para las RPM
int c=0; //Para el consumo

int i=0;
double vel=0;
int param_vel=0;
double RPM=20;
int param_rpm=0;
double litros=50;
int param_litros=0;

void setup(){ 

   DDRB = B11110000;
   Serial.begin(9600);  
   
   SREG = (SREG & 0b01111111); //Desabilitar interrupciones
   TIMSK2 = TIMSK2|0b00000001; //Habilita la interrupcion por desbordamiento
   TCCR2B = 1; //Configura preescala para que FT2 sea de 7812.5Hz
   SREG = (SREG & 0b01111111) | 0b10000000; //Habilitar interrupciones //Desabilitar interrupciones 
   TCNT2=Tiempo;
}

void loop(){  
  param_vel=(int)20359.96/(10*vel/36)-0.01523;
  param_rpm=(int)0;
}

//Interrupción
ISR(TIMER2_OVF_vect){ 
      a++;     
      b++;
      c++; 
      if(a>=param_vel) //Contador velocidad
      {        
        a=0;        
        PORTB = PORTB^B0010000;        
      }   
      if(b>=1) //Contador RPM
      {
        b=0;        
        PORTB = PORTB^B0100000;        
      } 
      if(c>=1) //Contador consumo
      {
        c=0;        
        PORTB = PORTB^B1000000;        
      }    
      TCNT2=Tiempo;
}
