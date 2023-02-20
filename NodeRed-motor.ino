// ข้อแนะนำการใช้งาน dht11
// S ต่อกับ IO32
// - ต่อกับ GND
// ตรงกลาง ต่อกับ 3v3


#include <WiFi.h>
#include <PubSubClient.h>
int enableA = 23; //motor A
int pinA1 = 19;
int pinA2 = 18;
int enableB = 5;  //motor B
int pinB1 = 26;
int pinB2 = 25;

int running = 10000;
boolean play;

// Update these with values suitable for your network.

const char* ssid = "UMR-LAB_2";
const char* password = "Ubon2565";
const char* mqtt_server = "192.168.1.202";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msgTemp;
  String top = String(topic);  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msgTemp +=(char)payload[i];
  }
  Serial.println();
  Serial.println(topic);
  Serial.println(msgTemp);
  if(top== "/forward"){
     Serial.println("xxx");    
     if(msgTemp == "on"){
      digitalWrite(enableA, HIGH);
      digitalWrite(pinA1, HIGH);
      digitalWrite(pinA2, LOW);
      digitalWrite(enableB, HIGH);
      digitalWrite(pinB1, HIGH);
      digitalWrite(pinB2, LOW);       
    } 
     if(msgTemp == "off"){
      digitalWrite(enableA, LOW);
      digitalWrite(pinA1, LOW);
      digitalWrite(pinA2, LOW);
      digitalWrite(enableB, LOW);
      digitalWrite(pinB1, LOW);
      digitalWrite(pinB2, LOW);       
    }     
  } 
  else if(top == "/backward"){
     if(msgTemp == "on"){
      digitalWrite(enableA, HIGH);
      digitalWrite(pinA2, HIGH);
      digitalWrite(pinA1, LOW);
      digitalWrite(enableB, HIGH);
      digitalWrite(pinB2, HIGH);
      digitalWrite(pinB1, LOW);
      delay(1000);       
    } 
     if(msgTemp == "off"){
      digitalWrite(enableA, LOW);
      digitalWrite(pinA1, LOW);
      digitalWrite(pinA2, LOW);
      digitalWrite(enableB, LOW);
      digitalWrite(pinB1, LOW);
      digitalWrite(pinB2, LOW);       
    }     
  }   
  else if(top == "/left"){
     if(msgTemp == "on"){
      digitalWrite(enableA, HIGH);
      digitalWrite(pinA1, HIGH);
      digitalWrite(pinA2, LOW);
      digitalWrite(enableB, LOW);
      delay(1000); 
    } 
     if(msgTemp == "off"){
      digitalWrite(enableA, LOW);
      digitalWrite(pinA1, LOW);
      digitalWrite(pinA2, LOW);
      digitalWrite(enableB, LOW);
      digitalWrite(pinB1, LOW);
      digitalWrite(pinB2, LOW);       
    }     
  }
  else if(top == "/right"){
     if(msgTemp == "on"){
      digitalWrite(enableB, HIGH);
      digitalWrite(pinB1, HIGH);
      digitalWrite(pinB2, LOW);
      digitalWrite(enableA, LOW);
      delay(1000);  
    } 
     if(msgTemp == "off"){
      digitalWrite(enableA, LOW);
      digitalWrite(pinA1, LOW);
      digitalWrite(pinA2, LOW);
      digitalWrite(enableB, LOW);
      digitalWrite(pinB1, LOW);
      digitalWrite(pinB2, LOW);       
    }     
  }   
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("/forward");
      client.subscribe("/backward");
      client.subscribe("/left");
      client.subscribe("/right");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);       
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
