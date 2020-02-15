# esp8266_mqtt_uart_bridge
esp8266 mqtt uart bridge.


# MQTT to UART

![esp8266_mqtt_to_uart](https://user-images.githubusercontent.com/6020549/74579213-5246ea00-4fdc-11ea-94cf-10b20d2a71ac.jpg)

## Environment
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
- const char* ssid = "SSID of Your AP";
SSID of your Access Point
- const char* password = "PASSWORD of Your AP";
Password of your Access Point

## Connection
ESP8266 serial is SWAP.   
TXD2 of ESP8266 is GPIO15.   
RXD2 of ESP8266 is GPIO13.   

```
 * ESP8266           UNO
 * GPIO15(TXD)   --- RX
 * GPIO13(RXD)   --- TX
```

# UART to MQTT

![esp8266_uart_to_mqtt](https://user-images.githubusercontent.com/6020549/74579216-55da7100-4fdc-11ea-9b3b-a6f54c6f8bab.jpg)


