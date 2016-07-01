#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

// the node ID that it will send to the server when it connects
String nodeID = "1";

// the device ID that it will send to the server when it connects
String deviceID;
int i = 1;

//the IP that is given to the device from the network it connects to
String deviceIP;

//the host that the msg would be send to "this is just the host the other part of the URL is set in the function sendToServer()
String host = "http://196.205.93.181:22355";


ESP8266WiFiMulti WiFiMulti;


char c;
String readString;



///////////////////////////////////////////////////////////////////////////////////////////
//This function connects the device to Wifi specified at the begining of it
void wifiConnect()
{
  //Wifi SSID & Password
  const char* ssid = "WattMAx";
  const char* password = "20162015";
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
//This is a function to send a string to the server
String sendToServer(String deviceID, String message)
{
  String response="";
  String url = "/api/readings/add_device_reading.php?device_id=" + deviceID + "&reading=" + message;
  
  // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        // configure traged server and url
        http.begin(host + url); //HTTP

        // start connection and send HTTP header
        int httpCode = http.GET();
        if(httpCode) {
            // HTTP header has been send and Server response header has been handled

            // file found at server
            if(httpCode == 200) {
                response = http.getString();

                //Print the server's response to the serial monitor
                Serial.println("Message sent!! , the server responded with :");
                Serial.println(response);
            }
        } else {
            Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
        }
    } 
    return response;
}
//////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////
//This function will ask the server if there any messages for this device and return the response
//the server will respond with either an empty string or the message
String anyMsgs()
{
  String response="";
  String url = "/api/message/request_message.php?device_id=" + deviceID;
  
  // wait for WiFi connection
        if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        // configure traged server and url
        http.begin(host + url); //HTTP

        // start connection and send HTTP header
        int httpCode = http.GET();
        if(httpCode) {
            // HTTP header has been send and Server response header has been handled
            
            // file found at server
            if(httpCode == 200) {
               response = http.getString();
            }
        } else {
            Serial.print("[HTTP] GET... failed, no connection or no HTTP server\n");
        }
    }
    return response;
}
///////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(115200);
  delay(10);
    
  wifiConnect();
  
  pinMode( 2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
}

void loop() {
//  digitalWrite( 2,LOW);
//  digitalWrite(12,LOW);
//  digitalWrite(13,LOW);
//  digitalWrite(14,LOW);
//  digitalWrite(15,LOW);
//  digitalWrite(16,LOW);
////////////////////////////////////////////////////////////////////////////
//get the readings from the arduino and send them to the DB by API

  while (Serial.available())
   {
       delay(100);  //small delay to allow input buffer to fill
       c = Serial.read();  //gets one byte from serial buffer
       if (c == ',')
        {
            break;
        } //breaks out of capture loop to print readstring

       readString += c;
       if(c==' ')
         {
          String ID = String(i);  
          sendToServer(ID, readString);
          Serial.print(readString); 
          i+=1;
          if(i == 7)
            {
               i = 1;
               delay(60000);   //delay 1 min
              
            }
         }
         
////////////////////////////////////////////////////////////////////////////
//Controlling the deivces


  String response = anyMsgs();
  if (response == "")
  { 
    delay(1000);
    return; 
  }
  else
  {
    Serial.println(response);
//////////////////////////////////////////////////////////////////////////////
//make device 1 on

    if (response.indexOf("pin11") != -1)
    {
      digitalWrite(2, HIGH);
      Serial.println("DEVICE 1 ON");
    }
//////////////////////////////////////////////////////////////////////////////
//make device 1 off

    if (response.indexOf("pin10") != -1)
    {
      digitalWrite(2, LOW);
      Serial.println("DEVICE 1 OFF");
    }

//////////////////////////////////////////////////////////////////////////////
//make device 2 on
    
    if (response.indexOf("pin21") != -1)
    {
      digitalWrite(12, HIGH);
      Serial.println("DEVICE 2 ON");
    }
//////////////////////////////////////////////////////////////////////////////
//make device 2 off

    if (response.indexOf("pin20") != -1)
    {
      digitalWrite(12, LOW);
      Serial.println("DEVICE 2 OFF");
    }

///////////////////////////////////////////////////////////////////////////////
//make device 3 on

    if (response.indexOf("pin31") != -1)
    {
      digitalWrite(13, HIGH);
      Serial.println("DEVICE 3 ON");
    }
///////////////////////////////////////////////////////////////////////////////
//make device 3 off

    if (response.indexOf("pin30") != -1)
    {
      digitalWrite(13, LOW);
      Serial.println("DEVICE 3 OFF");
    }

///////////////////////////////////////////////////////////////////////////////
//make device 4 on

    if (response.indexOf("pin41") != -1)
    {
      digitalWrite(14, HIGH);
      Serial.println("DEVICE 4 ON");
    }
///////////////////////////////////////////////////////////////////////////////
//make device 4 off

    if (response.indexOf("pin40") != -1)
    {
      digitalWrite(14, LOW);
      Serial.println("DEVICE 4 OFF");
    }

/////////////////////////////////////////////////////////////////////////////////
//make device 5 on

    if (response.indexOf("pin51") != -1)
    {
      digitalWrite(15, HIGH);
      Serial.println("DEVICE 5 ON");
    }
//////////////////////////////////////////////////////////////////////////////////
//make device 5 off    
    if (response.indexOf("pin50") != -1)
    {
      digitalWrite(15, LOW);
      Serial.println("DEVICE 5 OFF");
    }

///////////////////////////////////////////////////////////////////////////////////
//make device 6 on

    if (response.indexOf("pin61") != -1)
    {
      digitalWrite(16, HIGH);
      Serial.println("DEVICE 6 ON");
    }
////////////////////////////////////////////////////////////////////////////////////
//make device 6 off
    
    if (response.indexOf("pin60") != -1)
    {
      digitalWrite(16, LOW);
      Serial.println("DEVICE 6 OFF");
    }
////////////////////////////////////////////////////////////////////////////////////

  }

       
   } 
 readString=""; //clears variable for new input
 delay(1000); 

///////////////////////////////////////////////////////////////////////////////

}

