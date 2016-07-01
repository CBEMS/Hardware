#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
extern void slop_wdt_feed();
  // Create an instance of the server
  // specify the port to listen on as an argument
  WiFiServer server(80);

// the device ID that it will send to the server when it connects
String deviceID = "12";

//the IP that is given to the device from the network it connects to
String deviceIP;

//the host that the msg would be send to "this is just the host the other part of the URL is set in the function sendToServer()
String host = "lindabot.net23.net";


ESP8266WiFiMulti WiFiMulti;
double Vrms, Irms, activepower, apparentpower, powerfactor;
char c;
String readString;
char rec[68];

//This function connects the device to Wifi specified at the begining of it
void wifiConnect()
{
  //Wifi SSID & Password
  const char* ssid = "reda";
  const char* password = "pcf02450";
  
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
String sendToServer(String message)
{
                  Serial.println("sending...");
  String response="";
  String url = "/AlaaIOT/final/importMsg.php?deviceID=" + deviceID + "&msg=" + message;
  
  // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        // configure traged server and url
        http.begin(host, 80, url); //HTTP

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

void setup() {
 Serial.begin(9600);
 wifiConnect();
}

void loop() {
  
  Serial.println("Initializing");
  Serial.write(0x68);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x68);
Serial.write(0x23);
Serial.write(0x0A);
Serial.write(0x60);
Serial.write(0x00);
Serial.write(0x34);
Serial.write(0x12);
Serial.write(0x78);
Serial.write(0x56);
Serial.write(0xBC);
Serial.write(0x9A);
Serial.write(0xF0);
Serial.write(0xDE);
Serial.write(0x2B);
Serial.write(0x16);

while (Serial.available()) {
   delay(10);  //small delay to allow input buffer to fill
    c = Serial.read();  //gets one byte from serial buffer
   if (c == ',') {
     break;
   }  //breaks out of capture loop to print readstring
  
   readString += c;
 } 
   readString=""; //clears variable for new input

delay(100);
  //}
   
Serial.println("Requesting");
Serial.write(0x68);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x99);
Serial.write(0x68);
Serial.write(0x23);
Serial.write(0x02);
Serial.write(0x61);
Serial.write(0x00);
Serial.write(0xEC);
Serial.write(0x16);

while (Serial.available()) {
   delay(10);  //small delay to allow input buffer to fill
   //Serial.println("serial available");
   for (int i=0; i <= 67; i++)
   {
    c = Serial.read();  //gets one byte from serial buffer
//   if (c == ',') {
//     break;
//   }  //breaks out of capture loop to print readstring
     
     rec[i] =c ;
     
     Serial.println("serial available");

          char buf[9];
sprintf(buf, "%02x", rec[i]);
Serial.println(buf);
Serial.println(i);

    
   }
   if (c == ',') {
     break;
   }
}
//Serial.println("test");
//char buf[9];
//sprintf(buf, "%04x", rec[12]);
//Serial.println(buf);
//sprintf(buf, "%04x", rec[13]);
//Serial.println(buf);
//sprintf(buf, "%04x", rec[14]);
//Serial.println(buf);

    String x0 = String(rec[34], DEC);
    String x1 = String(rec[35], DEC);
    String x2 = String(rec[36], DEC); 
    String x3 = String(rec[37], DEC);
   
     long v0= x0.toInt();
     //Serial.println(v0);
  long v1= x1.toInt();
   //Serial.println(v1);
  long v2= x2.toInt();
   //Serial.println(v2);
  long v3= x3.toInt();
   //Serial.println(v3);
 
  double v= (v0 + v1 * 256.0 + v2 * 65536.0 + v3 * 16777216.0)/1000 ;
  if (v < 240) {
    Vrms=v;
    Serial.println("Voltage=");
   
  }
     Serial.println(Vrms);
   
  String y0 = String(rec[38], DEC);
    String y1 = String(rec[39], DEC);
    String y2 = String(rec[40], DEC); 
    String y3 = String(rec[41], DEC);
   
     long i0= y0.toInt();
     //Serial.println(v0);
  long i1= y1.toInt();
   //Serial.println(v1);
  long i2= y2.toInt();
   //Serial.println(v2);
  long i3= y3.toInt();
   //Serial.println(v3);
 
  double i= (i0 + i1 * 256.0 + i2 * 65536.0 + i3 * 16777216.0)/1000 ;
  if (i < 5000) {
    Irms=i;
    Serial.println("Current=");
    
  }
   Serial.println(Irms); 
    
  String z0 = String(rec[42], DEC);
    String z1 = String(rec[43], DEC);
    String z2 = String(rec[44], DEC); 
    String z3 = String(rec[45], DEC);
   
     long p0= z0.toInt();
     //Serial.println(v0);
  long p1= z1.toInt();
   //Serial.println(v1);
  long p2= z2.toInt();
   //Serial.println(v2);
  long p3= z3.toInt();
   //Serial.println(v3);
 
  double p= (p0 + p1 * 256.0 + p2 * 65536.0 + p3 * 16777216.0)/1000 ;
  if (p < 1150) {
    activepower=p;
    Serial.println("Active Power=");
    
  }
    Serial.println(activepower);

 String s0 = String(rec[50], DEC);
    String s1 = String(rec[51], DEC);
    String s2 = String(rec[52], DEC); 
    String s3 = String(rec[53], DEC);
   
     long ap0= s0.toInt();
     //Serial.println(v0);
  long ap1= s1.toInt();
   //Serial.println(v1);
  long ap2= s2.toInt();
   //Serial.println(v2);
  long ap3= s3.toInt();
   //Serial.println(v3);
 
  double ap= (ap0 + ap1 * 256.0 + ap2 * 65536.0 + ap3 * 16777216.0)/1000 ; 
   if (ap < 1150) {
    apparentpower=ap;
  }  

  double pf= p/ap ;
  if (pf <= 1.0) {
    powerfactor=pf;
    Serial.println("Power Factor=");  
  } 
  Serial.println(powerfactor); 

    String voltage = String(Vrms);
    //Serial.println(String(Vrms));
  //sentToServer function with a power value
  sendToServer(voltage);
extern void pp_soft_wdt_restart();
 delay(900); 
 extern void pp_soft_wdt_restart();
 delay(900); 
 extern void pp_soft_wdt_restart();
 delay(900);  
 

}
