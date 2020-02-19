//// Adding Libraries 
#include <SPI.h>             /* to handle the communication interface with the modem*/
#include <nRF24L01.h>        /* to handle this particular modem driver*/
#include <RF24.h>            /* the library which helps us to control the radio modem*/
#define led_pin 3            /* Connect LED anode to D3 (PWM pin) */

RF24 radio(9,10);             /* Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8 */                               
const byte Address[6] = "00009"; /* Address from which data to be received */

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);            /*Setting baudrate of Serial Port to 9600*/
radio.begin();                   /* Activate the modem*/
radio.openReadingPipe(1, Address); /* Sets the address of receiver from which program will receive the data*/
}

void loop() {
  delay(500);
// put your main code here, to run repeatedly:
radio.startListening();          /*Setting modem in Receiver mode*/
if (radio.available())
{
while (radio.available())              /* Loop until receiving valid data*/
{
int rx_data = 1 ;                    /* Variable to store received data */
Serial.println(rx_data);           /* Print received value on Serial Monitor */

radio.read(&rx_data, sizeof(rx_data));/* Read the received data and store in ' rx_data ' */
Serial.print("Received Data : ");
Serial.println(rx_data);           /* Print received value on Serial Monitor */
//analogWrite(led_pin , rx_data);/* Write received value to PWM pin 3 to which LED is connected */
}
}
  
else
{
Serial.println("Not Receiving !!!"); /* If not receiving valid data print " Not Receiving !!! " on Serial Monitor  */
  }
  ///// END OF LOOP //////
}
