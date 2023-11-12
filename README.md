# Projeto IrrigaJá - Controle de Irrigação Automatizado

Este projeto visa criar um sistema de controle de irrigação automatizado que utiliza a ESP32 e integra sensores para monitorar condições meteorológicas e do solo. Além disso, o projeto inclui um servidor web para configuração e controle remoto.

## Funcionalidades Principais

- Monitoramento de velocidade do vento, umidade do ar, umidade do solo e temperatura.
- Controle automático da bomba de água com base nas condições do solo e configurações do usuário.
- Configuração remota por meio de uma interface web acessível a partir de qualquer dispositivo conectado à mesma rede WiFi.

## Estrutura do Projeto

O código está organizado em módulos para facilitar a manutenção e expansão do sistema. Abaixo estão os principais módulos do projeto:

- **WiFiConfig**: Gerencia a configuração e conexão à rede WiFi.
- **MqttConfig**: Implementa a comunicação MQTT para integração com o servidor e troca de mensagens.
- **MemoryFlash**: Lida com o armazenamento e recuperação de configurações em memória flash.
- **Sensores**: Contém classes para os diversos sensores utilizados.
- **Atuadores**: Contém classes para os atuadores, como a bomba de água.
- **Sistema**: Orquestra a interação entre os diferentes módulos.

## Configuração do Ambiente de Desenvolvimento

Certifique-se de ter o ambiente de desenvolvimento Arduino IDE configurado corretamente. As bibliotecas necessárias podem ser instaladas via Gerenciador de Bibliotecas Arduino.

### Dependências

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [PubSubClient](https://pubsubclient.knolleary.net/)
- [EEPROM](https://www.arduino.cc/en/Reference/EEPROM)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [WiFi](https://www.arduino.cc/en/Reference/WiFi)
