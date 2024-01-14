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

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

Debounce Button1(33); // 4 is the pin, could be a variable too.
Debounce Button2(32); // 4 is the pin, could be a variable too.
Debounce Button3(25); // 4 is the pin, could be a variable too.
Debounce Button4(26); // 4 is the pin, could be a variable too.

const double freqs[] = {0,261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.00,415.30,440,466.16,493.88,523.25};
int noteVal;
char last_note = 0;

WebsocketsClient client;
char pathbuf[PATHBUFLEN];
bool connected;

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 27 as an output

  pinMode(led, OUTPUT); // Set buzzer - pin 27 as an output

  ledcAttachPin(buzzer, 0);

//   ledcAttach(led, 200, 10);
  Serial.begin(9600);  

  connectWiFi();
  connected = client.connect(server_host, server_port, "/1");
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
        connected = client.connect(server_host, server_port, "/1");
    }
#endif

#ifndef DEBUG
  while (1 == 1){
#endif
    float octaves[] = {1, 2,2, 4};
    
    char midi_bytes[3] = {0,0,0};
    char midi_note = 0;
    // put your main code here, to run repeatedly:
    buttonState1 = !Button1.read();
    buttonState2 = !Button2.read();
    buttonState3 = !Button3.read();
    buttonState4 = !Button4.read();
    
    int buttons = buttonState1<<3 | buttonState1<<2 | buttonState1<<1 | buttonState1; 

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState1 == LOW)
    {
        digitalWrite(led,HIGH);
        if (buttonState2 == LOW)
        {
        if (buttonState3 == LOW)
        {
            if (buttonState4 == LOW)
            {
            noteVal = 0;
            midi_note = 59;
            }
            else
            {
            noteVal = 1;
            midi_note = 60;
            }
        }
        else
        {
            if (buttonState4 == LOW)
            {
            noteVal = 2;
            midi_note = 61;
            }
            else
            {
            noteVal = 3;
            midi_note = 62;
            }
        }
        }
        else
        {
        if (buttonState3 == LOW)
        {
            if (buttonState4 == LOW)
            {
            noteVal = 4;
            midi_note = 63;
            }
            else
            {
            noteVal = 5;
            midi_note = 64;
            }
        }
        else
        {
            if (buttonState4 == LOW)
            {
            noteVal = 6;
            midi_note = 65;
            }
            else
            {
            noteVal = 7;
            midi_note = 66;
            }
        } 
        }
    }
    else
    {
        digitalWrite(led,LOW);
        if (buttonState2 == LOW)
        {
        if (buttonState3 == LOW)
        {
            if (buttonState4 == LOW)
            {
            noteVal = 8;
            midi_note = 67;
            }
            else
            {
            noteVal = 9;
            midi_note = 68;
            }
        }
        else
        {
            if (buttonState4 == LOW)
            {
            noteVal = 10;
            midi_note = 69;
            }
            else
            {
            noteVal = 11;
            midi_note = 70;
            }
        }
        }
        else
        {
        if (buttonState3 == LOW)
        {
            if (buttonState4 == LOW)
            {
            noteVal = 12;
            midi_note = 71;
            }
            else
            {
            noteVal = 13;
            midi_note = 72;
            }
        }
        else
        {
            if (buttonState4 == LOW)
            {
            noteVal = 14;
            }
            else
            {
            noteVal = 15;
            }
        } 
        }
    }
    
    if (noteVal == 0 || noteVal == 14 || noteVal == 15)
    {
        noTone(buzzer, 0);
    }
    else {
        tone(buzzer, freqs[noteVal],100, 0);
        // ledcWriteTone(0, 20* freqs[noteVal]);
        // tone(buzzer, 2* freqs[noteVal], 500, 0);
        // tone(buzzer, 2* freqs[noteVal], 0);

    }
    delay(30);
    #ifndef DEBUG
    if (last_note != noteVal){

        Serial.println(noteVal);

        // midi_bytes[0] = 145;
        // midi_bytes[1] = midi_note;
        // midi_bytes[2] = 127;
    }

    midi_bytes[0] = 145;
    midi_bytes[1] = midi_note;
    midi_bytes[2] = 127;

    boolean successful = client.sendBinary((const char *)midi_bytes, 3);

    if (!successful)
    {
        Serial.println("SubmitUserData: encountered error");
        delay(1000);
        connected = client.connect(server_host, server_port, "/1");
        break;
    } 
    last_note = noteVal;
    #endif
  #ifndef DEBUG
  }
  #endif
}