#include <WiFi.h>
#include <HTTPClient.h>

// --- Configurações da sua Rede ---
const char* ssid = "NOME DA REDE";
const char* password = "SENHA";

/*
Será necessário adicionar a rota correta fornecida pelo backend no final da URL
(ex: mude para "https://uaipy-app-be-4ap2g.ondigitalocean.app/algumacoisa").
*/

String serverName = "https://uaipy-app-be-4ap2g.ondigitalocean.app/";

// Buffer para armazenar a string JSON que será enviada
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

    // --- 1. SIMULANDO DADOS DOS SENSORES ---
    float dhtTemperature = random(200, 350) / 10.0;
    float dhtHumidity    = random(400, 800) / 10.0;
    float shtTemperature = dhtTemperature - 2.0;
    float shtHumidity    = random(300, 600) / 10.0;
    float rainMM         = random(0, 50) / 10.0;

    // Timestamp fixo de teste
    char timestampString[] = "2026-06-01T12:00:00Z";

    // --- 2. MONTAGEM DO JSON ---
    snprintf(txPacket, TX_BUFFER_SIZE,
      "{"
        "\"device_serial_number\":\"INSIRA_SEU_SERIAL_AQUI\","
        "\"readings\":["
          "{\"sensor_name_or_id\":\"air_tem\",\"value\":\"%.1f\",\"unit_of_measurement\":\"°C\",\"timestamp\":\"%s\"},"
          "{\"sensor_name_or_id\":\"air_hum\",\"value\":\"%.1f\",\"unit_of_measurement\":\"%%\",\"timestamp\":\"%s\"},"
          "{\"sensor_name_or_id\":\"soil_tem\",\"value\":\"%.1f\",\"unit_of_measurement\":\"°C\",\"timestamp\":\"%s\"},"
          "{\"sensor_name_or_id\":\"soil_hum\",\"value\":\"%.1f\",\"unit_of_measurement\":\"%%\",\"timestamp\":\"%s\"},"
          "{\"sensor_name_or_id\":\"rain\",\"value\":\"%.2f\",\"unit_of_measurement\":\"mm\",\"timestamp\":\"%s\"}"
        "]"
      "}",
      dhtTemperature, timestampString,
      dhtHumidity, timestampString,
      shtTemperature, timestampString,
      shtHumidity, timestampString,
      rainMM, timestampString
    );

    Serial.println("\n--- Enviando POST para o servidor ---");
    Serial.println("Payload JSON que será enviado:");
    Serial.println(txPacket);

    // --- 3. DISPARO DA REQUISIÇÃO ---
    int httpResponseCode = http.POST(txPacket);

    if (httpResponseCode > 0) {
      Serial.print("\nCódigo HTTP retornado: ");
      Serial.println(httpResponseCode); 
      
      String payload = http.getString();
      Serial.println("Resposta do Servidor: " + payload);
    } else {
      Serial.print("\nErro na requisição: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Erro: Wi-Fi desconectado.");
  }

  // Pausa de 10 segundos antes de enviar o próximo dado
  delay(10000); 
}
