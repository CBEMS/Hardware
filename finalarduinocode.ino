const int S0 = A0;
const int S1 = A1;
const int S2 = A2;
const int S3 = A3;
const int S4 = A4;
const int S5 = A5;

int mVperAmp = 185;
double Voltage0, Voltage1, Voltage2, Voltage3, Voltage4, Voltage5 = 0;
double VRMS0, VRMS1, VRMS2, VRMS3, VRMS4, VRMS5 = 0;
double AmpsRMS0, AmpsRMS1, AmpsRMS2, AmpsRMS3, AmpsRMS4, AmpsRMS5 = 0;


///////////////////////////////////////////////////////////////////////////
//calculations of currecnt readings


float getVPP(int S)
  {
    float result;
    int readValue;
    int maxValue = 0;
    int minValue = 1024;

    uint32_t start_time = millis();
    while ((millis() -start_time) < 1000)
     {
       if (S==S0)
        {
          readValue = analogRead(S0);
        }

        else if (S==S1)
        {
          readValue = analogRead(S1);
        }

        else if (S==S2)
        {
          readValue = analogRead(S2);
        }

        else if (S==S3)
        {
          readValue = analogRead(S3);
        }

        else if (S==S4)
        {
          readValue = analogRead(S4);
        }

        else if (S==S5)
        {
          readValue = analogRead(S5);
        }
        
       if (readValue > maxValue)
         {
           maxValue = readValue;
         }
       if (readValue < minValue)
         {
           minValue = readValue;
         }
      }
  result = ((maxValue - minValue) * 5.0)/1024.0;
  return result;
  }
  
void setup() {

    pinMode(S0, INPUT);
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);
    pinMode(S5, INPUT);
    
    Serial.begin(115200);
}

//////////////////////////////////////////////////////////////////////////


void loop() {


//////////////////////////////////////////////////////////////////////////
//for device 1

  Voltage0 = getVPP(S0);
  VRMS0 = (Voltage0/2.0) * 0.707;
  AmpsRMS0 = (VRMS0 * 1000) / mVperAmp;
  Serial.print(AmpsRMS0);
  Serial.println("  Amps RMS");
  String device1 = String(AmpsRMS0);  
  for (int k = 0; k < device1.length(); k++)
     {
      
       Serial.write(device1[k]);   // Push each char 1 by 1 on each loop pass
       Serial.println(device1[k]);   // Push each char 1 by 1 on each loop pass
  
     }
Serial.write(" ");


/////////////////////////////////////////////////////////////////////////////////
//for device 2

  Voltage1 = getVPP(S1);
  VRMS1 = (Voltage1/2.0) * 0.707;
  AmpsRMS1 = (VRMS1 * 1000) / mVperAmp;
  Serial.print(AmpsRMS1);
  Serial.println("   Amps RMS");
  String device2 = String(AmpsRMS1);  
  for (int s = 0; s < device2.length(); s++)
     {
      
       Serial.write(device2[s]);   // Push each char 1 by 1 on each loop pass
       Serial.println(device2[s]);   // Push each char 1 by 1 on each loop pass
  
     }     
Serial.write(" ");


////////////////////////////////////////////////////////////////////////////////////
//for device 3

  Voltage2 = getVPP(S2);
  VRMS2 = (Voltage2/2.0) * 0.707;
  AmpsRMS2 = (VRMS2 * 1000) / mVperAmp;
  Serial.print(AmpsRMS2);
  Serial.println("   Amps RMS");
  String device3 = String(AmpsRMS2);  
  for (int d = 0; d < device3.length(); d++)
     {
      
       Serial.write(device3[d]);   // Push each char 1 by 1 on each loop pass
  
     }          
Serial.write(" ");


////////////////////////////////////////////////////////////////////////////////
//for device 4

  Voltage3 = getVPP(S3);
  VRMS3 = (Voltage3/2.0) * 0.707;
  AmpsRMS3 = (VRMS3 * 1000) / mVperAmp;
  Serial.print(AmpsRMS3);
  Serial.println("   Amps RMS");
  String device4 = String(AmpsRMS3);  
  for (int c = 0; c < device4.length(); c++)
     {
      
       Serial.write(device4[c]);   // Push each char 1 by 1 on each loop pass
  
     }     
Serial.write(" ");


/////////////////////////////////////////////////////////////////////////////
//for device 5

  Voltage4 = getVPP(S4);
  VRMS4 = (Voltage4/2.0) * 0.707;
  AmpsRMS4 = (VRMS4 * 1000) / mVperAmp;
  Serial.print(AmpsRMS4);
  Serial.println("   Amps RMS");
  String device5 = String(AmpsRMS4);  
  for (int b = 0; b < device5.length(); b++)
     {
      
       Serial.write(device5[b]);   // Push each char 1 by 1 on each loop pass
  
     }     
Serial.write(" ");


//////////////////////////////////////////////////////////////////////////////
//for device 6

  Voltage5 = getVPP(S5);
  VRMS5 = (Voltage5/2.0) * 0.707;
  AmpsRMS5 = (VRMS5 * 1000) / mVperAmp;
  Serial.print(AmpsRMS5);
  Serial.println("    Amps RMS");
  String device6 = String(AmpsRMS5);  
  for (int a = 0; a < device6.length(); a++)
     {
      
       Serial.write(device6[a]);   // Push each char 1 by 1 on each loop pass
  
     }     
Serial.write(" ");


///////////////////////////////////////////////////////////////////////////////


}

