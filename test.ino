#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial GPSSerial(1);                  // UART1

void setup() {
  Serial.begin(115200);                       // USB-CDC (PC'ye log)
  GPSSerial.setRxBufferSize(1024);
  GPSSerial.begin(9600, SERIAL_8N1, 17, 18);  // RX=17 (GPS TX), TX=18 (GPS RX - opsiyonel)
  Serial.println("GPS verisi bekleniyor...");
}

void loop() {
  while (GPSSerial.available() > 0) {
    char c = GPSSerial.read();
    gps.encode(c);

    if (gps.location.isUpdated()) {
      Serial.print("Enlem: ");  Serial.println(gps.location.lat(), 6);
      Serial.print("Boylam: "); Serial.println(gps.location.lng(), 6);
      Serial.print("Uydu sayısı: "); Serial.println(gps.satellites.value());
      Serial.print("HDOP: ");   Serial.println(gps.hdop.hdop());
      Serial.println("----------------------");
    }
  }
}
