#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoWebsockets.h>
#include <Tone32.h>
// wifi
#include "wifi_setup.hpp"

// constants
#include "constants.h"

// debounce
#include "Debounce.h"


using namespace websockets;


bool iA = false;
bool activated = false;
long tA = 0;

WebsocketsClient client;
char pathbuf[PATHBUFLEN];
bool connected;

boolean successful;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(INPINA,INPUT);

  connectWiFi();
  connected = client.connect(server_host, server_port, "/drum");
  if (!connected)
    {
        Serial.println("Connection Error: Failed to Connect!");
        return;
    }  

}


void loop() {
#ifndef SOCKET_DEBUG
  if (!connected)
    {
        Serial.println("Trying to reconnect!");
        connected = client.connect(server_host, server_port, "/drum");
    }
#endif

#ifndef DEBUG
  while (1 == 1){
#endif
    float octaves[] = {1, 2,2, 4};
    
    char midi_bytes[3] = {0,0,0};
    char midi_note_A = 59;
    // put your main code here, to run repeatedly:

    
    int valA = analogRead(INPINA);
    if(valA>850&&iA==false)
    {
    long tnewA = millis();
    iA=true;
    if((tnewA-tA  )>90){
        Serial.println("a hit");
        midi_note_A = 60;
    }
    }
    else if(valA<750&&iA==true)
    {
    //Serial.println(micros());
    //Serial.print("low");
    //Serial.println(val);
    iA=false;
    }


    #ifndef DEBUG

    midi_bytes[0] = 145;
    midi_bytes[1] = midi_note_A;
    midi_bytes[2] = 127;

    successful = client.sendBinary((const char *)midi_bytes, 3);

    if (!successful)
    {
        Serial.println("SubmitUserData: encountered error");
        delay(1000);
        connected = client.connect(server_host, server_port, "/drum");
        break;
    } 

    #endif
  #ifndef DEBUG
  }
  #endif
}