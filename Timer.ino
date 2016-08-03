#include <Ticker.h>

Ticker tickerRTC;
Ticker tickerDHT;
int Event_RTC;
int Event_DHT;
void Initial_ticker()
{
  tickerRTC.attach_ms(501, Update_RTC);
  tickerDHT.attach_ms(1000, Update_DHT);
}
 void Update_RTC()
{
  Event_RTC=1;
       
//   Serial.println("Update_RTC");
}
void Update_DHT()
{
    Event_DHT =1;
//  Serial.println("Update_DHT");
}



