/*--------------------------------------------------
Telnet to Serial AccessPoint for ESP8266 
for ESP8266 adapted Arduino IDE

by Stefan Thesen 08/2015 - free for anyone
http://blog.thesen.eu

Creates an accesspoint or network client which can 
be connected by telnet; e.g. telnet 192.168.4.1
Telnet input is sent to serial and vice versa.

Serial output can e.g. be used to steer an attached
Arduino or other serial interfaces.
Please take care for levels of the serial lines.

Code inspired by a post of ghost on github:
https://github.com/esp8266/Arduino/issues/307
--------------------------------------------------*/
#include <HardwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define BUFFERSIZE 512

////////////////////////////////////
// settings for Telnet2Serial Bridge
////////////////////////////////////

// max number of clients that can connect
#define MAX_NO_CLIENTS 5

//#define AP_MODE

// shall local echo in telnet be suppressed (usually yes)
#define SUPPRESSLOCALECHO 

// speed of the serial connection
#define SERIALSPEED 115200

#ifdef AP_MODE
  const WiFiMode wifi_mode = WIFI_AP;     // access-point
  const char* ssid = "TEL2SER";   // Name of AP 
#else
  const WiFiMode wifi_mode = WIFI_STA;     // WIFI client
  const char* ssid = "XXXXX";   // Name of Wifi to connect to (for WIFI_STA)
#endif
const char* password = "XXXXX";      // set to "" for open access point w/o password

// Create an instance of the server on Port 23
WiFiServer server(23);
WiFiClient pClientList[MAX_NO_CLIENTS]; 
char sbuf[BUFFERSIZE];

void setup() 
{
  // start serial
  Serial.setRxBufferSize(BUFFERSIZE);
  Serial.begin(SERIALSPEED);

  pinMode(LED_BUILTIN,OUTPUT);

  WiFi.mode(wifi_mode);
  #ifdef AP_MODE
    WiFi.softAP(ssid, password);
  #else
    // network cient - inital connect
    WiFiStart();
  #endif

  // Port defaults to 8266
  ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("TEL2SER");

  // No authentication by default
  ArduinoOTA.setPassword("XXXXX");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    Serial.println("#Start updating sketch");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\n#End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("#Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();

  #ifndef AP_MODE
    IPAddress ip = WiFi.localIP();
    Serial.println();
    Serial.print("Connected : ");
    Serial.println(ip);
  #endif
  // Start the server
  server.begin();
  server.setNoDelay(true);
}

#ifndef AP_MODE
  void WiFiStart()
  { 
    // Connect to WiFi network
    WiFi.begin(ssid, password);
  
    if (WiFi.waitForConnectResult() != WL_CONNECTED) ESP.restart();
  }
#endif

void delay_OTA(unsigned long msec)
{
  if (msec == 0)
  {
    ArduinoOTA.handle();
    yield();    
    return;
  }

  unsigned long stopm = millis() + msec;
  while (stopm > millis())
  {
    ArduinoOTA.handle();
    yield();    
  }
}

void loop() 
{ 
  int ii;

  ////////////////////////////////////////////////
  // if network client: check if WLAN is connected
  ////////////////////////////////////////////////
  #ifndef AP_MODE
    if (WiFi.status() != WL_CONNECTED)
    {
      WiFiStart();
      // Start the server
      server.begin();
      server.setNoDelay(true);
    }
  #endif
  
  /////////////////////
  // handle new clients
  /////////////////////
  if (server.hasClient())
  {
    bool bFoundPlace=false;
    
    // search a free spot
    for(ii = 0; ii < MAX_NO_CLIENTS; ii++)
    {
      if (!pClientList[ii] || !pClientList[ii].connected())
      {
        // remove old connections
        if(pClientList[ii]) 
        {
          pClientList[ii].stop();
        }

        // new client
        pClientList[ii] = server.available();
	      #ifdef SUPPRESSLOCALECHO
          pClientList[ii].write("\xFF\xFB\x01", 3); 
        #endif
        pClientList[ii].write("Welcome to Telnet2Serial Adapter - S. Thesen 08/2015 - https://blog.thesen.eu\r\n"); 
        bFoundPlace=true;
        break;
      }
    }

    //no free spot --> sorry
    if (!bFoundPlace)
    {
      WiFiClient client = server.available();
      client.stop();
    }
  }

  /////////////////////
  // Telnet --> Serial
  /////////////////////
  for(ii = 0; ii < MAX_NO_CLIENTS; ii++)
  {
    if (pClientList[ii] && pClientList[ii].connected())
    {
      if(pClientList[ii].available())
      {
        while(pClientList[ii].available()) 
        {
          char c = pClientList[ii].read();
          if ((c > 0) && (c <= 127)) Serial.write(c);
          delay_OTA(1);
        }
      }
    }
  }

  /////////////////////
  // Serial --> Telnet
  /////////////////////
  if(Serial.available())
  {
    size_t len = Serial.read(sbuf, BUFFERSIZE);
    ArduinoOTA.handle();

    for(ii = 0; ii < MAX_NO_CLIENTS; ii++)
    {
      if (pClientList[ii] && pClientList[ii].connected())
      {
        pClientList[ii].write(sbuf, len);
        delay_OTA(1);
      }
    }
  }
  ArduinoOTA.handle();
}
