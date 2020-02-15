# esp8266_mqtt_uart_bridge
esp8266 mqtt uart bridge.

# Connection
ESP8266 serial is SWAP.   
TXD2 of ESP8266 is GPIO15.   
RXD2 of ESP8266 is GPIO13.   

```
 * ESP8266           UNO
 * GPIO15(TXD)   --- RX
 * GPIO13(RXD)   --- TX
```

# Monitoring
You can monitor ESP8266 using Serial1.   
Serial1 outputs to GPIO2

# MQTT to UART

![esp8266_mqtt_to_uart](https://user-images.githubusercontent.com/6020549/74579213-5246ea00-4fdc-11ea-94cf-10b20d2a71ac.jpg)

You need to adjust the following environment.

- #define MQTT_SERVER     "192.168.10.40"   
IP of MQTT Broker
- #define MQTT_PORT       1883   
Port of MQTT Broker
- #define MQTT_TOPIC      "atmega328"   
Subscribe topic
- #define MQTT_WILL_TOPIC "atmega328"   
Will topic
- #define MQTT_WILL_MSG   "I am leaving..."   
Will message
- #define UART_BAUDRATE   115200   
UART boudrate
- const char* ssid = "SSID of Your AP";   
SSID of your Access Point
- const char* password = "PASSWORD of Your AP";   
Password of your Access Point


# UART to MQTT

![esp8266_uart_to_mqtt](https://user-images.githubusercontent.com/6020549/74579472-262c6880-4fde-11ea-9f81-ce0632e203a0.jpg)

You need to adjust the following environment.

- #define MQTT_SERVER     "192.168.10.40"   
IP of MQTT Broker
- #define MQTT_PORT       1883   
Port of MQTT Broker
- #define MQTT_TOPIC      "atmega328"   
Publish topic
- #define MQTT_WILL_TOPIC "atmega328"   
Will topic
- #define MQTT_WILL_MSG   "I am leaving..."   
Will message
- #define UART_BAUDRATE   115200   
UART boudrate
- const char* ssid = "SSID of Your AP";   
SSID of your Access Point
- const char* password = "PASSWORD of Your AP";   
Password of your Access Point


