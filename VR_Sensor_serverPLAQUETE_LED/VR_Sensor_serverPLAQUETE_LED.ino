/* Creates a WiFI access point (default IP is 192.168.4.1) opens up Udp port 8888 and accepts data.
   hacked from the ESP8266 AP and Udp examples by Alexandre Castonguay for Yesica Duarte
*/
/// TODO : Merge with the sensor receive code and sending to Unity ////
int LED = D2;

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged\r\n";       // a string to send back

WiFiUDP Udp;


void setup()
{
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  Serial.println();

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESPdatos", "respiracion");

  if (result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }

  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);

}


void loop()
{
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    Serial.println(" ");
    Serial.println(packetBuffer);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();

    delay (150);


//    if ( Udp.write = ("belly, 2") ) {
//      digitalWrite(LED, HIGH);
//      delay(5000);
//    }
//    if ( Udp.write = ("belly, 1") ) {
//      digitalWrite(LED, LOW);
//      delay(3000);
//    }



  }

}

