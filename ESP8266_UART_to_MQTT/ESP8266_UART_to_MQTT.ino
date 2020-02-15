/*
 * ESP8266 UART-->WiFi(MQTT) Converter
 *
 * TX of Serial1 for ESP8266 is GPIO2
 *
 * ESP8266 serial is SWAP.
 * TXD2 of ESP8266 is GPIO15
 * RXD2 of ESP8266 is GPIO13
 *
 * ESP8266           UNO
 * GPIO15(TXD)   --- RX
 * GPIO13(RXD)   --- TX
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient

#define MQTT_SERVER     "192.168.10.40"   // You can change
#define MQTT_PORT       1883
#define MQTT_WILL_TOPIC "atmega328"       // You can change
#define MQTT_TOPIC      "atmega328"       // You can change
#define MQTT_WILL_MSG   "I am leaving..." // You can change
#define UART_BAUDRATE   115200            // You can change
#define RXBUFFERSIZE    1024

const char* ssid = "SSID of Your AP";
const char* password = "PASSWORD of Your AP";

WiFiClient espClient;
PubSubClient client(espClient);

#define bufferSize 8192
char buf[bufferSize];
uint8_t iofs=0;

#define RXBUFFERSIZE 1024
#define UART_BAUDRATE 115200  // You can change

 errorDisplay(char* buff) {
  Serial1.print("Error:");
  Serial1.println(buff);
  for (int i=0;i<10;i++) {
    delay(1000);
  }
  ESP.restart();
}

void setup()
{
  delay(1000);
  Serial1.begin(115200); // for DEBUG
  Serial.begin(UART_BAUDRATE);
  // Allow to define the receiving buffer depth.
  // The default value is 256.
  Serial.setRxBufferSize(RXBUFFERSIZE);
  // Hardware serial is now on RX:GPIO13 TX:GPIO15
  Serial.swap();

  // Connect Wifi
  Serial1.println();
  Serial1.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial1.print(".");
  }
  Serial1.println("WiFi connected");
  Serial1.print("IP address: ");
  Serial1.println(WiFi.localIP());
  Serial1.print("subnetMask: ");
  Serial1.println(WiFi.subnetMask());
  Serial1.print("gatewayIP: ");
  Serial1.println(WiFi.gatewayIP());

  // Connect MQTT
  client.setServer(MQTT_SERVER, MQTT_PORT);
  char clientid[20];
  sprintf(clientid,"ESP8266-%06x",ESP.getChipId());
  Serial1.print("clientid=");
  Serial1.println(clientid);
  Serial1.print("Attempting MQTT connection...");

  // Attempt to connect
  if (strlen(MQTT_WILL_MSG)) {
    if (!client.connect(clientid, MQTT_WILL_TOPIC, 0, 0, MQTT_WILL_MSG)) {
      errorDisplay("connect Fail");
    }
  } else {
    if (!client.connect(clientid)) {
      errorDisplay("connect Fail");
    }
  }
  Serial1.println("connected");
  Serial1.print("Waiting for input from UART at ");
  Serial1.print(UART_BAUDRATE);
  Serial1.println("bps"); 
}


void loop()
{
  static int term = 0;

  if (!client.connected()) {
    errorDisplay("not connect");
  }
  client.loop();
  if(Serial.available()) {
    char ch = Serial.read(); // read char from UART
    //Serial1.print("ch=0x");
    //Serial1.println(ch,HEX);
    if (ch == 0x0d) {

    } else if (ch == 0x0a) {
      Serial1.println();
      Serial1.print("Publish to ");
      Serial1.println(MQTT_SERVER);
      if (!client.publish(MQTT_TOPIC, buf)) {
        errorDisplay("publish fail");
      }
      iofs = 0;
    } else {
      buf[iofs] = ch;
      buf[iofs+1] = 0;
      Serial1.print(buf[iofs]);
      if(iofs<bufferSize-1) iofs++;
    }
  }
} 
