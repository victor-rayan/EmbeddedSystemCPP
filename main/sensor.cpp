#include "DHT.h"
#include "mqtt.h"
#include "memoryFlash.h"
#include "bomba.h"

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

int solo_min1 = 1024;
int solo_max1 = 3000;
int solo_min2 = 300;
int solo_max2 = 5100;

int i = 0, x = 0, f = 0;

DHT dht(DHTPIN, DHTTYPE);


void setupSensor() {
  pinMode(nivel, INPUT);
  pinMode(alerta,OUTPUT);
  digitalWrite(alerta, LOW);
  pinMode(temp_umi, INPUT);
  pinMode(solo1, INPUT);
  pinMode(solo2, INPUT);
  
  dht.begin();
}

bool reservatorioVazio() {
  reservatorio = digitalRead(nivel);
  if (reservatorio == HIGH) {
    
    Serial.print("Nível do reservatório: vazio");
    Serial.print('\n');
    return true;
  }else{
    
    Serial.print("Nível do reservatório: cheio");
    Serial.print('\n');
    return false;
  }
}

void verifySensor() {
  
  reservatorio = reservatorioVazio();
  Serial.print("Estado da bomba: ");
  Serial.println(reservatorio);
  if (reservatorio == true) {
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
  float windSpeed = 5.0;
  bool status = loadBombaStatus();

  sendMessageInfo(windSpeed, umidadear, umidade_solo1, temperatura, status, reservatorio);


}
