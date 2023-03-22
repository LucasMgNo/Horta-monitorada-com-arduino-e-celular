#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "horta-monitorada-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "VF02UvmYYFHxikxGghYeL6i0W8KPPxDXjPI0wCi2"
#define WIFI_SSID "TddsFibra_Nem Tenta "
#define WIFI_PASSWORD "tempos2525"

SoftwareSerial mySerial (D1, D2);


void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.setTimeout(100);
  mySerial.setTimeout(100);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int humidAr, tempAr, temp1, temp2,humid1;

void loop(){
  if (mySerial.available()){
  String recebido = mySerial.readStringUntil('\n');
  String msg = recebido;

  if(msg.startsWith("T")){
    msg.remove(0,1);
    tempAr = msg.toInt();
  } 
  if (msg.startsWith("H")){
    msg.remove(0,1);
    humidAr = msg.toInt();
  }
  if (msg.startsWith("t1")){
    msg.remove(0,2);
    temp1 = msg.toInt();
  }
  else if (msg.startsWith("t2")){
    msg.remove(0,2);
    temp2 = msg.toInt();
  }
  }

  Serial.print(humidAr);
  Serial.print("\n");
  Serial.print(tempAr);
  Serial.print("\n");
  Serial.print(temp1);
  Serial.print("\n");
  Serial.print(temp2);
  Serial.print("\n");
  delay(1000);

  Firebase.setInt("ar/temperatura",tempAr);
  Firebase.setInt("ar/humidade",humidAr);
  Firebase.setInt("solo1/temperatura",temp1);
  Firebase.setInt("solo2/temperatura",temp2);
}
