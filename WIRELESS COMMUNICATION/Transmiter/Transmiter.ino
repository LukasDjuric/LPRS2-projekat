#include "SPI.h" 
#include "RF24.h" 
#include "nRF24L01.h" 
#define CE_PIN 9 
#define CSN_PIN 10 
#define INTERVAL_MS_TRANSMISSION 250 
RF24 radio(CE_PIN, CSN_PIN); 
const byte address[6] = "00001"; 
//NRF24L01 buffer limit is 32 bytes (max struct size) 
struct payload { 
   int data1; 
   float data2; 
   float data3;
}; 
payload payload; 
void setup() 
{ 
   Serial.begin(115200); 
   radio.begin(); 
   delay(50);
   //Append ACK packet from the receiving radio back to the transmitting radio 
   radio.setAutoAck(false); //(true|false) 
   //Set the transmission datarate 
   radio.setDataRate(RF24_250KBPS); //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS) 
   //Greater level = more consumption = longer distance 
   radio.setPALevel(RF24_PA_MAX); //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX) 
   //Default value is the maximum 32 bytes 
   radio.setPayloadSize(sizeof(payload)); 
   //Act as transmitter 
   radio.openWritingPipe(address); 
   radio.stopListening(); 
} 
void loop() 
{ 
   payload.data1 = 5; 
   payload.data2 = 0.01; 
   payload.data3 = payload.data1 * payload.data2;
   radio.write(&payload, sizeof(payload)); 
   Serial.print("Napon:"); 
   Serial.println(payload.data1); 
   Serial.print("Struja:"); 
   Serial.println(payload.data2); 
   Serial.print("Snaga:"); 
   Serial.println(payload.data3);
   Serial.println("Sent"); 
   delay(INTERVAL_MS_TRANSMISSION); 
}
