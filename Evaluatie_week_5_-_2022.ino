#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLjHqHVrSR"
#define BLYNK_DEVICE_NAME "test"
#define BLYNK_AUTH_TOKEN "FQEWU_JgdDj-b7DyUpEqY0LdIIPTBf7_"
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 6 
#define relais 3
#define pot 0    
#define DHTTYPE DHT11 
DHT_Unified dht(DHTPIN, DHTTYPE);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "KamerGlenn";
char pass[] = "GlennIsCool";
float temphulp =0;
float val = 0;
int waarde =0; 

BLYNK_WRITE(V3)
{

    int pinValue = param.asInt();
    int waarde = pinValue;
   
}


void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  lcd.begin();
  lcd.clear();
  lcd.setBacklight(HIGH);
  pinMode(pot,INPUT);
  pinMode(relais,OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() 
{
  val = analogRead(pot);
  val = map(val, 0, 1023, 0, 31);
  lcd.setCursor(0,0);
  lcd.print("Gew.");
  lcd.setCursor(5,0);
  lcd.print(val);
  Blynk.virtualWrite(V2, val);

 
   // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    if(event.temperature > temphulp){
     temphulp = event.temperature;  
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    lcd.setCursor(0,1);
    lcd.print("Temp.");
    lcd.setCursor(5,1);
    lcd.print(event.temperature);
    Blynk.virtualWrite(V1, event.temperature);
  
  }
  }
  
  if(event.temperature > val)
  {
    digitalWrite(relais, LOW);
    lcd.setCursor(11,0);
    lcd.print("POMP");
    lcd.setCursor(11,1);
    lcd.print("UIT");
    
  }
    if(event.temperature <= val)
  {
     digitalWrite(relais, HIGH);
     lcd.setCursor(11,0);
     lcd.print("POMP");
     lcd.setCursor(11,1);
     lcd.print("AAN");
  }
   
}
