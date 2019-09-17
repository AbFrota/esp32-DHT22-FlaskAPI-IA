//Incluindo as bibliotecas necessárias

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <DHT_U.h>

// Nome da sua rede Wifi
//const char* ssid = "Project Planet 2G";
//const char* ssid = "SENHOR_DOS_PAPEIS";
const char* ssid = "LIVE TIM_3EC0_2G";

// Senha da rede
//const char* password = "pp40dciot";
const char* password = "43pve8fpp6";
String servidor = String("http://192.168.1.41:5000/predict");

// Pino do DHT
#define DHTPIN 13

// Definindo o sensor como DHT11
#define DHTTYPE DHT22

// Inicializando o sensor DHT
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // Iniciando o Serial
  Serial.begin(115200);

  // Iniciando o DHT
  dht.begin();  // Conectando na rede wifi

  Serial.println("");
  Serial.print("Conectando");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a rede: ");
  Serial.println(ssid);
}
void loop() {
  

  // Lendo a temperatura em graus Celsius
  int t = dht.readTemperature();
  int h = dht.readHumidity();

  HTTPClient http;

  // Enviando para o host a temperatura lida.
  http.begin(servidor);
  http.addHeader("Content-Type","application/x-www-form-urlencoded;charset=UTF-8");

  int httpResponseCode = http.POST(String("temperature=") + t + String("&humidity=") + h);

  if (httpResponseCode > 0) {

    String response = http.getString();  //Get the response to the request

    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer

  } else {

    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);

  }

  // Repetindo a cada 5 segundos
  delay(10000);

  Serial.print("Temperatura enviada: ");
  Serial.println(t);
}
