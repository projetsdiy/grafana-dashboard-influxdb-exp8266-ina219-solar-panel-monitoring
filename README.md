# How to create a Grafana Dashboard to monitor Solar Panel power for DIY IoT

The measurements (current, voltage, power, sunshine) are carried out using the [INA219](http://bit.ly/2LDbUM) circuit using an ESP8266. Measurements transmitted in WiFi are stored in an InfluxDB database. You can monitor up to 4 solar panels (up to 26V - 3.2A). 

Convenient to check if the size, orientation, inclination is sufficient to recharge a battery (LiPo, Li - Ion).

[More details on the blog](http://bit.ly/2sL4os4)

Connection to InfluxDB database based on [Francesco d'Aloisio's project](https://github.com/fradaloisio/ESP8266-Sensors-InfluxDB)

## Material needed
For power measurement of solar panels
* [ESP8266 (recommended Wemos d1 mini v3)](http://bit.ly/2sYbfgT)
* [1x to 4x INA219 (preferably GY-219)](http://bit.ly/2LDbUM)
* [1x BH1750 (optional)](http://bit.ly/2JApQ9w)
* [1x to 4x mini solar panels (max voltage 26V)](http://bit.ly/2HDPrwk)
* [Breadboard + jumper (seamless)](http://bit.ly/2Mgxl76)
* [or perforated plate](http://bit.ly/2JIJ6EY)

For the server
* [Raspberry Pi 3:](https://amzn.to/2y6QmWu)
* [Micro SD card (16GB recommended, class 10)](https://amzn.to/2Me4xw1)
* [5V power supply (3000mA recommended)](https://amzn.to/2sW1lMU)

## Some tutorials to start
* [Install and configure InfluxDB on a Raspberry Pi](https://diyprojects.io/influxdb-part-1-installation-on-macos-methods-shell)
* [Install and start with Grafana on Raspberry Pi](https://diyprojects.io/grafana-installation-macos-influxdb-charts-mysensors-iot/)
* [Measurement of luminosity using a BH1750](https://diyprojects.io/bh1750-gy-302-measure-lighting-quality-home-arduino-esp8266-esp32)
* [Measurement of power (current, voltage) with the INA219](https://projetsdiy.fr/capteur-ina219-measure-power-of-a-school-solar-battery-arduino-esp8266/)

InfluxDB and Grafana also work on Windows

# Comment créer un Dashboard Grafana pour surveiller l'alimentation en énergie panneau solaire pour objets connectés DIY
Les mesures (courant, tension, puissance, ensoleillement) sont réalisées à l'aide du circuit [INA219](http://bit.ly/2LDbUM) à l'aide d'un ESP8266. Les mesures transmises en WiFi sont enregistrées dans une base de données InfluxDB. Vous pourrez surveiller jusqu'à 4 panneaux solaires (jusqu'à 26V - 3.2A). 

Pratique pour vérifier si la taille, l'orientation, l'inclinaison est suffisante pour recharger une batterie (LiPo, Li - Ion).

Plus de détails sur [l'article du blog](https://projetsdiy.fr/dashboard-grafana-monitoring-panneau-solaire-wifi-esp8266-puissance-objets-connectes-diy/)

Connexion à InfluxDB depuis un ESP8266 basé sur la librairie de [Francesco d'Aloisio](https://github.com/fradaloisio/ESP8266-Sensors-InfluxDB)

## Matériel nécessaire
Pour la mesure de puissance des panneaux solaires
* [ESP8266 (Wemos d1 mini v3 conseillée)](http://bit.ly/2sYbfgT)
* [1x à 4x INA219 (de préférence GY-219)](http://bit.ly/2LDbUMq)
* [1x BH1750 (optional)](http://bit.ly/2JApQ9w)
* [1x à 4x mini panneaux solaire (tension max. 26V)](http://bit.ly/2HDPrwk)
* [Breadboard + jumper (sans soudure)](http://bit.ly/2Mgxl76)
* [ou plaque perforée](http://bit.ly/2JIJ6EY)

Pour le serveur 
* [Raspberry Pi 3](https://amzn.to/2l3663O)
* [Carte micro SD (16Go conseillée, classe 10)](https://amzn.to/2xZPB1E)
* [Alimentation 5V (3000mA conseillé)](https://amzn.to/2l34eYP)

## Installer et configurer InfluxDB et Grafana 
Suivez ces tutoriels pour installer et configurer InfluxDB et Grafana sur un Raspberry Pi 3. 
* [Débuter avec le Raspbian et le Raspberry PI 3](https://projetsdiy.fr/decouverte-test-configuration-raspberry-pi-3/)
* [Installer et configurer InfluxDB sur un Raspberry PI](https://projetsdiy.fr/tutoriel-influxdb-installation-configuration-macos/)
* [Installer et débuter avec Grafana sur Raspberry PI](https://projetsdiy.fr/grafana-graphiques-installation-macos-mysensors-influxdb-partie1/)
* [Mesure de luminosité à l'aide d'un BH1750](https://projetsdiy.fr/bh1750-gy-302-mesure-qualite-eclairage-habitation-arduino-esp8266-esp32/)
* [Mesure de puissance (courant, tension) avec l'INA219](https://projetsdiy.fr/capteur-ina219-mesurer-puissance-dun-panneau-solaire-batterie-arduino-esp8266/)

InfluxDB et Grafana fonctionnent également sur Windows

![alt text](https://projetsdiy.fr/wp-content/uploads/2018/06/grafana-dashboard-esp8266-influxdb-ina218-solar-panel.png)
