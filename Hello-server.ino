#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Wilddesk";
const char* password = "whitelegbluedress";

ESP8266WebServer server(80);
#define LED_ON 0
#define LED OFF 1
const int led_1 = 4;
const int led_2 = 5;
boolean value_led[2]; 
String WebString = "";
int time_call;

void ON1() {
    WebString = "<html>";
    WebString +="<head>";
    WebString += "<meta http-equiv=";
    WebString +="refresh";
    WebString +=" content=";
    WebString +='"';
    WebString +="1; ";
    WebString +="URL=http";
    WebString +=':';
    WebString +='/';
    WebString +='/';
    WebString +="192.168.1.37";
    WebString +='"';
    WebString +=';';
    WebString +='"';
    WebString +=" />";
    WebString +="</head>"; 
   

    WebString +="<body>";
    WebString +="<p>";
    WebString +="Light 1 - ON";
    WebString +="</p>";
    WebString +="</body>";
    
    WebString +="</html>";
    value_led[0] = true;
 //    Serial.print("LED ON");
    server.send(200, "text/html", WebString);
}
void OFF1 (){
    WebString = "<html>";
    WebString +="<head>";
    WebString += "<meta http-equiv=";
    WebString +="refresh";
    WebString +=" content=";
    WebString +='"';
    WebString +="1; ";
    WebString +="URL=http";
    WebString +=':';
    WebString +='/';
    WebString +='/';
    WebString +="192.168.1.37";
    WebString +='"';
    WebString +=';';
    WebString +='"';
    WebString +=" />";
    WebString +="</head>"; 
   

    WebString +="<body>";
    WebString +="<p>";
    WebString +="Light 1 - OFF";
    WebString +="</p>";
    WebString +="</body>";
    
    WebString +="</html>";
     value_led[0] = false;
  //  Serial.print("LED OFF");
    server.send(200, "text/html", WebString);
}
void ON2(){
    WebString = "<html>";
    WebString +="<head>";
    WebString += "<meta http-equiv=";
    WebString +="refresh";
    WebString +=" content=";
    WebString +='"';
    WebString +="1; ";
    WebString +="URL=http";
    WebString +=':';
    WebString +='/';
    WebString +='/';
    WebString +="192.168.1.37";
    WebString +='"';
    WebString +=';';
    WebString +='"';
    WebString +=" />";
    WebString +="</head>"; 
   

    WebString +="<body>";
    WebString +="<p>";
    WebString +="Light 2 - ON";
    WebString +="</p>";
    WebString +="</body>";
    
    WebString +="</html>";
     value_led[1] = true;
  server.send(200, "text/html", WebString);
}
void OFF2(){
   WebString = "<html>";
    WebString +="<head>";
    WebString += "<meta http-equiv=";
    WebString +="refresh";
    WebString +=" content=";
    WebString +='"';
    WebString +="1; ";
    WebString +="URL=http";
    WebString +=':';
    WebString +='/';
    WebString +='/';
    WebString +="192.168.1.37";
    WebString +='"';
    WebString +=';';
    WebString +='"';
    WebString +=" />";
    WebString +="</head>"; 
   

    WebString +="<body>";
    WebString +="<p>";
    WebString +="Light 2 - OFF";
    WebString +="</p>";
    WebString +="</body>";
    
    WebString +="</html>";
     value_led[1] = false;
    server.send(200, "text/html", WebString);

}

