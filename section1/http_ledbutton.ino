#include <WiFi.h>

const char* ssid = "xxx-xxx-xxx";
const char* password = "xxx-xxx-xxx";
const int button = 32;
const int led = 33;
int buttonState = 0;
WiFiServer server(80);


void setup(){
	Serial.begin(115200);
	pinMode(button,INPUT);
	pinMode(led1,OUTPUT);
	
	Serial.print("Connecting to Wifi..");
	Wifi.begin(ssid,password);
	while (WiFi.status != WL_CONNECTED){
		delay(500);
		Serial.print(".");
	}
	Serial.println("\nConnected");
	Serial.print("IP Address: ");
	Serial.println(WiFi.localIP());

	server.begin();
	Serial.println("Server started on port 80");
}

void loop(){
	buttonState = digitalRead(button);
	
	if(buttonState == LOW){
		digitalWrite(led,HIGH);
	}else{
		digitalWrite(led,LOW);
	}
	WiFiClient client = server.available()
	if(client){
    	// Generate HTML response
    	client.println("HTTP/1.1 200 OK");
    	client.println("Content-type:text/html");
    	client.println("Connection: close");
    	client.println();
    
   	client.println("<!DOCTYPE html><html><head><title>ESP32 LED Status</title>");
    	client.println("</head><body>");
    	client.println("<h2>ESP32 Web Server</h2>");
    	client.println("<h3>LED Status: " + String((buttonState == LOW) ? "ON" : "OFF") + "</h3>");
    	client.println("</body></html>");

    	client.stop();
    	Serial.println("Client disconnected.");
  }
}
