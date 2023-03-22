#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>        //biblioteca wifi do nodemcu
#include <FirebaseArduino.h>    //biblioteca para o nodemcu conectar dom o firebase

// Set these to run example.
#define FIREBASE_HOST "horta-monitorada-default-rtdb.firebaseio.com"      //endereco do banco de dados
#define FIREBASE_AUTH "VF02UvmYYFHxikxGghYeL6i0W8KPPxDXjPI0wCi2"          //codigo de seguranca do banco
#define WIFI_SSID "TddsFibra_Nem Tenta "                                  //informacoes do wifi
#define WIFI_PASSWORD "tempos2525"

SoftwareSerial mySerial (D1, D2);             //configurar as portas do nodemcu para funcionar com RX e TX


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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);    //inicia a conexao com o banco de dados
}

int humidAr, tempAr, temp1, temp2,humid1;    //variaveis globais das informacoes recebbidas dos sensores

void loop(){
  if (mySerial.available()){                //verifica se tem dados na porta serial
  String recebido = mySerial.readStringUntil('\n');       //recebe os dados da porta serial
  String msg = recebido;                    //atribui o dado recebido a uma string para ser feita a manipulacao nessa string
  
                              //a partir daqui sao feitas a logica para distinguir de qual sensor é a informação recebida, atraves de manipulação de string    
  if(msg.startsWith("T")){    //verifica a primeira letra de identificacao da variavel recebida para atribuir a sua respectiva variavel
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

  Serial.print(humidAr);        //imprime as informacoes para visualizacao no console
  Serial.print("\n");
  Serial.print(tempAr);
  Serial.print("\n");
  Serial.print(temp1);
  Serial.print("\n");
  Serial.print(temp2);
  Serial.print("\n");
  delay(1000);

  Firebase.setInt("ar/temperatura",tempAr);           //envia as variaveis recebidas pelo serial para o firebase
  Firebase.setInt("ar/humidade",humidAr);
  Firebase.setInt("solo1/temperatura",temp1);
  Firebase.setInt("solo2/temperatura",temp2);
}
