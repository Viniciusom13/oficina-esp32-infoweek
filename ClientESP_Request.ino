#include <WiFi.h>
#include <HTTPClient.h>

// --- Configurações da sua Rede (Precisa ter internet!) ---
const char* ssid = "NOME DA REDE";
const char* password = "SENHA";

// A URL exata do servidor (geralmente precisa do caminho final, ex: /api/dados)
String serverName = "https://uaipy-app-be-4ap2g.ondigitalocean.app/";

void setup() {
  Serial.begin(115200);

  // Inicia a conexão Wi-Fi
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado à Internet com sucesso!");

  // --- FAZENDO A REQUISIÇÃO HTTP ---
  // Verifica se o Wi-Fi ainda está conectado
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Prepara a requisição para a URL do servidor
    Serial.println("Iniciando conexão com o servidor UAI.py...");
    http.begin(serverName); 

    // Dispara uma requisição do tipo GET
    int httpResponseCode = http.GET();

    // Se o código for maior que 0, a requisição chegou lá
    if (httpResponseCode > 0) {
      Serial.print("Código de Resposta HTTP: ");
      Serial.println(httpResponseCode);
      
      // Lê o que o servidor respondeu (ex: um JSON confirmando o recebimento)
      String payload = http.getString();
      Serial.println("Resposta do Servidor:");
      Serial.println(payload);
    } else {
      Serial.print("Erro na requisição HTTP: ");
      Serial.println(httpResponseCode);
    }

    // Encerra a conexão para liberar memória
    http.end();
  } else {
    Serial.println("Erro: Wi-Fi desconectado.");
  }
}

void loop() {

}
