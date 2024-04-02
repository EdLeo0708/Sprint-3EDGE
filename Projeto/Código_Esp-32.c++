#include <WiFi.h>            // Inclui a biblioteca WiFi para comunicação Wi-Fi
#include <PubSubClient.h>    // Inclui a biblioteca PubSubClient para MQTT
#include <DHTesp.h>          // Inclui a biblioteca DHTesp para o sensor DHT

const int DHT_PIN = 15;      // Define o pino ao qual o sensor DHT está conectado
DHTesp dht;                  // Cria uma instância do objeto DHTesp para o sensor DHT
const char* ssid = "Wokwi-GUEST"; // Nome da rede Wi-Fi
const char* password = "";   // Senha da rede Wi-Fi
const char* mqtt_server = "test.mosquitto.org"; // URL do servidor MQTT

WiFiClient espClient;        // Cria um cliente Wi-Fi
PubSubClient client(espClient); // Cria um cliente MQTT
unsigned long lastMsg = 0;   // Variável para armazenar o tempo da última mensagem enviada
float temp = 0;              // Variável para armazenar a temperatura
float hum = 0;               // Variável para armazenar a umidade

// Função para configurar a conexão Wi-Fi

void setup_wifi() { 
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);       // Define o modo do ESP32 como estação Wi-Fi
  WiFi.begin(ssid, password); // Conecta-se à rede Wi-Fi

  while (WiFi.status() != WL_CONNECTED) { // Aguarda a conexão ser estabelecida
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());      // Inicializa a semente aleatória
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // Imprime o endereço IP atribuído ao ESP32
}

// Função de callback para receber mensagens MQTT

void callback(char* topic, byte* payload, unsigned int length) { 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) { 
    Serial.print((char)payload[i]);
  }
}

// Função para reconectar ao servidor MQTT

void reconnect() { 
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.publish("/ThinkIOT/Publish", "Welcome");
      client.subscribe("/ThinkIOT/Subscribe"); 
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(2, OUTPUT);        // Define o pino 2 como saída
  Serial.begin(115200);      // Inicializa a comunicação serial com taxa de 115200 bps
  setup_wifi();              // Configura a conexão Wi-Fi
  client.setServer(mqtt_server, 1883); // Configura o servidor MQTT
  client.setCallback(callback); // Define a função de callback MQTT
  dht.setup(DHT_PIN, DHTesp::DHT22); // Inicializa o sensor DHT
}

void loop() {
  if (!client.connected()) {
    reconnect();             // Reconecta ao servidor MQTT se a conexão não estiver ativa
  }
  client.loop();             // Mantém a comunicação MQTT ativa

  unsigned long now = millis();
  if (now - lastMsg > 2000) { // Publica os dados a cada 2 segundos
    lastMsg = now;
    TempAndHumidity  data = dht.getTempAndHumidity(); // Lê os dados do sensor DHT

    String temp = String(data.temperature, 2); // Converte a temperatura para String
    client.publish("/Thinkitive/temp", temp.c_str()); // Publica a temperatura no tópico MQTT

    String hum = String(data.humidity, 1); // Converte a umidade para String
    client.publish("/Thinkitive/hum", hum.c_str()); // Publica a umidade no tópico MQTT

    Serial.print("Temperatura: ");
    Serial.println(temp); // Imprime a temperatura no monitor serial
    Serial.print("Humidade: ");
    Serial.println(hum);  // Imprime a umidade no monitor serial
  }
}