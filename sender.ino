#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
//Based on MY board,I include the relevant Wi-Fi library.

//my ssid and my password
char ssid[] = "Galaxy M114971";;    
char pass[] = "987654321";    

//Define the ultrasonic sensor pin in 
const int trigPin = 5;
//transmit tx
const int echoPin = 6;
//rx
float duration, distance;

// Setup the MQTT client and WiFi client.

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// MQTT configuration
const char broker[] = "mqtt-dashboard.com";
int        port     = 1883;
const char topic[]  = "brain";
// THE TOPIC name which i used in MQTT
const long interval = 2000;
//Sensor readings and MQTT message intervals

unsigned long previousMillis = 0;

int count = 0;
// Start serial communication from scratch
void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
// Await connection of the serial port (only for native USB ports)
 
  Serial.print("connection attempt to WPA SSID ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
   
    // Print lines while joining

    Serial.print("!!!!!!!!!!!!!!!!!!!!!!!!!!");
    delay(1000);
  }


  Serial.println("You are logged into the Internet");
  Serial.println();
// While joining, print dotted lines.


  Serial.print(" Connecting to the MQTT broker in an attempt");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("Connection to MQTT was lost! error code ");
    Serial.println(mqttClient.connectError());
//If the MQTT connection breaks, hang

    while (1);
  }

  Serial.println("You are now linked to the MQTT broker.");
  Serial.println();
}

void loop() {
 // The MQTT client is polled to check for new messages.

  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
   
    previousMillis = currentMillis;
// Start the ultrasonic sensor, then measure the distance.

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * .0343) / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance < 12)
    {
      // When a wave is found, publish a message to the MQTT topic.

      mqttClient.beginMessage(topic);
      mqttClient.print("  Tanya,  Wave detected!!!!!! ");
      mqttClient.print("Distance is -  ");
      mqttClient.print(distance);
      mqttClient.endMessage();
      delay(5000);
    }

    Serial.println();

    count++;
  }
}