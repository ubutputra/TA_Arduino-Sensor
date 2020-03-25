#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <stdio.h>



//global variable untuk sensor Mq-7
#define pinSensor A0
long RL = 1000; // 1000 Ohm
long Ro = 830; // 830 ohm ( SILAHKAN DISESUAIKAN)
//
RF24 radio(9,10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);            /*Setting baudrate of Serial Port to 9600*/
  radio.begin();
  
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0A1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();

}

void loop() {
  // put your main code here, to run repeatedly:
  char send_data[15] = "1|";
  int SensorValueMq7 = getSensorMq7();
  Serial.println(SensorValueMq7);
 
  char SaveValueMq7[10];
  //convert int to char
  itoa(SensorValueMq7,SaveValueMq7,10);
  Serial.println(SaveValueMq7);
  Serial.print("Start Send data : \n");
  //concat char sensor mq7
  strcat(send_data,SaveValueMq7);
  Serial.println(send_data);
  radio.write(&send_data, sizeof(send_data));
 

  delay(1000);
}

float getSensorMq7(){
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
