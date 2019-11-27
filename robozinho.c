/********
 * BIBLIOTECAS          *
 ********/
#include <Servo.h>
#include <NewPing.h>

/********
 * DEFINIÇÕES           *
 ********/
#define trig_pin A1
#define echo_pin A2

#define TESTE 1                   //UTILIZADO PARA QUANDO EM TESTE COLOCAR NUMERO 1

#define on HIGH                   //LIGADO
#define off LOW                   //DESLIGADO
#define max_distance 500          //CENTIMETROS
#define min_distance 10           //CENTIMETROS

/********
 * CONSTANTES           *
 ********/
const int RodaDirFrente = 3;
const int RodaDirRe = 2;
const int RodaEsqFrente = 4;
const int RodaEsqRe = 5;

const int Pescoco = 11;

const int VisaoEsquerda = 150;
const int VisaoFrente = 90;
const int VisaoDireita = 30;

/********
 * VARIAVEIS GLOBAIS    *
 ********/
NewPing sonar(trig_pin, echo_pin, max_distance);
Servo servo_motor;

long distance = 0;

int lado = 1;
int velocidadeDeOlhar = 300;

long distanciaFrente = 0;
long distanciaEsquerda = 0;
long distanciaDireita = 0;


/********
 * METODOS E FUNÇÕES    *
 ********/

int readPing() {  
  delay(100);
  int cm = sonar.ping_cm();
  delay(100);
  return cm;  
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void ConfigurandoPortas()
{
  servo_motor.attach(Pescoco);
  pinMode(RodaDirFrente,OUTPUT);
  pinMode(RodaDirRe,OUTPUT);
  pinMode(RodaEsqFrente,OUTPUT);
  pinMode(RodaEsqRe,OUTPUT);
}

void TestesIniciais()
{
    //Testando para Frente
    digitalWrite(RodaDirFrente, on ); 
    digitalWrite(RodaEsqFrente, on ); delay(500);
    digitalWrite(RodaDirFrente, off ); 
    digitalWrite(RodaEsqFrente, off ); 
    //Testando para Traz
    digitalWrite(RodaDirRe, on ); 
    digitalWrite(RodaEsqRe, on ); delay(500);
    digitalWrite(RodaDirRe, off ); 
    digitalWrite(RodaEsqRe, off );
    //Testando para Direita
    digitalWrite(RodaDirRe, on ); 
    digitalWrite(RodaEsqFrente, on ); delay(500);
    digitalWrite(RodaDirRe, off ); 
    digitalWrite(RodaEsqFrente, off );
    //Testando para Esquerda
    digitalWrite(RodaDirFrente, on ); 
    digitalWrite(RodaEsqRe, on ); delay(500);
    digitalWrite(RodaDirFrente, off ); 
    digitalWrite(RodaEsqRe, off );
    //Testando para Pescoço, olhando frente, direita e esquerda
    servo_motor.write(VisaoFrente);   delay(2000);    
    servo_motor.write(VisaoEsquerda); delay(2000);
    servo_motor.write(VisaoDireita);  delay(2000);
    servo_motor.write(VisaoFrente);   delay(2000);       
}

/********
 * CONFIGURAÇÃO ROBO    *
 ********/

void setup(){
    Serial.begin(9600); //Configuração para printar no Monitor serial

    ConfigurandoPortas();
    //TestesIniciais();  
}

/********
 * VIDA ROBO            *
 ********/

void loop(){
    //Obtendo Distancia Inicial

    if (lado == 1) {
        servo_motor.write(VisaoFrente); 
        distance = readPing();
        distanciaFrente = distance;
        //Serial.println("Frente");    
    } else if(lado == 2){
        servo_motor.write(VisaoDireita); 
        distance = readPing();
        distanciaDireita = distance;
        //Serial.println("DIREITA");    
    } else if(lado == 3) {
        servo_motor.write(VisaoEsquerda); 
        distance = readPing();
        distanciaEsquerda = distance;
        //Serial.println("ESQUERDA");    
    }
    delay(velocidadeDeOlhar);


    int dirASeguir = 0;
    if (distanciaFrente < distanciaDireita && distanciaFrente < distanciaEsquerda){
        dirASeguir = 1;
    } else if (distanciaDireita < distanciaEsquerda && distanciaDireita < distanciaFrente) {
        dirASeguir = 2;
    } else if (distanciaEsquerda < distanciaDireita && distanciaEsquerda < distanciaFrente) {
        dirASeguir = 3;
    } else {
        dirASeguir = 4;
    }

    if (distanciaFrente < 5) {
        dirASeguir = 4;
    }

    Serial.print("Escolha: ");
    Serial.print(dirASeguir);
    Serial.println();

    
    if (dirASeguir == 1) 
    {
      Serial.println(" Frente ");
      digitalWrite(RodaDirFrente, on ); 
      digitalWrite(RodaEsqFrente, on );
      delay(distanciaFrente * 10);
      digitalWrite(RodaDirFrente, off ); 
      digitalWrite(RodaEsqFrente, off );
    }

    if (dirASeguir == 2) 
    {
      Serial.println(" Direita ");
      digitalWrite(RodaDirFrente, on ); 
      digitalWrite(RodaEsqRe, on ); 
      delay(500);
      digitalWrite(RodaDirFrente, off ); 
      digitalWrite(RodaEsqRe, off );
    }

    if (dirASeguir == 3) 
    {
      Serial.println(" Esquerda ");
      digitalWrite(RodaDirRe, on ); 
      digitalWrite(RodaEsqFrente, on ); 
      delay(500);
      digitalWrite(RodaDirRe, off ); 
      digitalWrite(RodaEsqFrente, off );
    }

    if (dirASeguir == 4) 
    {
      Serial.println(" Re ");
      digitalWrite(RodaDirRe, on ); 
      digitalWrite(RodaEsqRe, on ); 
      delay(distanciaFrente * 10);
      digitalWrite(RodaDirRe, off ); 
      digitalWrite(RodaEsqRe, off );
    }
    
    if (lado < 3) {
        lado++;
    } else {
        lado = 1;
    }
}