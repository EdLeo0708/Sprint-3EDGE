# Sprint-3EDGE

*Visão Geral da Solução*

  Este projeto utiliza o microcontrolador ESP32 em conjunto com o sensor DHT22 (temperatura e umidade) e comunicação MQTT para criar um sistema de automação e monitoramento ambiental em salas do hospital. A solução visa monitorar continuamente as condições ambientais e realizar avisos se os numeros estiverem muito altos e baixos, para manter o ambiente dentro de parâmetros ideais de cada sala hospitalar.


*Requisitos*

 • Hardware: ESP32, sensor DHT22, módulo Wi-Fi.
 
 • Software: Arduino IDE (ou outro ambiente de programação para ESP32).


*Configuração do Hardware*

 • Conecte o sensor DHT22 ao pino definido (por exemplo, pino 15) no ESP32.
 
 • Conecte o ESP32 ao módulo Wi-Fi para comunicação com a rede local.


*Configuração do Software*

1. Instale as bibliotecas necessárias:
   
 • WiFi.h: Para comunicação Wi-Fi.
 
 • PubSubClient.h: Para comunicação MQTT.
 
 • DHTesp.h: Para o sensor DHT22.
 

2. Abra o arquivo ESP32_MQTT_DHT22.ino no ambiente de programação (Arduino IDE, por exemplo).


3. Configure as seguintes variáveis no código:

 • DHT_PIN: Pino ao qual o sensor DHT22 está conectado.

 • ssid: Nome da rede Wi-Fi.
 
 • password: Senha da rede Wi-Fi.
 
 • mqtt_server: URL do servidor MQTT.


 *Execução da Aplicação*
 
 • Compile e faça o upload do código para o ESP32.
 
 • Abra o monitor serial para visualizar os dados de temperatura e umidade.
 
 • Conecte-se ao servidor MQTT para receber e publicar mensagens.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Link wokwi: https://wokwi.com/projects/393804794889664513


Integrantes:


1. Eduardo Mazelli - 553236


2. Nathan Uflacker - 552264


3. Beatriz Silva – 5534552


4. Carolina Machado – 5529253


5. Edson Leonardo - 553737



