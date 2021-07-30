#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "******"
#define STAPSK  "******"
#endif

const char* ssid = STASSID;                                                           //Nework Name
const char* password = STAPSK;                                                        //Network Password
const long utcOffsetInSeconds = 0;                                                    //UTCOFFSET UTC+0 = 0*60*60

char dias [7][12] ={"Domingo","Segunda","Terça","Quarta","Quinta","Sexta","Sabado"};  //Days of the Week
int tempo = 3;                                                                        //Time of work
int horas[3]= {12,54,0};                                                              //Hour that triggers the regar function

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org",utcOffsetInSeconds);

void setup(){
  //Pin Configuration
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, HIGH);
  //Wifi Connection
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  //NTPServer Connection
  timeClient.begin();
}

void loop(){
  timeClient.update();
  Serial.print(dias[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours()+1);                                               // "+1" SummerTime
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  if(timeClient.getHours()+1 == horas[0] && timeClient.getMinutes() == horas[1] && \
  timeClient.getSeconds() == horas[2]){
    regar(1);   //ALTERAR PARA TEMPO
  }
  delay(1000);
}

void regar(int minutos){
  digitalWrite(LED_BUILTIN, LOW);
  //ligar chuveiros  
  for(int i = 0; i< minutos; i++){
    Serial.println("A REGAR");
    delay(60000);
  }
  //desligar chuveiros

  digitalWrite(LED_BUILTIN, HIGH);
}
