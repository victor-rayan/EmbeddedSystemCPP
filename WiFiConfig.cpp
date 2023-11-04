#include "Arduino.h"
#include "WiFiConfig.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "UniqueID.h"

AsyncWebServer server(80);

const char* ap_ssid = "ESP32-AP";
const char* ap_password = "password";

const char* input_parameter1 = "input_ssid";
const char* input_parameter2 = "input_password";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Bem-vindo ao Configurador IrrigaJá</title>
    <style>
        body{background-color:#008000;font-family:"Times New Roman",Times,serif;text-align:center;margin:0;padding:0}
        h2{font-size:2.5rem;color:#fff;padding:20px 0}
        form{background-color:#fff;border-radius:10px;max-width:300px;margin:0 auto;padding:20px 40px 30px 20px}
        label{display:block;text-align:left;font-weight:bold;margin-top:10px;color:#008000}
        input[type="text"]{width:100%;padding:10px;margin-top:5px;border:1px solid #008000;border-radius:5px}
        input[type="submit"]{background-color:#008000;color:#fff;border:none;padding:10px 20px;margin-top:20px;cursor:pointer;border-radius:5px}
        input[type="submit"]:hover{background-color:#006600}
    </style>
</head>
<body>
    <h2>Bem-vindo ao Configurador IrrigaJá</h2>
    <form action="/connect" method="get">
        <p>Configure o seu IrrigaJá para uma plantação mais eficiente!</p>
        <label for="input_ssid">Nome da sua Rede Wi-Fi (SSID):</label>
        <input type="text" id="input_ssid" name="input_ssid" required placeholder="Digite o nome da sua rede Wi-Fi">
        <label for="input_password">Senha da sua Rede Wi-Fi:</label>
        <input type="text" id="input_password" name="input_password" required placeholder="Digite a senha da sua rede Wi-Fi">
        <input type="submit" value="Conectar ao IrrigaJá">
    </form>
</body>
</html>
)rawliteral";

const char success_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
    <title>Configuração Concluída</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {font-family: Times New Roman; display: inline-block; text-align: center;}
      h2 {font-size: 3.0rem; color: #008000;}
      button {padding: 10px; font-size: 1.5rem;}
    </style>
    </head><body>
    <h2>Configuração Concluída</h2>
    <h3>Seu irrigador está quase configurado. Acesse <a href="http://irrigaja.com.br" style="color: #008000;">irrigaja.com.br</a> e utilize seu código:</h3>
    <p><strong id="uniqueID">%s</strong></p>
    <button onclick="copyToClipboard()">Copiar Código</button>
  
    <script>
      function copyToClipboard() {
        var id = document.getElementById("uniqueID");
        var textArea = document.createElement("textarea");
        textArea.value = id.textContent;
        document.body.appendChild(textArea);
        textArea.select();
        document.execCommand("copy");
        document.body.removeChild(textArea);
        alert("ID copiado para a área de transferência: " + id.textContent);
      }
    </script>
  </body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void returnMessageWhenConnected(){
    String id = getUniqueID();
    String response = String(success_html);
    response.replace("%s", id);
    request->send(200, "text/html", response);
}

bool connectToWiFi(const String& ssid, const String& password) {
  WiFi.disconnect();
  WiFi.begin(ssid.c_str(), password.c_str());

  int timeout = 10; // Tentar se conectar por até 10 segundos
  while (timeout > 0) {
    if (WiFi.status() == WL_CONNECTED) {
      return true; // Conectado com sucesso
    }
    delay(1000);
    timeout--;
  }
  return false; // Falha na conexão
}

void setupWebServer() {
  Serial.begin(115200);

  // Configure a rede WiFi como ponto de acesso (AP)
  WiFi.softAP(ap_ssid, ap_password);

  // Obtenha o endereço IP do ponto de acesso
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("IP Address: ");
  Serial.println(apIP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/connect", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String input_ssid;
    String input_password;

    if (request->hasParam(input_parameter1)) {
      input_ssid = request->getParam(input_parameter1)->value();
    }

    if (request->hasParam(input_parameter2)) {
      input_password = request->getParam(input_parameter2)->value();
    }

    // Tentar conectar a ESP32 à rede WiFi
    if (connectToWiFi(input_ssid, input_password)) {
      String id = getUniqueID();
      String response = String(success_html);
      response.replace("%s", id);
      request->send(200, "text/html", response);
    } else {
      request->send(200, "text/html", "Falha ao conectar à rede WiFi: " + input_ssid);
    }

  });

  server.onNotFound(notFound);
  server.begin();
}