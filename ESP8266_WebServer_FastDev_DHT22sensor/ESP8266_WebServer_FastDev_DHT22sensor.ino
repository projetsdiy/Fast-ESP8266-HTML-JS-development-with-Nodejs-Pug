#include <ESP8266WebServer.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <FS.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ArduinoJson.h>

#define ssid      "XXXX"      // WiFi SSID
#define password  "xxxx"      // WiFi password
#define DHTTYPE   DHT22       // DHT type (DHT11, DHT22)
#define DHTPIN    D4          // Broche du DHT / DHT Pin
const uint8_t GPIOPIN[4] = {D5,D6,D7,D8};  // Led
float   t = 0 ;
float   h = 0 ;
float   pa = 0;
int     sizeHist = 100;        // Nombre de points dans l'historique - History size

unsigned long previousMillis = 0;  // Dernier point enregistré dans l'historique - time of last point added
const long intervalHist = 5000;    // Durée entre deux points dans l'historique

// Création des objets / create Objects
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
ESP8266WebServer server ( 80 );

StaticJsonBuffer<10000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
JsonArray& timestamp = root.createNestedArray("timestamp");
JsonArray& hist_t = root.createNestedArray("t");
JsonArray& hist_h = root.createNestedArray("h");
JsonArray& hist_pa = root.createNestedArray("pa");
 
void updateGpio(){
  String gpio = server.arg("id");
  String etat = server.arg("etat");
  String success = "1";
  int pin = D5;
 if ( gpio == "D5" ) {
      pin = D5;
 } else if ( gpio == "D7" ) {
     pin = D7;
 } else if ( gpio == "D8" ) {
     pin = D8;  
 } else {   
      pin = D5;
  }
  Serial.println(pin);
  if ( etat == "1" ) {
    digitalWrite(pin, HIGH);
  } else if ( etat == "0" ) {
    digitalWrite(pin, LOW);
  } else {
    success = "1";
    Serial.println("Err Led Value");
  }
  
  String json = "{\"gpio\":\"" + String(gpio) + "\",";
  json += "\"etat\":\"" + String(etat) + "\",";
  json += "\"success\":\"" + String(success) + "\"}";
    
  server.send(200, "application/json", json);
  Serial.println("GPIO mis a jour");
}

void sendMesures() {
  String json = "{\"t\":\"" + String(t) + "\",";
  json += "\"h\":\"" + String(h) + "\",";
  json += "\"pa\":\"" + String(pa) + "\"}";

  server.send(200, "application/json", json);
  Serial.println("Mesures envoyees");
}

void sendTabMesures() {
  double temp = root["t"][0];      // Récupère la plus ancienne mesure (temperature) - get oldest record (temperature)
  String json = "[";
  json += "{\"mesure\":\"Température\",\"valeur\":\"" + String(t) + "\",\"unite\":\"°C\",\"glyph\":\"glyphicon-indent-left\",\"precedente\":\"" + String(temp) + "\"},";
  temp = root["h"][0];             // Récupère la plus ancienne mesure (humidite) - get oldest record (humidity)
  json += "{\"mesure\":\"Humidité\",\"valeur\":\"" + String(h) + "\",\"unite\":\"%\",\"glyph\":\"glyphicon-tint\",\"precedente\":\"" + String(temp) + "\"},";
  temp = root["pa"][0];             // Récupère la plus ancienne mesure (pression atmospherique) - get oldest record (Atmospheric Pressure)
  json += "{\"mesure\":\"Pression Atmosphérique\",\"valeur\":\"" + String(pa) + "\",\"unite\":\"mbar\",\"glyph\":\"glyphicon-dashboard\",\"precedente\":\"" + String(temp) + "\"}";
  json += "]";
  server.send(200, "application/json", json);
  Serial.println("Tableau mesures envoyees");
}

