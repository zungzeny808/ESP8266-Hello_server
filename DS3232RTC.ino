#include <Wire.h>
#define SDA     D4
#define SCL     D5
typedef struct
{
	int _sec;
	int _min;
	int _hr;
	int _day_of_week;
	int _day;
	int _mounth;
	int _year;

	int temp_sec;
	int temp_min;
	int temp_hr;
	int temp_day_week;
	int temp_day;
	int temp_mounth;
	int temp_year;

}RTC_time;

RTC_time rtc_time;

uint8_t Buffer_data_TIME[] = {0, 1, 2,3,4,5,6,7,8,9,10,11,12,13};

static uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4); }
static uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10); }

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}


#define DS3231_ADDRESS 0x68
int Initial_RTC_I2C(void)
{

   Wire.begin(D5, D4); // sda , scl

}
uint8_t RTC_recive()
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS, 1);
  uint8_t ss = Wire.read();
  Serial.println((int)ss);
  return !(ss>>7);
}
uint8_t get_RTC_sec()
{
  return rtc_time._sec;
}
uint8_t get_RTC_min()
{
  return rtc_time._min;
}
uint8_t get_RTC_Hr()
{
  return rtc_time._hr;
}
uint8_t get_RTC_day()
{
  return rtc_time._day;
}
uint8_t get_RTC_day_of_week()
{
  return rtc_time._day_of_week;
}
String get_String_day_of_week()
{
  String day ="None day";
     switch(get_RTC_day_of_week())
     {
       case 1:
          day = "Sunday";
       break;
       case 2:
         day = "Monday";
       break;
       case 3:
         day = "Tuesday";
       break;
       case 4:
        day = "Wednesday";
       break;
       case 5:
       day = "Thursday";
       break;
       case 6:
        day = "Friday";
       break;
       case 7:
        day = "Saturday";
       break;
       default:
         day = "RTC_Error";
       break;
     
     }
  return day; 
}

uint8_t get_RTC_mounth()
{
  return rtc_time._mounth;
}
uint16_t get_RTC_year()
{
   return rtc_time._year;
}

void Now()
{
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(0);
    Wire.endTransmission();

    Wire.requestFrom(DS3231_ADDRESS, 19);
    
    uint8_t ss = bcd2bin(Wire.read() & 0x7F);
    uint8_t mm = bcd2bin(Wire.read());
    uint8_t hh = bcd2bin(Wire.read());
   // Wire.read();
    uint8_t d_f_w = bcd2bin(Wire.read());
    uint8_t d = bcd2bin(Wire.read());
    uint8_t m = bcd2bin(Wire.read());
    uint16_t y = bcd2bin(Wire.read()) + 2500;
    
    rtc_time._sec  = ss;
    rtc_time._min  = mm;
    rtc_time._hr   = hh;
    rtc_time._day_of_week = d_f_w;
    rtc_time._day = d;
    rtc_time._mounth = m;
    rtc_time._year   = y;
    delay(100);
    /*
      Serial.println("TIME");
      Serial.println(ss);
      Serial.println(mm);
      Serial.println(hh);
      Serial.println(d);
    */     
   // return DateTime (y, m, d, hh, mm, ss);
}
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void sethr(byte hr)
{
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(2); // set next input to start at the seconds register
    Wire.write(decToBcd(hr)); // set hours
    Wire.endTransmission();
}
void setmin(byte m)
{
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(1); // set next input to start at the seconds register
    Wire.write(decToBcd(m)); // set min
    Wire.endTransmission();
}
void setsec(byte s)
{
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(0); // set next input to start at the seconds register
    Wire.write(decToBcd(s)); // set sec
    Wire.endTransmission();
}
void setday(byte d)
{
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(4); // set next input to start at the seconds register
    Wire.write(decToBcd(d)); // set day
    Wire.endTransmission();
}
void setday_of_week(byte d)
{
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(3); // set next input to start at the seconds register
    Wire.write(decToBcd(d)); // set week
    Wire.endTransmission();
}
void setmonth(byte m)
{
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(5); // set next input to start at the seconds register
    Wire.write(decToBcd(m)); // set mount
    Wire.endTransmission();
}
void setyear(byte y)
{
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(6); // set next input to start at the seconds register
    Wire.write(decToBcd(y)); // set year
    Wire.endTransmission();
}

