#include "DHTStable.h"    //biblioteca o dht11
#include <OneWire.h>       //biblioteca do sensor de temperatura do solo
#include <DallasTemperature.h>  ////biblioteca do sensor de temperatura do solo

#define temphum A8     //sensor dht11 na porta A8
#define temterra 2     //sensor dtemp do solo na porta 2
#define humsolo A10    //sensor humidade do solo na porta A10
#define sol A9        //sensor luminosidade na porta A9


DHTStable DHT;
OneWire oneWire(temterra);  
DallasTemperature sensors(&oneWire);


void setup(){
  Serial.begin(9600);
  sensors.begin();         //inicia o sensor de temperatura do solo
  pinMode(temphum, INPUT);
  pinMode(temterra, INPUT);
  pinMode(humsolo, INPUT);
  pinMode(sol, INPUT);
}

void loop(){
  String T ="T", H ="H",t1 = "t1",t2 = "t2"; //declarar strings para concatenar com a leitura
  DHT.read11(temphum);                    //inicia o sensor de temperatura e humidade
  float humidAr = DHT.getHumidity();      // recebe a humidade
  float tempAr =  DHT.getTemperature();  //recebe a temperatura
  H.concat(humidAr);                    // adiciona a temperatura a string H
  Serial.println(H);            // envia para a serial em formato de String
  T.concat(tempAr);                     //adiciona a temperatura a string T
  Serial.println(T);            // envia para a serial em formato de String


  sensors.requestTemperatures();        //ativa o sensor de temperatura do solo
  float temp1 = sensors.getTempCByIndex(0);   //obtem a temperatura do solo1
  float temp2 = sensors.getTempCByIndex(1);   //obtem a temperatura do solo2
  delay(200);
  t1.concat(temp1);
  Serial.println(t1);                   //envia pra serial a temperatura1
  t2.concat(temp2);
  Serial.println(t2);                  //envia pra serial a temperatura2

  delay(3000);
}
