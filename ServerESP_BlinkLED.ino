#include <WiFi.h>
#include <WebServer.h>

// --- Configurações da sua Rede ---
const char* ssid = "NOME DA REDE";
const char* password = "SENHA DA REDE";

// --- Configuração do Pino ---
// Use 2 para ESP32 genérico ou 25 se for a placa Heltec LoRa
const int ledPin = 2; 

// Cria o servidor web na porta 80 (porta padrão de navegadores)
WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  // Configura o pino do LED como saída e garante que inicie apagado
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  // Inicia a conexão Wi-Fi
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Aguarda até conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Imprime o endereço IP gerado (você vai precisar dele!)
  Serial.println("\nWi-Fi Conectado!");
  Serial.print("Endereço IP do ESP32: ");
  Serial.println(WiFi.localIP());

  // --- Rotas HTTP do Servidor ---
  
  // 1. Rota Principal (Acessar apenas o IP)
  server.on("/", []() {
    server.send(200, "text/plain", "Servidor do ESP32! Use /on para acender o LED ou /off para apagar.");
  });

  // 2. Rota para Acender o LED
  server.on("/on", []() {
    digitalWrite(ledPin, HIGH); // Liga o LED
    server.send(200, "text/plain", "LED ACESO com sucesso!");
    Serial.println("Comando via HTTP: LED Aceso");
  });

  // 3. Rota para Apagar o LED
  server.on("/off", []() {
    digitalWrite(ledPin, LOW); // Desliga o LED
    server.send(200, "text/plain", "LED APAGADO com sucesso!");
    Serial.println("Comando via HTTP: LED Apagado");
  });

  // Inicia o servidor para começar a escutar as requisições
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

void loop() {
  // Essa função deve ficar no loop para processar quem tenta acessar o IP
  server.handleClient();
}
