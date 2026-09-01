#include <ESP8266WiFi.h>

const char* ssid = "wifi name";
const char* password = "password";

WiFiServer server(80);

const int relayPin = D1;

void setup() {

  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server Started");
}

void loop() {
  WiFiClient client = server.available();

  if (!client) {
    return;
  }
  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();
  
  if (request.indexOf("/ON") != -1) {

    digitalWrite(relayPin, LOW);

    Serial.println("Light is ON");
  }

  if (request.indexOf("/OFF") != -1) {

    digitalWrite(relayPin, HIGH);

    Serial.println("Light is OFF");
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<html>");
  client.println("<head>");
  client.println("<title>Smart Light Control</title>");
  client.println("</head>");

  client.println("<body>");
  client.println("<h1>Smart Home Automation</h1>");
  client.println("<p>Light Control System</p>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  client.stop();
}
