/*
 * Solar Panel Power Monitoring with InfluxDB and Grafana Dashboard
 * Comparison of the power delivered by 2 mini solar panels using INA219
 * Measurement of sunshine with a BH1750
 *
 * Connection to InfluxDB database based on Francesco d'Aloisio's project
 * https://github.com/fradaloisio/ESP8266-Sensors-InfluxDB
 * 
 * Tutorials to start
 * Install and configure InfluxDB on a Raspberry Pi: https://diyprojects.io/influxdb-part-1-installation-on-macos-methods-shell
 * Install and start with Grafana on Raspberry Pi: https://diyprojects.io/grafana-installation-macos-influxdb-charts-mysensors-iot/
 * Measurement of luminosity using a BH1750: https://diyprojects.io/bh1750-gy-302-measure-lighting-quality-home-arduino-esp8266-esp32
 * Measurement of power (current, voltage) with the INA219: https://projetsdiy.fr/capteur-ina219-measure-power-of-a-school-solar-battery-arduino-esp8266/
 *
 * ------
 * 
 * Monitoring puissance panneau solaire avec un Dashboard Grafana et InfluxDB
 * Comparaison de la puissance délivrée par 2 mini panneaux solaire à l'aide d'INA219
 * Mesure d'ensoleillement avec un BH1750
 * 
 * Connection à la base InfluxDB basée sur le projet de Francesco d'Aloisio 
 * https://github.com/fradaloisio/ESP8266-Sensors-InfluxDB
 * 
 * Tutoriels pour débuter
 * Débuter avec le Raspbian et le Raspberry PI 3 : https://projetsdiy.fr/decouverte-test-configuration-raspberry-pi-3/
 * Installer et configurer InfluxDB sur un Raspberry Pi : https://projetsdiy.fr/tutoriel-influxdb-installation-configuration-macos/
 * Installer et débuter avec Grafana sur Raspberry Pi : https://projetsdiy.fr/grafana-graphiques-installation-macos-mysensors-influxdb-partie1/
 * Mesure de luminosité à l'aide d'un BH1750 : https://projetsdiy.fr/bh1750-gy-302-mesure-qualite-eclairage-habitation-arduino-esp8266-esp32/
 * Mesure de puissance (courant, tension) avec l'INA219 : https://projetsdiy.fr/capteur-ina219-mesurer-puissance-dun-panneau-solaire-batterie-arduino-esp8266/
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <BH1750.h>
#include "ESPinfluxdb.h"

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WiFiMulti.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiMulti.h>
#endif

Adafruit_INA219 ina219;
Adafruit_INA219 ina219b;
BH1750 lightMeter(0x23);


const char *INFLUXDB_HOST = "ip_influxDB";
const uint16_t INFLUXDB_PORT = 8086;

const char *DATABASE = "database_name";
const char *DB_USER = "user";
const char *DB_PASSWORD = "password";


#if defined(ESP8266)
ESP8266WiFiMulti WiFiMulti;
#elif defined(ESP32)
WiFiMulti WiFiMulti;
#endif

Influxdb influxdb(INFLUXDB_HOST, INFLUXDB_PORT);

void setup() {
        Serial.begin(115200);
        WiFiMulti.addAP("ssid", "wifi_password");
        while (WiFiMulti.run() != WL_CONNECTED) {
                delay(100);
        }
        Serial.println("Ready");
        
        ina219.begin(0x40);
        ina219b.begin(0x41);
        lightMeter.begin();

        //influxdb.opendb(DATABASE, DB_USER, DB_PASSWORD);
        // Connexion à la base InfluxDB - Connect to InfluxDB database
        while (influxdb.opendb(DATABASE, DB_USER, DB_PASSWORD)!=DB_SUCCESS) {
                Serial.println("Open database failed");
                delay(10000);
        }

}

void loop() {
  //Writing data with influxdb HTTP API: https://docs.influxdata.com/influxdb/v1.5/guides/writing_data/
  //Querying Data: https://docs.influxdata.com/influxdb/v1.5/query_language/

  // Vérifie les adresses i2C des capteurs - Check i2c sensor address 
  scani2c();
  
  float busvoltage = 0;
  float current_mA = 0;
  float busvoltageb = 0;
  float current_mAb = 0;
  uint16_t lux = 0;

  // Lecture des mesures - Read values 
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  busvoltageb = ina219b.getBusVoltage_V();
  current_mAb = ina219b.getCurrent_mA();
  lux = lightMeter.readLightLevel();

  // Affiche les mesures sur le moniteur série - Print values on console
  Serial.print(busvoltage);
  Serial.print(" V / ");
  Serial.print(current_mA);
  Serial.print(" mA - ina219b ");
  Serial.print(busvoltageb);
  Serial.print(" V / ");
  Serial.print(current_mAb);
  Serial.print(" mA - Lux ");
  Serial.println(lux);

  // Envoi la puissance 1er panneau - Send power of the 1st solar panel
  dbMeasurement row("80x55");
  row.addField("voltage", busvoltage);
  row.addField("Current", current_mA); 
  row.addField("power", busvoltage * current_mA);
  Serial.println(influxdb.write(row) == DB_SUCCESS ? " - Object write success" : " - Writing failed");

  // Envoi la puissance 2nd panneau - Send power of the 2nd solar panel
  dbMeasurement rowb("85x115");
  rowb.addField("voltage", busvoltageb);
  rowb.addField("Current", current_mAb); 
  rowb.addField("power", busvoltageb * current_mAb);
  Serial.println(influxdb.write(rowb) == DB_SUCCESS ? " - Object write success" : " - Writing failed");

  // Envoi l'ensoleillement - Send sunshine (lux)
  dbMeasurement rowlux("lux");
  rowlux.addField("lux", lux);
 Serial.println(influxdb.write(rowlux) == DB_SUCCESS ? " - Object write success" : " - Writing failed");
  
  // Vide les données - Empty field object.
  row.empty();
  rowb.empty();
  rowlux.empty();
  
  delay(5000);
        
}

void scani2c()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  //delay(5000);           // wait 5 seconds for next scan
}
