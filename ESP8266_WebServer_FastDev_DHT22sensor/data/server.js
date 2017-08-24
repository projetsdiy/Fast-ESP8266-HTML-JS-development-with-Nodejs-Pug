/*
*   Serveur de développement rapide pour projets ESP8266
*   Fast development Server for ESP8266 projects
*   http://www.projetsdiy.fr - 2017
*/
var express = require('express');
var request = require('request');

// Fichiers publics (css, img) - Public files
var app = express();
var baseUrl = "http://192.168.1.21";

// Pages HTML créées directement à partir des temmplates Pug - Create HTML page directly form Pug templates
app.set('views', './views');
app.set('view engine', 'pug');

app.use(express.static('public'));
app.use('/static', express.static(__dirname + '/public'));

app.get('/', function(req, res) {
  res.render('index')
});

app.use('/mesures.json', function (req, res, next) {
  request({url: baseUrl + '/mesures.json',timeout:2000}, function (error, response, body) {
    if (!error && response.statusCode == 200) {
      console.log("Mesures receptionnées depuis ESP8666" + body) 
      res.send(body);
    } else {
      console.log("ESP8666 muet, envoi du jeu de données test")
      res.send({"t":"21.70","h":"29.50","pa":"984.43"});
    }
  })
});

app.use('/tabmesures.json', function (req, res, next) {
  request({url: baseUrl + '/tabmesures.json',timeout:2000}, function (error, response, body) {
    if (!error && response.statusCode == 200) {
      console.log("tabmesures receptionnées depuis l'ESP8666" + body) 
      res.send(body);
    } else {
      console.log("ESP8666 muet, envoi du jeu de données test")
      res.send([{"mesure":"Température","valeur":"21.60","unite":"°C","glyph":"glyphicon-indent-left","precedente":"19.80"},{"mesure":"Humidité","valeur":"29.80","unite":"%","glyph":"glyphicon-tint","precedente":"30.40"},{"mesure":"Pression Atmosphérique","valeur":"984.51","unite":"mbar","glyph":"glyphicon-dashboard","precedente":"984.74"}]);
    }
  })
});

app.use('/graph_temp.json', function (req, res, next) {
  request({url: baseUrl + '/graph_temp.json',timeout:2000}, function (error, response, body) {
    if (!error && response.statusCode == 200) {
      console.log("Graph receptionnées depuis l'ESP8666" + body) // Show the HTML for the Google homepage.
      res.send(body);
    } else {
      console.log("ESP8666 muet, envoi du jeu de données test")
      res.send({"timestamp":[1485273937,1485273938,1485273939,1485273940,1485273941,1485273942,1485273943,1485273944,1485273945,1485273946,1485273947,1485273948,1485273949,1485273950],"t":[23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3],"h":[35.6,35.6,35.6,35.6,35.6,35.5,35.5,35.4,35.4,35.5,35.5,35.5,35.5,35.5],"pa":[987.7,987.7,987.7,987.8,987.7,987.7,987.7,987.7,987.7,987.8,987.7,987.7,987.7,987.7],"bart":[23.30,23.30,23.30,23.30,23.30,23.30,23.30],"barh":[35.60,35.60,35.50,35.40,35.50,35.50,35.50]});
    }
  })
});

app.use('/gpio', function (req, res, next) {
	var options = {
      url: baseUrl + "/gpio",
      method: 'GET',
      headers: {
    	  'User-Agent':       'Super Agent/0.0.1',
    	  'Content-Type':     'application/x-www-form-urlencoded'
	    },
      qs: {'id': req.param('id'), 'etat': req.param('etat')},
      timeout:2000
    }

	//_url = baseUrl + "/gpio&id=" + req.param('id') + "&etat="+ req.param('etat');
	//console.log(_url);
	request(options, function (error, response, body) {
    if (!error && response.statusCode == 200) {  
      console.log("Retour GPIO ESP8266 : " + body);
      res.send(body);
    } else {
      console.log("ESP8666 muet, envoi du jeu de données test")
      res.send({id:req.param('id'), etat: req.param('etat'), success:1});
    }  
	});
})

app.listen(8080);




