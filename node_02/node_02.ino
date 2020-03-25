#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>


RF24 radio(9,10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);            /*Setting baudrate of Serial Port to 9600*/
  radio.begin();
  
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0A2LL);
//   radio.openWritingPipe(address);
  radio.enableDynamicPayloads();
  radio.powerUp();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Start Send data : \n");
  char text[] = "20|40|60";

  Serial.println(text);
  radio.write(&text, sizeof(text));
  //radio.write(&coba2, sizeof(coba2));
  

  delay(1000);
}
