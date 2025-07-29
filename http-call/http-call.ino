#include <WiFi.h>
#include <ArduinoHttpClient.h>
#define LED_BUILTIN 2

char ssid[] = "methylphenidate_generic";
char pass[] = "marnie&poppy";
char addr[] = "192.168.254.177";
int port = 8888;
WiFiClient wifi;
HttpClient client = HttpClient( wifi, addr, port );
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  while ( status != WL_CONNECTED) {
	Serial.print("Status: ");
    Serial.println(status);
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    WiFi.begin(ssid, pass);
	status = WiFi.waitForConnectResult();
	delay(5000);
  }

  // print the SSID of the network you're attached to:
  Serial.print("connected to SSID: ");
  Serial.println(ssid);
  printCurrentNet();
  printWifiData();
}

void loop() {
  Serial.println("making GET request");
  client.get("/cgi-bin/index.py");
//   client.get("/");

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: '");
  Serial.print(response);
  Serial.println("'");
  
  if ( response == "Meet is Running\r\n") {
  	Serial.println("Turn on Light");
	digitalWrite(LED_BUILTIN, HIGH);
  } else {
  	Serial.println("Turn off Light");
	digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.println("Wait 1 second");
  delay(1000);
}



void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");

  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

}

void printMacAddress(byte mac[]) {
  for (int i = 0; i < 6; i++) {
    if (i > 0) {
      Serial.print(":");
    }
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
  }
  Serial.println();
}