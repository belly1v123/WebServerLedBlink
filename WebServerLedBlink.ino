// led blink project that works on ESP32
// make sure you import the webserver file
// change the Wi-fi credentials and upload the code then check the serial monitor you will get the ip address like http://192.168.18.xxx/ then go to your browser and paste the ip address to interact


#include <WiFi.h>
#include <WebServer.h> //do not forgot to import the web-server-file

// Replace with your Wi-Fi credentials
const char* ssid = "Pranjal_2.4";
const char* password = "PK@98400";

const int ledPin = 2; //defult led pin of esp32 

WebServer server(80);

// HTML content
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 LED Control</title>
  <style>
    body { font-family: Arial; text-align: center; padding-top: 50px; }
    h1 { color: #333; }
    button {
      font-size: 20px;
      padding: 10px 20px;
      margin: 20px;
      cursor: pointer;
      border: none;
      border-radius: 5px;
    }
    .on { background-color: #4CAF50; color: white; }
    .off { background-color: #f44336; color: white; }
  </style>
</head>
<body>
  <h1>ESP32 LED Controller</h1>
  <button class="on" onclick="location.href='/led/on'">Turn LED ON</button>
  <button class="off" onclick="location.href='/led/off'">Turn LED OFF</button>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleLedOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);  // Redirect to root page
}

void handleLedOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);  // Redirect to root page
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
