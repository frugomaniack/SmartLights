#define WIFI_NAME "yourwifi"
#define WIFI_PASSWORD "password"
#define DEVICE_ID 1002
#define DEVICE_NAME "SmartLights"
#define TOKEN "~yourtoken"


#include <RemoteMe.h>
#include <RemoteMeSocketConnector.h>
#include <ESP8266WiFi.h>


boolean lampa1=0;
boolean lampa2=0;
boolean lampa3=0;
boolean lampa4=0;
boolean lamps=0;

RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

//*************** CODE FOR COMFORTABLE VARIABLE SET *********************

inline void setLamp1(boolean b) {remoteMe.getVariables()->setBoolean("lamp1", b); }
inline void setLamp2(boolean b) {remoteMe.getVariables()->setBoolean("lamp2", b); }
inline void setLamp3(boolean b) {remoteMe.getVariables()->setBoolean("lamp3", b); }
inline void setLamp4(boolean b) {remoteMe.getVariables()->setBoolean("lamp4", b); }
inline void setLamps(boolean b) {remoteMe.getVariables()->setBoolean("lamps", b); }

//*************** IMPLEMENT FUNCTIONS BELOW *********************


void onLamp1Change(boolean b) {
  Serial.printf("onLamp1Change: b: %d\n",b);
  lampa1=b;
}
void onLamp2Change(boolean b) {
  Serial.printf("onLamp2Change: b: %d\n",b);
  lampa2=b;
}
void onLamp3Change(boolean b) {
  Serial.printf("onLamp3Change: b: %d\n",b);
  lampa3=b;
}
void onLamp4Change(boolean b) {
  Serial.printf("onLamp4Change: b: %d\n",b);
  lampa4=b;
}

void onLampsChange(boolean b) {
  Serial.printf("onLampsChange: b: %d\n",b);
  lamps=b;
  if(lamps==1)
  {
     lampa1=1;
       lampa2=1;
       lampa3=1;
       lampa4=1;
  }
  else
  {
     lampa1=0;
       lampa2=0;
       lampa3=0;
       lampa4=0;
  }
}






void setup() {
  Serial.begin(115200);

pinMode(D5,OUTPUT);
pinMode(D6,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(D8,OUTPUT);

  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  remoteMe.getVariables()->observeBoolean("lamp1" ,onLamp1Change);
  remoteMe.getVariables()->observeBoolean("lamp2" ,onLamp2Change);
  remoteMe.getVariables()->observeBoolean("lamp3" ,onLamp3Change);
  remoteMe.getVariables()->observeBoolean("lamp4" ,onLamp4Change);
 remoteMe.getVariables()->observeBoolean("lamps" ,onLampsChange);
 
  remoteMe.setConnector(new RemoteMeSocketConnector());
  remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);

       lampa1=0;
       lampa2=0;
       lampa3=0;
       lampa4=0;
       digitalWrite(D5,LOW);
       digitalWrite(D6,LOW);
       digitalWrite(D7,LOW);
       digitalWrite(D8,LOW);
}


void loop() {
  remoteMe.loop();


   if (WiFi.status() != WL_CONNECTED) {
       lampa1=0;
       lampa2=0;
       lampa3=0;
       lampa4=0;
    }

    
  if(lampa1==1)
  {
    digitalWrite(D5,HIGH);
  }
  else
  {
    digitalWrite(D5,LOW);
  }

   if(lampa2==1)
  {
    digitalWrite(D6,HIGH);
  }
  else
  {
    digitalWrite(D6,LOW);
  }

   if(lampa3==1)
  {
    digitalWrite(D7,HIGH);
  }
  else
  {
    digitalWrite(D7,LOW);
  }

    if(lampa4==1)
  {
    digitalWrite(D8,HIGH);
  }
  else
  {
    digitalWrite(D8,LOW);
  }
}
