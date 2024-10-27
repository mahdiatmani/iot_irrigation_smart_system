#include "arduino_secrets.h"
#include "thingProperties.h"

const int moistureSensorPin = 32;  // Changez vers une autre broche
const int relayPin = 26;           // Pin GPIO pour contrôler le relais (G26 sur l'ESP32)
int moistureLevel = 0;             // Variable pour stocker la valeur du capteur

void setup() {
  // Initialisation de la communication série
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);       // Définir la pin du relais comme sortie
  digitalWrite(relayPin, LOW);     // S'assurer que le relais est éteint au départ (pompe arrêtée)

  // Initialisation des propriétés IoT Cloud
  initProperties();

  // Synchronisation avec le cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Attente de la connexion au cloud
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  // Mise à jour des données IoT
  ArduinoCloud.update();

  // Lecture de l'humidité
  moistureLevel = analogRead(moistureSensorPin);
  
  // Conversion de la valeur du capteur en pourcentage (0 à 100)
  int moisturePercent = map(moistureLevel,4095,910, 0, 100);
  mOISTURE = moisturePercent;
  Serial.print("Humidité : ");
  Serial.print(moistureLevel);
  Serial.print(" | Pourcentage : ");
  Serial.println(moisturePercent);

  // Vérification de l'état du commutateur et de l'humidité
  if (sWITCH || moisturePercent < 50) {  // Utilisation de la variable _switch_
    Serial.println("Le commutateur est activé");
    digitalWrite(relayPin, HIGH);  // Allumer le relais (pompe activée)
    Serial.println("Pompe activée");
  } else {
    digitalWrite(relayPin, LOW);   // Éteindre le relais (pompe désactivée)
    Serial.println("Pompe désactivée");
  }

  delay(2000);  // Pause de 2 secondes avant la prochaine vérification
}
/*
  Since MOISTURE is READ_WRITE variable, onMOISTUREChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMOISTUREChange()  {
  // Add your code here to act upon MOISTURE change
}
/*
  Since SWITCH is READ_WRITE variable, onSWITCHChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSWITCHChange()  {
  // Add your code here to act upon SWITCH change
}