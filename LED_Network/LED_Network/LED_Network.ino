#include <AntoIO.h>

// username of anto.io account
const char *user = "sopon";

// key of permission, generated on control panel anto.io
const char* key = "DBaSjOTCUrfQDTGsUZFfGHIcMjcJeTfbwJwVGEF4";

// your default thing.
const char* thing = "NodeMCUv2_Anto_LED";

// create AntoIO object named anto.
// using constructor AntoIO(user, key, thing)
// or use AntoIO(user, key, thing, clientId)
// to generate client_id yourself.
AntoIO anto(user, key, thing);

bool bIsConnected = false;

int Led1,Led2,Led3,Led4 = 0;
int value = 0;


void setup() {
    // SSID and Password of your WiFi access point.
    const char* ssid = "@met";
    const char* pwd  = "";
  
    Serial.begin(74880);
    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Anto library version: ");
    Serial.println(anto.getVersion());


    // Connect to your WiFi access point
    if (!anto.begin(ssid, pwd)) {
        Serial.println("Connection failed!!");

        // Stop everything.
        while (1);
    }

    Serial.println();
    Serial.println("WiFi connected");  
    Serial.println("Connecting to MQTT broker");
    
    // register callback functions
    anto.mqtt.onConnected(connectedCB);
    anto.mqtt.onDisconnected(disconnectedCB);
    anto.mqtt.onData(dataCB);
    anto.mqtt.onPublished(publishedCB);
    
    // Connect to Anto.io MQTT broker
    anto.mqtt.connect();

    //port output
    pinMode(D1,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D3,OUTPUT);
    pinMode(D4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

/*
* connectedCB(): a callback function called when the connection to the MQTT broker is establised.
*/
void connectedCB()
{   
    // If the connection is establised, subscribe channels.

    bIsConnected = true;
    Serial.println("Connected to MQTT Broker");
    
    anto.sub("LED1");
    anto.sub("LED2");
    anto.sub("LED3");
    anto.sub("LED4");
}

/*
* disconnectedCB(): a callback function called when the connection to the MQTT broker is broken.
*/
void disconnectedCB()
{   
    bIsConnected = false;
    Serial.println("Disconnected to MQTT Broker");
}

/*
* msgArrvCB(): a callback function called when there a message from the subscribed channel.
*/
void dataCB(String& topic, String& msg)
{
    uint8_t index = topic.indexOf('/');

    index = topic.indexOf('/', index + 1);
    index = topic.indexOf('/', index + 1);

    topic.remove(0, index + 1);
   
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(msg);

    if(topic.equals("LED1")){
      value = msg.toInt();
      if(value == 1){
        digitalWrite(D1,HIGH);
      }
      else{
        digitalWrite(D1,LOW);
      }
      
    }
    else if(topic.equals("LED2")){
     value = msg.toInt();
     if(value == 1){
        digitalWrite(D2,HIGH);
      }
      else{
        digitalWrite(D2,LOW);
      }
    }
    else if(topic.equals("LED3")){
      value = msg.toInt();
      if(value == 1){
        digitalWrite(D3,HIGH);
      }
      else{
        digitalWrite(D3,LOW);
      }
    }
     else if(topic.equals("LED4")){
      value = msg.toInt();
      if(value == 1){
        digitalWrite(D4,HIGH);
      }
      else{
        digitalWrite(D4,LOW);
      }
    }
}

/*
* publishedCB(): a callback function called when the message is published.
*/
void publishedCB(void)
{
    Serial.println("published");
}




