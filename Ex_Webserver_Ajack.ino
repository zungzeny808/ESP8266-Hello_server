

#include <ESP8266WiFi.h>
#include "DHT.h"
#include "Timer.h"


const char* ssid = "Wilddesk";
const char* password = "whitelegbluedress";
#define Relay1 D1
#define Relay2 D2
int  Relay_1= 0;
int  Relay_2 = 0;
#define DHTPIN 12
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE,15);
WiFiServer server(80);

IPAddress ip(192,168,1,128);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0); // fix IP 


void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  digitalWrite(Relay1,LOW);
  digitalWrite(Relay2,LOW);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet,IPAddress(192,168,1,128)); // fix IP 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  
  Initial_RTC_I2C();
  Initial_ticker();
  //
  
  //
 // setDS3231time(10,22,2,1,19,6,59);
}
 float hum;
 float temp;


void loop() {
/// Update_DS3231();
// RTC_recive();
  if(Event_RTC == 1)
  {
   Now();
   Event_RTC = 0;
  }
  if(Event_DHT == 1)
  {
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    Event_DHT =0;
  }

  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  if (req.indexOf("/r1off.html") != -1)
  {
     Relay_1 = 0;
    digitalWrite(Relay1,LOW);
     
  }
  else if (req.indexOf("/r1on.html") != -1)
  {
     Relay_1 = 1;
    digitalWrite(Relay1,HIGH);
  }
   else if (req.indexOf("/r2on.html") != -1)
  {
     Relay_2 = 1;
    digitalWrite(Relay2,HIGH);
  }
   else if (req.indexOf("/r2off.html") != -1)
  {
    Relay_2 = 0;
    digitalWrite(Relay2,LOW);
  }
  else if(req.indexOf("/Temp_.html") != -1)
  {

     int  hr = get_RTC_Hr();
     int  mm = get_RTC_min();
     int  sec = get_RTC_sec();
     int  day = get_RTC_day();
     String  day_of_week = get_String_day_of_week();
     int  mount = get_RTC_mounth();
     int  year =  get_RTC_year();
  //  Serial.println(String(t));
    client.flush();
    String massage=String(temp)+":"+String(hum)+":"+String(Relay_1)+":"+String(Relay_2)+":";
           massage+=String(hr)+":"+String(mm)+":"+String(sec)+":";
           massage+=day_of_week+":"+String(day)+":"+String(mount)+":"+String(year);
           
    client.print(massage);
  }
  else if(req.indexOf("/Settime/Temp_.html") != -1)
  {

     int  hr = get_RTC_Hr();
     int  mm = get_RTC_min();
     int  sec = get_RTC_sec();
     int  day = get_RTC_day();
     String  day_of_week = get_String_day_of_week();
     int  mount = get_RTC_mounth();
     int  year =  get_RTC_year();
  //  Serial.println(String(t));
    client.flush();
    String massage=String(temp)+":"+String(hum)+":"+String(Relay_1)+":"+String(Relay_2)+":";
           massage+=String(hr)+":"+String(mm)+":"+String(sec)+":";
           massage+=day_of_week+":"+String(day)+":"+String(mount)+":"+String(year);
           
    client.print(massage);
  }
  else if(req.indexOf("/LEDS_TEST_.html") != -1)
  {
      int LED_1 = 0;
      int LED_2 = 0;
    // String test;
  

    // client.print(test);
  }
  else if(req.indexOf("/Settime") != -1)
  {
     page_Set_Time(&client);
      return;
  }
  else if(req.indexOf("/") != -1)
  {
    page_Frist(&client);
    return;
  }
  
  
}

