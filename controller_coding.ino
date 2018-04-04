/ Code to use SoftwareSerial
//The final sketch
 #include "SoftwareSerial.h"
 #include <dht.h>

#define dht_dpin 8

String data;
String ssid ="TRAK family";

String password="rukman12345";

SoftwareSerial espSerial(6, 7);// RX, TX


dht DHT;

int t;
int h;

String server = "svce-ece-b2.000webhostapp.com"; 

String uri = "/esp.php";



boolean DEBUG=true;


void showResponse(int waitTime){
    long t=millis();
    char c;
    while (t+waitTime>millis()){
      if (espSerial.available()){
        c=espSerial.read();
        if (DEBUG) Serial.print(c);
      }
    }
                   
}


void setup() {                
  DEBUG=true;    

  Serial.begin(115200);
  delay(500);
  
  espSerial.begin(115200); 
  
 espSerial.println("AT+RST");         // Enable this line to reset the module;
 showResponse(1000);

 // espSerial.println("CIOBAUD=9600");    // Enable this line to set esp8266 serial speed to 9600 bps
 // showResponse(1000);
  
  

  espSerial.println("AT+CWMODE=1");
  showResponse(1000);

 espSerial.println("AT+CWJAP=\""+ssid+"\",\""+password+"\""); 
  showResponse(5000);

   if (DEBUG)  Serial.println("Setup completed");
}

void httppost () {

espSerial.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.

if( espSerial.find("OK")) {

Serial.println("TCP connection ready");

} delay(1000);

String postRequest =

"POST " + uri + " HTTP/1.0\r\n" +

"Host: " + server + "\r\n" +

"Accept: *" + "/" + "*\r\n" +

"Content-Length: " + data.length() + "\r\n" +

"Content-Type: application/x-www-form-urlencoded\r\n" +

"\r\n" + data;

String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.

espSerial.print(sendCmd);

espSerial.println(postRequest.length() );

delay(500);

if(espSerial.find(">")) { Serial.println("Sending.."); espSerial.print(postRequest);

if( espSerial.find("SEND OK")) { Serial.println("Packet sent");

while (espSerial.available()) {

String tmpResp = espSerial.readString();

Serial.println(tmpResp);

}

// close the connection

espSerial.println("AT+CIPCLOSE");

}

}}


void loop() {

 // Read sensor values
  DHT.read11(dht_dpin);
    t = int(DHT.temperature);
    h = int(DHT.humidity);
        if (isnan(t) || isnan(h)) {
        if (DEBUG) Serial.println("Failed to read from DHT");
      }
      else {
          if (DEBUG)  Serial.println("Temp="+String(t)+" *C");
          if (DEBUG) Serial.println("Humidity="+String(h)+" %");
  
data = "temperature=" + String(t) + "&humidity=" + String(h);// data sent must be under this form //name1=value1&name2=value2.

httppost();
      }

delay(1000);
}
