# Project IrrigaJá - Automated Irrigation Control

This project aims to create an automated irrigation control system utilizing ESP32 and integrating sensors to monitor weather and soil conditions. Additionally, the project includes a web server for configuration and remote control.

## Key Features

- Monitoring wind speed, air humidity, soil moisture, and temperature.
- Automatic water pump control based on soil conditions and user settings.
- Remote configuration through a web interface accessible from any device connected to the same WiFi network.

## Project Structure

The code is organized into modules for ease of maintenance and system expansion. Below are the main modules of the project:

- **WiFiConfig**: Manages WiFi network configuration and connection.
- **MqttConfig**: Implements MQTT communication for server integration and message exchange.
- **MemoryFlash**: Handles storage and retrieval of settings in flash memory.
- **Sensors**: Contains classes for various used sensors.
- **Actuators**: Contains classes for actuators like the water pump.
- **System**: Orchestrates interaction between different modules.

## Development Environment Setup

Ensure your Arduino IDE development environment is correctly set up. Required libraries can be installed via the Arduino Library Manager.

### Dependencies

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [PubSubClient](https://pubsubclient.knolleary.net/)
- [EEPROM](https://www.arduino.cc/en/Reference/EEPROM)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [WiFi](https://www.arduino.cc/en/Reference/WiFi)
