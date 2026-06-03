#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA";

String serverName = "https://api.uaipy.com.br/actor-data";

#define TX_BUFFER_SIZE 1024
char txPacket[TX_BUFFER_SIZE];

void setup() {
  Serial.begin(115200);

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

    // --- 1. SIMULANDO APENAS DHT E UMIDADE DO SOLO ---
    float dhtTemperature = random(200, 350) / 10.0; // Ex: 25.4
    float dhtHumidity    = random(400, 800) / 10.0; // Ex: 65.2
    float soilHumidity   = random(300, 600) / 10.0; // Ex: 45.0

    // --- 2. MONTAGEM DO JSON REDUZIDO ---
    snprintf(txPacket, TX_BUFFER_SIZE,
    "{"
      "\"serialNumber\":\"SERIAL_NUMBER\","
      "\"readings\":["
        "{\"actor_name\":\"temperature\",\"value\":%.1f,\"unit_of_measurement\":\"°C\"},"
        "{\"actor_name\":\"humidity\",\"value\":%.1f,\"unit_of_measurement\":\"%%\"},"
        "{\"actor_name\":\"soil_humidity\",\"value\":%.1f,\"unit_of_measurement\":\"%%\"}"
      "]"
    "}",
    dhtTemperature,
    dhtHumidity,
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
  }
  delay(10000); 
}
