#include <WiFi.h>

// Replace with your WiFi credentials
const char* ssid = "vivoV29";
const char* password = "11111111";
const int relay = 19;

WiFiServer server(80); // Create a server on port 80

void setup() {
  Serial.begin(115200); // Start serial communication
  delay(1000);
  pinMode(relay,OUTPUT);
  Serial.print("Connecting to WiFi..");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Check for incoming requests

  if (client) {
    Serial.println("Client connected!");
    String request = client.readStringUntil('\r'); // Read the request line
    request.trim();

    // Handle different request types (e.g., GET, POST)
    if (request.indexOf("/on") != -1 && request.startsWith("GET")) {
      // Send sensor data or other information in response to a GET request at /data
      String response = "{'sensor1': 10, 'sensor2': 20}"; // Replace with actual data
      //pin handle
      digitalWrite(relay,LOW);
      //http handle
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Content-Length: " + response.length());
      client.println();
      client.println(response);
    }

        if (request.indexOf("/off") != -1 && request.startsWith("GET")) {
              //pin handle
       digitalWrite(relay,HIGH);
      // Send sensor data or other information in response to a GET request at /data
      String response = "{'sensor1': 10, 'sensor2': 20}"; // Replace with actual data
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Content-Length: " + response.length());
      client.println();
      client.println(response);
    }

    client.stop(); // Stop serving this client
  }
}