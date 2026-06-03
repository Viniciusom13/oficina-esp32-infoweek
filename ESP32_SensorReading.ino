#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA";

// Endpoint
String serverName = "https://api.uaipy.com.br/actor-data";

// Configurações dos Pinos
#define DHTPIN 4
#define DHTTYPE DHT11
#define SOIL_PIN 34

DHT dht(DHTPIN, DHTTYPE);

#define TX_BUFFER_SIZE 1024
char txPacket[TX_BUFFER_SIZE];

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado à Internet com sucesso!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName); 
    http.addHeader("Content-Type", "application/json");

    // 1. LEITURA DOS SENSORES
    float dhtTemperature = dht.readTemperature();
    float dhtHumidity    = dht.readHumidity();

    int soilRaw = analogRead(SOIL_PIN);
    
    // Calibração: map(leitura, valor_seco, valor_molhado, 0, 100)
    float soilHumidity = map(soilRaw, 4095, 1200, 0, 100);
    
    if (soilHumidity < 0) soilHumidity = 0;
    if (soilHumidity > 100) soilHumidity = 100;

    // 2. MONTAGEM DO JSON
    snprintf(txPacket, TX_BUFFER_SIZE,
      "{"
        "\"serialNumber\":\"NUMERO DO DISPOSITIVO\","
        "\"readings\":["
          "{\"actor_name\":\"temperature\",\"value\":%.1f,\"unit_of_measurement\":\"°C\"},"
          "{\"actor_name\":\"humidity\",\"value\":%.1f,\"unit_of_measurement\":\"%%\"},"
          "{\"actor_name\":\"soil_humidity\",\"value\":%.1f,\"unit_of_measurement\":\"%%\"}"
        "]"
      "}",
      dhtTemperature = 10,
      dhtHumidity = 10,
      soilHumidity
    );

    Serial.println("\n--- Enviando POST para o servidor ---");
    Serial.println(txPacket);

    int httpResponseCode = http.POST(txPacket);

    if (httpResponseCode > 0) {
      Serial.print("Código HTTP retornado: ");
      Serial.println(httpResponseCode); 
    } else {
      Serial.print("Erro na requisição: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Erro: Wi-Fi desconectado.");
  }
  
  delay(10000); 
}