void sendHistory(){
  
  char json[10000];
  root.printTo(json, sizeof(json));

  //Serial.println(buffer);
  //String json = "{\"data\":\"[" + String(temp) +  

  
  /*
  String json = "{\"datasets\":[{";
  json += "\"label\":\"Historique de Température\",";
  json += "\"data\":[";
            for ( int j=0; j <= 100 ; j++ ){
              temp = root["timestamp"][j];
              json += "{\"x\":\"" + String(temp) +"\",";
              temp = root["t"][j];
              json += "\"y\":\"" + String(temp) +"\"}";
              if ( j < 100 ) {
                json += ",";
              }
            }
  json += "]";
  json += "}]}";
  */

  server.send(200, "application/json", json);
  Serial.println("data graph temp envoyees");
}

void getNtpTime() {
  static int i = 0;
  static int last = 0;

    if ((millis() - last) > 5100) {
        Serial.print(NTP.getTime()); ; Serial.print(" | ");
        
        last = millis();
        Serial.println(NTP.getTimeDateString(NTP.getFirstSync()).c_str());

        //i++;
    }
    delay(0);  
}

void setup() {
  NTP.onNTPSyncEvent([](NTPSyncEvent_t error) {
        if (error) {
            Serial.print("Time Sync error: ");
            if (error == noResponse)
                Serial.println("NTP server not reachable");
            else if (error == invalidAddress)
                Serial.println("Invalid NTP server address");
        }
        else {
            Serial.print("Got NTP time: ");
            Serial.println(NTP.getTimeDateString(NTP.getLastNTPSync()));
        }
    });
  NTP.begin("pool.ntp.org", 1, true);
  NTP.setInterval(1800);
  delay(1000);
    
  for ( int x = 0 ; x < 5 ; x++ ) {
    pinMode(GPIOPIN[x], OUTPUT);
  }
  
  Serial.begin ( 115200 );
  // Initialisation du BMP180 / Init BMP180
  if ( !bmp.begin() ) {
    Serial.println("BMP180 KO!");
    while (1);
  } else {
    Serial.println("BMP180 OK");
  }

  WiFi.begin ( ssid, password );
  // Attente de la connexion au réseau WiFi / Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 ); Serial.print ( "." );
  }
  // Connexion WiFi établie / WiFi connexion is OK
  Serial.println ( "" );
  Serial.print ( "Connected to " ); Serial.println ( ssid );
  Serial.print ( "IP address: " ); Serial.println ( WiFi.localIP() );

  if (!SPIFFS.begin())
  {
    // Serious problem
    Serial.println("SPIFFS Mount failed");
  } else {

    Serial.println("SPIFFS Mount succesfull");
  }

  server.on("/tabmesures.json", sendTabMesures);
  server.on("/mesures.json", sendMesures);
  server.on("/gpio", updateGpio);
  server.on("/graph_temp.json", sendHistory);

  server.serveStatic("/js", SPIFFS, "/js");
  server.serveStatic("/css", SPIFFS, "/css");
  server.serveStatic("/img", SPIFFS, "/img");
  server.serveStatic("/", SPIFFS, "/index.html");

  server.begin();
  Serial.println ( "HTTP server started" );

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  t = dht.readTemperature();
  h = dht.readHumidity();
  pa = bmp.readPressure() / 100.0F;
  addPtToHist();
  delay(100);
}

void addPtToHist(){
  unsigned long currentMillis = millis();

  if ( currentMillis - previousMillis > intervalHist ) {
     previousMillis = currentMillis;
     timestamp.add(NTP.getTimeStr());
     hist_t.add(double_with_n_digits(t, 1));
     hist_h.add(double_with_n_digits(h, 1));
     hist_pa.add(double_with_n_digits(pa, 1));
     //Serial.println(hist_t.size());
     //root.printTo(Serial);
     if ( timestamp.size() > sizeHist ) {
      //Serial.println("erase old values");
      timestamp.removeAt(0);
      hist_t.removeAt(0);
      hist_h.removeAt(0);
      hist_pa.removeAt(0);
     }
  }
}
