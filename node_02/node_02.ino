#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <stdio.h>

//sensor mq135
#define pin_sensor_mq135 A1

//Sensor DHT11
#include "DHT.h" //library sensor yang telah diimportkan 
#define DHTPIN A2     //Pin apa yang digunakan
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
const uint64_t pipe = 0xF0F0F0F0A2LL;

//global variable untuk sensor Mq-7
#define pinSensor A0
long RL = 1000; // 1000 Ohm
long Ro = 830; // 830 ohm ( SILAHKAN DISESUAIKAN)
//
RF24 radio(9,10);

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);            /*Setting baudrate of Serial Port to 9600*/
  dht.begin(); //prosedur memulai pembacaan module sensor

  radio.begin();
  
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(0x76);
  radio.openWritingPipe(pipe);
  radio.enableDynamicPayloads();
  radio.powerUp();

}

void loop() {
  // put your main code here, to run repeatedly:
  //keterangan variable send_data -> nomor_node|ppmCOMq7|CelciusDHT11|HumidityDHT11|ppmMQ135
  char send_data[15] = "2|";
  char SaveValueMq7[10];
  char SaveValueMq135[10];

  char SaveValueTempDHT11[10];
  char SaveValueHumidityDHT11[10];
  int SensorValueMq7 = getSensorMq7();
  int SensorValueTempDHT11 = getTempSensorDHT11();
  int SensorValueHumidityDHT11 = getHumiditySensorDHT11();
  int SensorValueMq135 = getSensorMq135();

  Serial.println(SensorValueMq135);
  Serial.println(SensorValueMq7);
  Serial.println(SensorValueTempDHT11);

 
  //convert int to char
  itoa(SensorValueMq7,SaveValueMq7,10);
  itoa(SensorValueMq135,SaveValueMq135,10);
  itoa(SensorValueTempDHT11,SaveValueTempDHT11,10);
  itoa(SensorValueHumidityDHT11,SaveValueHumidityDHT11,10);


  Serial.println(SaveValueMq7);
  Serial.print("Start Send data from node 2 : \n");
  //concat char sensor mq7
  strcat(send_data,SaveValueMq7);
  strcat(send_data,"|");
  strcat(send_data,SaveValueTempDHT11);
  strcat(send_data,"|");
  strcat(send_data,SaveValueHumidityDHT11);
  strcat(send_data,"|");
  strcat(send_data,SaveValueMq135);



  Serial.println(send_data);
  radio.write(&send_data, sizeof(send_data));
 

  delay(5000);
}

int getSensorMq7(){
  int sensorvalue = analogRead(pinSensor); // membaca nilai ADC dari sensor
  float VRL= sensorvalue*5.00/1024;  // mengubah nilai ADC ( 0 - 1023 ) menjadi nilai voltase ( 0 - 5.00 volt )
//  Serial.print("VRL : ");
//  Serial.print(VRL);
//  Serial.println(" volt");
  
  float Rs = ( 5.00 * RL / VRL ) - RL;
//  Serial.print("Rs : ");
//  Serial.print(Rs);
//  Serial.println(" Ohm");
  
  float ppm = 100 * pow(Rs / Ro,-1.53); // ppm = 100 * ((rs/ro)^-1.53);
  Serial.print("CO : ");
  Serial.print(ppm);
  Serial.println(" ppm");
  return ppm;
//  Serial.println();
}

int getTempSensorDHT11(){
 // put your main code here, to run repeatedly:
  
  //Pembacaan dalam format celcius (c)
  float celcius_1 = dht.readTemperature();
  //convert float to int agar bisa di assign array of char
  int t_celcius = celcius_1;
  //mengecek pembacaan apakah terjadi kegagalan atau tidak
  if (isnan(celcius_1)) {
    Serial.println("Pembacaan data dari module sensor gagal!");
  } 
  
  //pembacaan nilai pembacaan data suhu
  Serial.print("Suhu : ");
  Serial.print(celcius_1); //format derajat celcius
  Serial.print(" 'C ");
  return(t_celcius);
 }

int getHumiditySensorDHT11(){

  float humidity_1 = dht.readHumidity();
  int t_humidity = humidity_1;
  if (isnan(t_humidity)) {
    Serial.println("Pembacaan data dari module sensor gagal!");
  }
  
  return t_humidity;
 }

int getSensorMq135(){
  int sensorValue;
  
  sensorValue = analogRead(pin_sensor_mq135);       // read analog input pin 0
  Serial.print("Data Sensor Mq135=");
  Serial.print(sensorValue);               // prints the value read
  Serial.println(" PPM");

  return(sensorValue);

  }
