/********
 * BIBLIOTECAS          *
 ********/
#include <Servo.h>
#include <NewPing.h>

/********
 * DEFINIÇÕES           *
 ********/
#define trig_pin A4
#define echo_pin A5

#define TESTE 1                   //UTILIZADO PARA QUANDO EM TESTE COLOCAR NUMERO 1

#define on HIGH                   //LIGADO
#define off LOW                   //DESLIGADO
#define max_distance 500          //CENTIMETROS
//#define min_distance 10           //CENTIMETROS

/********
 * CONSTANTES           *
 ********/
const int RodaDirFrente = 6;
const int RodaDirRe = 7;
const int RodaEsqFrente = 2;
const int RodaEsqRe = 3;

const int Pescoco = 5;

//Leds 
int ledGVerm = 10;
int ledGAmar = 11;
int ledGVerd = 12;
int ledPVerd = 9;
int ledPVerm = 8;

// Movimentos
const int VisaoEsquerda = 180;
const int VisaoDigEsquerda = 135;
const int VisaoFrente = 90;
const int VisaoDigDireita = 45;
const int VisaoDireita = 0;


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

void ConfigurandoPortas() {
    servo_motor.attach(Pescoco);
    pinMode(RodaDirFrente,OUTPUT);
    pinMode(RodaDirRe,OUTPUT);
    pinMode(RodaEsqFrente,OUTPUT);
    pinMode(RodaEsqRe,OUTPUT);
    pinMode(ledGAmar,OUTPUT);
    pinMode(ledGVerd,OUTPUT);
    pinMode(ledGVerm,OUTPUT);
    pinMode(ledPVerd,OUTPUT);
    pinMode(ledPVerm,OUTPUT);
}

void TestesDePing() {
    Serial.println("Testes de ping");
    servo_motor.write(VisaoFrente);

    while (true)
    {
        int distancia = readPing();
        Serial.print("Distancia : ");
        Serial.print(distancia);
        Serial.print(" cm");
        Serial.println();
    }

}

void TestesDeVisaoAngulo() {
    Serial.println("Testes de angulo");

    for (int i = 0; i < 180; i+=10){
        delay(2000);
        Serial.print("Angulo ");
        Serial.print(i);
        Serial.println();

        servo_motor.write(i);
    }

    Serial.println("Fim dos testes de angulo");
}

void TestesDeVisao() {
    Serial.println("Testes de Pescoço");
    //Testando para Pescoço, olhando frente, direita e esquerda
    //servo_motor.write(VisaoFrente);   delay(2000);

    Serial.println("Olhando pra Esquerda");
    servo_motor.write(VisaoEsquerda); delay(2000);

    Serial.println("Olhando pra Frente");
    servo_motor.write(VisaoFrente);   delay(2000);
    
    Serial.println("Olhando pra Direita");
    servo_motor.write(VisaoDireita);  delay(2000);

    Serial.println("Fim dos testes de Pescoço");
}

void TestesDeMotor() {
    Serial.println("Testes de Motor");
    delay(1000);

    Serial.println("Testando para Frente");
    //Testando para Frente
    digitalWrite(RodaDirFrente, on ); 
    digitalWrite(RodaEsqFrente, on ); delay(500);
    digitalWrite(RodaDirFrente, off ); 
    digitalWrite(RodaEsqFrente, off );

    Serial.println("Testando para Traz");
    //Testando para Traz
    digitalWrite(RodaDirRe, on ); 
    digitalWrite(RodaEsqRe, on ); delay(500);
    digitalWrite(RodaDirRe, off ); 
    digitalWrite(RodaEsqRe, off );

    Serial.println("Testando para Direita");
    //Testando para Direita
    digitalWrite(RodaDirRe, on ); 
    digitalWrite(RodaEsqFrente, on ); delay(500);
    digitalWrite(RodaDirRe, off ); 
    digitalWrite(RodaEsqFrente, off );

    Serial.println("Testando para Esquerda");
    //Testando para Esquerda
    digitalWrite(RodaDirFrente, on ); 
    digitalWrite(RodaEsqRe, on ); delay(500);
    digitalWrite(RodaDirFrente, off ); 
    digitalWrite(RodaEsqRe, off );
    
    Serial.println("Fim dos testes de motor");
}

// Movimentos
void rodaEsquerda(bool onOrOff) {
    digitalWrite(RodaDirRe,     onOrOff ? on : off ); 
    digitalWrite(RodaEsqFrente, onOrOff ? on : off ); 

    digitalWrite(ledGVerm, onOrOff ? on : off );
}

void rodaFrente(bool onOrOff) {
    digitalWrite(RodaDirFrente, onOrOff ? on : off );
    digitalWrite(RodaEsqFrente, onOrOff ? on : off );

    digitalWrite(ledGAmar, onOrOff ? on : off );
}

void rodaDireita(bool onOrOff) {
    digitalWrite(RodaDirFrente, onOrOff ? on : off );
    digitalWrite(RodaEsqRe,     onOrOff ? on : off );

    digitalWrite(ledGVerd, onOrOff ? on : off );
}

void rodaRe(bool onOrOff) {
    digitalWrite(RodaDirRe,     onOrOff ? on : off );
    digitalWrite(RodaEsqRe,     onOrOff ? on : off );
}

void movInicial() {
    int timeVision = 400;
    servo_motor.write(VisaoEsquerda);
    delay(timeVision);
    servo_motor.write(VisaoDireita);
    delay(timeVision);

    servo_motor.write(VisaoEsquerda);
    delay(timeVision);
    servo_motor.write(VisaoDireita);
    delay(timeVision);

    servo_motor.write(VisaoFrente);
    delay(1000);
}

/********
 * CONFIGURAÇÃO ROBO    *
 ********/
void setup(){
    Serial.begin(9600); //Configuração para printar no Monitor serial

    ConfigurandoPortas();
    movInicial();
    //TestesDeMotor();
    //TestesDeVisao();
    //TestesDeVisaoAngulo();
    //TestesDePing();
}

/********
 * VIDA ROBO            *
 ********/
void loop(){
    long dist = readPing();
    int dist_min = 10; //cm
    if (dist < dist_min) {
        rodaRe(true);
        delay(500);
        rodaRe(false);
    }


    long dists[5] = {0, 0, 0, 0, 0};
    int cont_visao = 0;
    for (int i = 0; i <= 180; i+=45){
        delay(300);
        servo_motor.write(i);
        dists[cont_visao] = readPing();
        cont_visao++;
    }

    int maior_distancia = 0;
    for (int i = 0; i < 5; i++) {
        maior_distancia = dists[i] > dists[maior_distancia] ? i : maior_distancia;
    }

    servo_motor.write(VisaoFrente);
    int delay_check_vision = 10;
    int delay_lateral = 400;
    if (maior_distancia == 0 || maior_distancia == 1) {
        //Esquerda
        rodaEsquerda(true);

        delay(delay_lateral);
        /*bool correto = false;
        while (!correto) {
            delay(delay_check_vision);
            correto = readPing() <= dist_min;
        }*/

        rodaEsquerda(false);
    } else if (maior_distancia == 2) {
        //Frente
        rodaFrente(true);

        bool correto = false;
        while (!correto) {
            delay(delay_check_vision);
            correto = readPing() <= dist_min;
        }

        rodaFrente(false);
    } else if (maior_distancia == 3 || maior_distancia == 4 ) {
        //Direita
        rodaDireita(true);

        delay(delay_lateral);
        /*bool correto = false;
        while (!correto) {
            delay(delay_check_vision);
            correto = readPing() <= dist_min;
        }*/

        rodaDireita(false);
    }
    
}
