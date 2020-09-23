// Instructables Internet of Things Class sample code
// Circuit Triggers Internet Action
// A button press is detected and stored in a feed
// An LED is used as confirmation feedback
//
// Modified by Becky Stern 2017
// based on the Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************ Adafruit IO Configuration *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "user"
#define IO_KEY         "number"

/******************************* WIFI Configuration **************************************/

#define WIFI_SSID       "name"
#define WIFI_PASS       "pass"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Main Program Starts Here *******************************/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>


#define switch 0
#define output 2




// set up the 'name of feed' feed
AdafruitIO_Feed *name of feed = io.feed("name of feed");

// button/switch state
bool current = 0;
bool state = 0; // at first put 0, so that it's on when powered up


void setup() {

  // set button pin as an input
  pinMode(switch, INPUT);
  pinMode(output, OUTPUT);
  current = digitalRead(switch);

  Serial.begin(9600);
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  // set up a message handler for the 'name of feed' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  name of feed->onMessage(handleMessage1);
 
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  
  digitalWrite(output, state);
 

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  button1();
  //to power up correctly, the switch must be in logic 1 
   
  
}


void handleMessage1(AdafruitIO_Data *data) {

  int name of feed = data->toInt();
  
  if (name of feed == 1){ //light up the LED
    Serial.println("name of feed:");
    Serial.print("received <- ");
    Serial.println(name of feed);
    state = !state;
    digitalWrite(output, state);
    Serial.print("output state: ");
    Serial.println(state);
  } 
  // if u want to see the received 0
  /*else {
    Serial.print("received <- ");
    Serial.println(name of feed);
  }
  */
}

void button1(){
  // for two state switch triger
  if(digitalRead(switch) != current){
     current = !current;
     state = !state;
  }
  // save the current state to the 'output' 
  digitalWrite(output, state);



  
  /* for a button triger
    if((digitalRead(switch) == LOW) and (current == 0)){
      state = !state;
      current = 1;
    }  
    if(digitalRead(switch) == HIGH){
      current = 0;
    }
    
    // save the current state to the 'output' 
    digitalWrite(output, state);
    */
}
