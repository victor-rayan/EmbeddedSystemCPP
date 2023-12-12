#include "DHT.h"
#include "mqtt.h"
#include "memoryFlash.h"
#include "bomba.h"
#include "sensor.h"

#define DHTPIN 4
#define DHTTYPE DHT22

int temp_umi = 4;
int alerta = 2;
int nivel = 26;
bool reservatorio = LOW;
float umidadear;
float temperatura;
int solo1 = 35;
int solo2 = 34;
float umidade_solo1;
float umidade_solo2;

int solo_min1 = 300;
int solo_max1 = 5100;
int solo_min2 = 300;
int solo_max2 = 5100;

int i = 0, x = 0, f = 0;

//variaveis anememotro
const int anemometro = 19; // pino digital do anemômetro
const int potenciometro = 15; // pino digital do potenciômetro
// variáveis
unsigned int pulsos = 0; // variável para contar os pulsos
float direcao = 0;
unsigned long tempo; // variável para registrar um tempo
bool atual_estado = LOW;
bool ultimo_estado = LOW; // variável para armazenar o estado do pino de interrupção
unsigned int ultimo_debounce = 0;
unsigned int tempo_debounce = 80;
float pulsos_por_segundo = 0;
float velocidade_do_vento = 0;
const float multiplicador = 0.7989;
const float defasagem = 0.28;


DHT dht(DHTPIN, DHTTYPE);


void setupSensor() {
  pinMode(nivel, INPUT);
  pinMode(alerta,OUTPUT);
  digitalWrite(alerta, LOW);
  pinMode(temp_umi, INPUT);
  pinMode(solo1, INPUT);
  pinMode(solo2, INPUT);
  dht.begin();

  //setup anenometro
  pinMode(anemometro, INPUT);
  pinMode(potenciometro, INPUT);
  attachInterrupt(digitalPinToInterrupt(anemometro), contaPulsos, RISING);
}

bool reservatorioVazio() {
  reservatorio = digitalRead(nivel);
  if (reservatorio == HIGH) {
    
    Serial.print("Nível do reservatório: vazio");
    Serial.print('\n');
    return false;
  }else{
    
    Serial.print("Nível do reservatório: cheio");
    Serial.print('\n');
    return true;
  }
}

void verifySensor() {
  
  bool validade_reservatorio = reservatorioVazio();
  Serial.print("Estado da reservatorio na leitura: ");
  Serial.println(validade_reservatorio);
  if (validade_reservatorio == false) {
    Serial.print("Nível do reservatório deu vazio fechando bomba");
   closeBomba();
  }

  umidadear = dht.readHumidity(); //Lê o nível de umidade do ar
  temperatura = dht.readTemperature(); //Lê a temperatura
  Serial.print("Umidade do ar (percentual: ");
  Serial.print(umidadear);
  Serial.print('\n');
  Serial.print("Temperatura (graus Célsius: ");
  Serial.print(temperatura);
  Serial.print('\n');
  

  umidade_solo1 = analogRead(solo1); //lê a umidade do solo do primeiro sensor
  
  umidade_solo1 = map(umidade_solo1, solo_min1, solo_max1, 100, 0); //converte a leitura do solo em porcentagem
  Serial.print("Umidade do Solo 1 (percentual): ");
  Serial.print(umidade_solo1);
  Serial.print('\n');

  umidade_solo2 = analogRead(solo2); //lê a umidade do solo do segundo sensor
  
  umidade_solo2 = map(umidade_solo2, solo_min2, solo_max2, 100, 0); //converte a leitura do solo em porcentagem
  Serial.print("Umidade do Solo 2 (percentual): ");
  Serial.print(umidade_solo2);
  Serial.print('\n');

  pulsos_por_segundo = (((float)pulsos/2)/((millis() - tempo)/5000.0)); // calcula pulsos por segundo e transforma para float
  velocidade_do_vento = (multiplicador * pulsos_por_segundo) + defasagem;
  float windSpeed = velocidade_do_vento * 3.6;

  Serial.print("velocidade do vento ");
  Serial.print(windSpeed);
  Serial.print('\n');
  
  bool status = loadBombaStatus();
  Serial.print("medias Umidade do Solo (percentual): ");
  float media_umidade = ((umidade_solo1 + umidade_solo2) / 2);
  Serial.print(media_umidade);
  Serial.print('\n');

  sendMessageInfo(windSpeed, umidadear, media_umidade, temperatura, status, validade_reservatorio);


}

void contaPulsos() {

  if ((millis() - ultimo_debounce) > tempo_debounce) {
    atual_estado = digitalRead(anemometro); // Lê o estado do pino 19
    //if (atual_estado == HIGH && ultimo_estado == LOW) {  // detecta borda de subida
      ultimo_debounce = millis();
      pulsos++;
    //}
  }
}
