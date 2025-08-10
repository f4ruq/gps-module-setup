#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#define RXPIN 17
#define TXPIN 18

TinyGPSPlus gps;
HardwareSerial GPSSerial(1);                  // UART1

void setup() {
  Serial.begin(115200);                       // USB-CDC (PC'ye log)
  GPSSerial.setRxBufferSize(1024);
  GPSSerial.begin(9600, SERIAL_8N1, RXPIN, TXPIN);  // RX=17 (GPS TX), TX=18 (GPS RX)
  Serial.println("waiting for gps data..");
}

void loop() {
  while (GPSSerial.available()) {
    char c = GPSSerial.read();
    gps.encode(c);

    if (gps.location.isUpdated()) 
    {
      Serial.print("coordinates: ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" ,");
      Serial.println(gps.location.lng(), 6);
      Serial.print("number of satellites : ");
      Serial.println(gps.satellites.value());
      Serial.print("HDOP: ");
      Serial.println(gps.hdop.hdop());
      Serial.println("----------------------");
    }
  }
} 