void handleRoot() {
  WebString = "<html>";
  WebString +="<head>";
  
  WebString += "<meta http-equiv=";
  WebString +="refresh";
  WebString +=" content=";
  WebString +='"';
  WebString +="3";
  WebString +='"';
  WebString +=" />";
  
  WebString +="<meta http-equiv=";
  WebString +='"';
  WebString +="Content-Language";
  WebString +='"';
  WebString +=" content=";
  WebString +='"';
  WebString +="th";
  WebString +='"';
  WebString +=">";
  
  WebString +="<meta http-equiv=";
  WebString +='"';
  WebString +="Content-Type";
  WebString +='"';
  WebString +=" content=";
  WebString +='"';
  WebString +="text/html; Charset=Utf-8";
  WebString +='"';
  WebString +=">";
  
  WebString +="</head>";
  WebString +="<body>";
  ///////////////////////////////////////
  if(value_led[0] == true)
  {
  WebString +="<p>";
  WebString +="<button style=";
  WebString +='"';
  WebString +="background-color:lightgreen";
  WebString +='"';
  WebString +=">ไฟดวงที่ 1</button>";
  WebString +="</p>";
  
  }
  else
  {
    WebString +="<p>";
    WebString +="<button style=";
    WebString +='"';
    WebString +="background-color:Red";
    WebString +='"';
    WebString +=">ไฟดวงที่ 1</button>";
    WebString +="</p>";
  

  }
  
    WebString +="<p>";
    WebString +="Light 1";
    WebString +="</p>";
    
  WebString += "<p>";
  
  WebString +="<a href=";
  WebString +='"';
  WebString +="http";
  WebString +=':';
  WebString +='/';
  WebString +='/';
  WebString +="192.168.1.37/ON_1";
  WebString +='"';
  WebString +="><button style=";
  WebString +='"';
  WebString +="background-color:Green";
  WebString +='"';
  WebString +=">ON</button></a>";
 
  WebString +="<a href=";
  WebString +='"';
  WebString +="http";
  WebString +=':';
  WebString +='/';
  WebString +='/';
  WebString +="192.168.1.37/OFF_1";
  WebString +='"';
  WebString +="><button style=";
  WebString +='"';
  WebString +="background-color:Red";
  WebString +='"';
  WebString +=">OFF</button></a>";
  ///////////////////////////////////////
  WebString += "</p>";
  ////////////////////////////////////////
  
  
  if(value_led[1] == true)
  {
  WebString +="<p>";
  WebString +="<button style=";
  WebString +='"';
  WebString +="background-color:lightgreen";
  WebString +='"';
  WebString +=">ไฟดวงที่ 2</button>";
  WebString +="</p>";
  
  }
  else
  {
    WebString +="<p>";
    WebString +="<button style=";
    WebString +='"';
    WebString +="background-color:Red";
    WebString +='"';
    WebString +=">ไฟดวงที่ 2</button>";
    WebString +="</p>";
  }
  
  
  
  WebString +="<p>";
  WebString +="Light 2";
  WebString +="</p>";
  
  
  WebString += "<p>";
  
  WebString +="<a href=";
  WebString +='"';
  WebString +="http";
  WebString +=':';
  WebString +='/';
  WebString +='/';
  WebString +="192.168.1.37/ON_2";
  WebString +='"';
  WebString +="><button style=";
  WebString +='"';
  WebString +="background-color:Green";
  WebString +='"';
  WebString +=">ON</button></a>";
 
  WebString +="<a href=";
  WebString +='"';
  WebString +="http";
  WebString +=':';
  WebString +='/';
  WebString +='/';
  WebString +="192.168.1.37/OFF_2";
  WebString +='"';
  WebString +="><button style=";
  WebString +='"';
  WebString +="background-color:Red";
  WebString +='"';
  WebString +=">OFF</button></a>";
  ///////////////////////////////////////
  WebString += "</p>";
  
  
  
  WebString +="</body>";
  WebString +="</html>";
  
  
  
  time_call++;
  server.send(200, "text/html", WebString);
//  digitalWrite(led, 0);
}

void handleNotFound(){
 // digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
 // digitalWrite(led, 0);
}

void setup(void){
  pinMode(led_1, OUTPUT);    // Pin D7
  pinMode(led_2, OUTPUT);      // Pin D1

  
 // digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("setup wifi");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });
  server.on("/ON_1",ON1);
  server.on("/OFF_1",OFF1);
  server.on("/ON_2",ON2);
  server.on("/OFF_2",OFF2);
  
  

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
   
   if(value_led[0] == true)
   {
     digitalWrite(led_1,1);
   }
   else
   {
      digitalWrite(led_1,0);
   }
    if(value_led[1] == true)
    {
       digitalWrite(led_2,1);
    }
    else
    {
       digitalWrite(led_2,0);

    }
  
     
}
