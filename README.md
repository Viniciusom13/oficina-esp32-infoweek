## 1️⃣ INSTALAR O DRIVER USB 
*(O computador precisa disso para "enxergar" a placa)*

* Placas comuns usam o chip CH340 ou CP210x.
* Baixe e instale o driver CP210x neste link (é o mais comum em placas convencionais): 
👉 [Driver CP210x da Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) *(baixe a versão para Windows ou Mac)*.
* Se puder, reinicie o PC depois de instalar.

---

## 2️⃣ CONFIGURAR O ARDUINO IDE

* Abra o **Arduino IDE**.
* Vá em: **Arquivo > Preferências**.
* No campo **"URLs Adicionais para Gerenciadores de Placas"**, cole este link exatamente como está:
`https://espressif.github.io/arduino-esp32/package_esp32_index.json`
* Clique em **OK**.

---

## 3️⃣ INSTALAR O PACOTE ESP32

* No menu esquerdo do Arduino IDE, clique no ícone do **Gerenciador de Placas** (parece uma caixinha com circuitos).
* Na barra de pesquisa, digite: `esp32 Espressif Systems`
* Procure pelo pacote da "Espressif Systems" e clique em **INSTALAR**.
* *(Aguarde um pouco, pois demora uns minutinhos para baixar tudo).*

---

## 4️⃣ CONECTAR A PLACA E SELECIONAR A PORTA

* Plugue o ESP32 no computador com um cabo USB.
* No menu superior do Arduino IDE, vá em: **Ferramentas > Placa > ESP32 Arduino**.
* Escolha o modelo: se for uma comum, selecione **"ESP32 Dev Module"**.
* Vá em: **Ferramentas > Porta** e selecione a porta COM que apareceu (ex: `COM3`, `COM4`, etc.). Se não aparecer nenhuma COM, o driver do Passo 1 não ficou bem instalado ou o cabo USB é ruim.

---

## 5️⃣ TESTE

* Cole o código que vai testar no Arduino IDE.
* Clique na **"Seta para a direita"** (Carregar) no topo do programa.
* Fique olhando a barra preta lá embaixo. Assim que aparecer a palavra `Connecting........___`, segure pressionado o botão **"BOOT"** (ou **"PRG"**) na placa física do ESP32.
* Mantenha pressionado até ver que começou a carregar (linhas com porcentagem 10%, 20%...). Quando começar a carregar, pode soltar o botão!
* Quando terminar, vai aparecer `Hard resetting via RTS pin...`. Pronto, código gravado!
