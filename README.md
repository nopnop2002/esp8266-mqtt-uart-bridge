# esp8266_mqtt_uart_bridge
esp8266 mqtt uart bridge.

- Convert from UART output to MQTT publish.   

- Convert from MQTT subscribe to UART input.   


# Monitoring
You can monitor ESP8266 using Serial1.   
Serial1 outputs to GPIO2

# How to disable ESP8266 boot messages
ESP8266 boot rom writes a log to the UART when booting like this:
```
ets Jan  8 2014,rst cause 1, boot mode:(3,7)

load 0x40100000, len 24236, room 16
tail 12
chksum 0xb7
ho 0 tail 12 room 4
load 0x3ffe8000, len 3008, room 12
tail 4
chksum 0x2c
load 0x3ffe8bc0, len 4816, room 4
tail 12
chksum 0x46
csum 0x46
```
This message can cause unexpected trouble.   

## Swap UART
UART can be swapped by adding the following one line:
```
Serial.swap();   
```
TX / RX changes to the following when UART is swapped.
```
GPIO15(TXD)   --- RX
GPIO13(RXD)   --- TX
```
The boot message does not reach RX port of other side.   
However, since GPIO15 is a pin that determines the boot mode, ESP8266 does not start.   
__This method cannot be used.__   

## Add a circuit
If the following circuit is added, All message does not reach RX port of other side.   
I used 1N5819 Schottky Barrier Plastic Rectifier.   

![UART_BOOT_MESSAGE](https://user-images.githubusercontent.com/6020549/74654209-28084e80-51cd-11ea-8af5-d0c03551a484.jpg)

To start transmission, set the GPIO polarity to OUTPUT and the level to LOW.   

```
pinMode(GPIO, OUTPUT);
digitalWrite(GPIO, LOW);
Serial.begin(115200);
```

NOTE:GPIO15 is pulled down and cannot be used for this.   


# MQTT to UART

![esp8266_mqtt_to_uart](https://user-images.githubusercontent.com/6020549/74579213-5246ea00-4fdc-11ea-94cf-10b20d2a71ac.jpg)

You need to adjust the following environment.

- #define MQTT_SERVER     "broker.emqx.io"   
IP of MQTT Broker
- #define MQTT_PORT       1883   
Port of MQTT Broker
- #define MQTT_TOPIC      "/esp-bridge"   
Subscribe topic
- #define MQTT_WILL_TOPIC "/esp-bridge"   
Will topic
- #define MQTT_WILL_MSG   "I am leaving..."   
Will message
- #define UART_BAUDRATE   115200   
UART boudrate
- const char* ssid = "SSID of Your AP";   
SSID of your Access Point
- const char* password = "PASSWORD of Your AP";   
Password of your Access Point

## Publish using mosquitto-clients
```
$ mosquitto_pub -h broker.emqx.io -p 1883 -t "/esp-bridge" -m "Hello World"
```

# UART to MQTT

![esp8266_uart_to_mqtt](https://user-images.githubusercontent.com/6020549/74579472-262c6880-4fde-11ea-9f81-ce0632e203a0.jpg)

You need to adjust the following environment.

- #define MQTT_SERVER     "broker.emqx.io"   
IP of MQTT Broker
- #define MQTT_PORT       1883   
Port of MQTT Broker
- #define MQTT_TOPIC      "/esp-bridge"   
Publish topic
- #define MQTT_WILL_TOPIC "/esp-bridge"   
Will topic
- #define MQTT_WILL_MSG   "I am leaving..."   
Will message
- #define UART_BAUDRATE   115200   
UART boudrate
- const char* ssid = "SSID of Your AP";   
SSID of your Access Point
- const char* password = "PASSWORD of Your AP";   
Password of your Access Point

## Subscribe using mosquitto-clients
```
$ mosquitto_sub -v -h broker.emqx.io -p 1883  -t "/esp-bridge"
```
