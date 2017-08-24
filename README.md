# Fast ESP8266 webserver development (HTML + JS) with Nodejs and Pug (Old Jade)
## Equipment used
* Any ESP8266 ESP-12 module, for example <a href="http://www.banggood.com/search/esp8266-nodemcu/0-0-0-1-3-45-0-price-0-0_p-1.html?sortType=asc?p=RA18043558422201601Y" target="_blank" rel="nofollow" data-mce-href="http://www.banggood.com/search/esp8266-nodemcu/0-0-0-1-3-45-0-price-0-0_p-1.html?sortType=asc?p=RA18043558422201601Y">Wemos D1 mini</a>
* <a href="http://s.click.aliexpress.com/e/BeYvjyfim" target="_blank" rel="nofollow" data-mce-href="http://s.click.aliexpress.com/e/BeYvjyfim">DHT22</a> Temperature and humidity sensor

## Wiring
|Sensor |Pin |ESP8266 Pin|
|-------|----|----------:|
|DHT22  |VCC |5V         |
|       |GND |G          |
|       |Data|D4         |

## Project content
* Installation of Nodejs
* Installation of Pug (former Jade) to quickly write the HTML of the projects ESP8266
* Install nodemon to update server-side code every time

## Server code (Nodejs)
* Server code can be run on any machine that can run Nodejs (PC Winodws, Linux, Mac OS, Raspberry Pi, Orange Pi ...)
* Server code allows:
  
  * Responding to requests from the web interface. For example, send a test dataset
  
  * Recover the state of the GPIO
* Code Arduino / ESP8266
  
  * Web interface developed in Pug to display temperature, humidity, measurements with a graph <a href= "https://projetsdiy.fr/esp8266-web-serveur-partie5-gauges-Graphics-google-charts/">Google Chart</a>, the status of the GPIO
  
  * Storing a measurement history <a href="https://projectsdiy.fr/esp8266-webserveur-partie4-arduinojson-charger-register-files-spiffs/">in JSON format in the SPIFFS area</a>
  
  * Manages GPIO status refresh requests from the web interface or a remote server
  
  * Send measurements in the form of a JSON array (remote server request or WEB interface)
  
  * Retrieves time from an NTP time server. For more information, read <a href="https://projectsdiy.com/esp8266-web-server-partial3-time-internet-ntp-ntpclientlib/">this tutorial</a>

# Programmation web serveur rapide pour ESP8266 avec Nodejs et Pug
Le tutoriel complet ici
https://projetsdiy.fr/esp8266-web-serveur-developpement-rapide-code-htmljs-node-js-pug/
## Matériel utilisé
* N'importe quel ESP8266 (ESP-12x), par exemple <a href="http://www.banggood.com/search/esp8266-nodemcu/0-0-0-1-3-45-0-price-0-0_p-1.html?sortType=asc?p=RA18043558422201601Y" target="_blank" rel="nofollow" data-mce-href="http://www.banggood.com/search/esp8266-nodemcu/0-0-0-1-3-45-0-price-0-0_p-1.html?sortType=asc?p=RA18043558422201601Y">Wemos D1 mini</a>
* <a href="http://s.click.aliexpress.com/e/BeYvjyfim" target="_blank" rel="nofollow" data-mce-href="http://s.click.aliexpress.com/e/BeYvjyfim">DHT22</a> capteur de température et d'humitité

## Cablage
|Sensor |Broche |Broche ESP8266|
|-------|-------|-------------:|
|DHT22  |VCC    |5V            |
|       |GND    |G             |
|       |Data   |D4            |

## Contenu du projet
* Installation de Nodejs
* Installation de Pug (ancien Jade) pour écrire rapidement le code HTML du projets ESP8266
* Installation de nodemon pour actualiser le code coté serveur à chaque modification

## Code serveur (Nodejs)
* Le code serveur peut être exécuter sur n'importe quelle machine pouvant faire fonctionner Nodejs (PC Winodws, Linux, mac OS, Raspberry Pi, Orange Pi...)
* Le code serveur permet :
  
  * De réponse aux requêtes de l'interface web. Par exemple envoyer un jeu de données test
  
  * De récupérer l'état du GPIO
* Code Arduino/ESP8266
  * Interface Web développée en Pug permettant d'afficher la température, l'humidité, les mesures à l'aide d'un graphique <a href="https://projetsdiy.fr/esp8266-web-serveur-partie5-gauges-graphiques-google-charts/">Google Chart</a>, le statut du GPIO
  
  * Stockage un historique de mesure <a href="https://projetsdiy.fr/esp8266-webserveur-partie4-arduinojson-charger-enregistrer-fichiers-spiffs/">au format JSON dans la zone SPIFFS</a>
  
  * Gère les requêtes d'actualise d'état du GPIO depuis l'interface web ou un serveur distant
  
  * Envoi les mesures sous la forme d'un tableau JSON (requête serveur distant ou interface WEB)
  
  * Récupère le temps depuis un serveur de temps NTP. Pour en savoir plus, lisez <a href="https://projetsdiy.fr/esp8266-web-serveur-partie3-heure-internet-ntp-ntpclientlib/">ce tutoriel</a>
  
