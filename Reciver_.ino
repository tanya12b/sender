
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
//Based on MY board,I include the relevant Wi-Fi library.

//Deactivate your Wi-Fi login information

char ssid[] = "Galaxy M1149781";    
char pass[] = "987654321";   

int light = 6;

//Initialise the MQTT and Wi-Fi clients.

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "broker.mqttdashboard.com";
int        port     = 1883;
const char topic[]  = "bawana ";

void setup() {
  // Setup serial communication initially for debugging

  Serial.begin(9600);
  // Create an output on the LED pin.

  pinMode(light, OUTPUT);
  // Only necessary for native USB ports, wait for the serial port to open.

  while (!Serial) {
    ;
  }

// Join the wireless network

  Serial.print(" Connecting to a WPA SSID attempt: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    
    Serial.print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    delay(2000);
  }

  Serial.println("You are linked to the internet");
  Serial.println();

  
//Join the MQTT broker here:

  Serial.print("Connection attempts to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("Connection to MQTT was lost! error number  ");
    Serial.println(mqttClient.connectError());
// Stop the programme if the MQTT connection fails.

    while (1);
  }

  Serial.println("You are now linked to the MQTT broker.");
  Serial.println();
// Join a particular MQTT topic.

  Serial.print("topic subscription ");
  Serial.println(topic);
  Serial.println();

  mqttClient.subscribe(topic);


  Serial.print("awaiting replies on the subject");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
  // The MQTT broker sent a message to us.
    Serial.print(" gotten a message with the subject");
    Serial.print(mqttClient.messageTopic());
    Serial.print("' size: ");
    Serial.print(messageSize);
    Serial.println("byte:");
// Print the text of the message
    while (mqttClient.available()) {
      Serial.print((char)mqttClient.read());
    }
     Serial.println();
    // Blink the LED to indicate message receptio
   // Led is going tp blink three times
    digitalWrite(light, HIGH);   
    delay(350);                       
    digitalWrite(light, LOW);    
    delay(350);
    digitalWrite(light, HIGH);   
    delay(350);                       
    digitalWrite(light, LOW);    
    delay(350);
    digitalWrite(light, HIGH);   
    delay(350);                       
    digitalWrite(light, LOW);    
    delay(350);

    Serial.println();
  }
}