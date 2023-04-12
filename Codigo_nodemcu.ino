#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>        //biblioteca wifi do nodemcu
#include <FirebaseESP8266.h>    //biblioteca para o nodemcu conectar dom o firebase

// Set these to run example.
#define FIREBASE_HOST "horta-monitorada-default-rtdb.firebaseio.com"      //endereco do banco de dados
#define FIREBASE_AUTH "VF02UvmYYFHxikxGghYeL6i0W8KPPxDXjPI0wCi2"          //codigo de seguranca do banco
#define WIFI_SSID "TddsFibra_Nem Tenta "                                  //informacoes do wifi
#define WIFI_PASSWORD "tempos2525"

SoftwareSerial mySerial (D1, D2);             //configurar as portas do nodemcu para funcionar com RX e TX
FirebaseData firebaseData;

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);               //Inicia o Wifi no esp8266 passando o usuario e senha
   while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());                   //imprimi o IP da rede conectada pra confirmar a conexao
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);    //inicia a conexao com o banco de dados
}

int humidAr, tempAr, temp1, temp2,humid1;    //variaveis globais das informacoes recebbidas dos sensores

void loop(){
  if (mySerial.available()){                               //verifica se tem dados na porta serial
  String recebido = mySerial.readStringUntil('\n');       //recebe os dados da porta serial
  String msg = recebido;                                  //atribui o dado recebido a uma string para ser feita a manipulacao nessa string
  
                              //a partir daqui sao feitas as logicas para distinguir de qual sensor é a informação recebida, atraves de manipulação de string    
  if(msg.startsWith("T")){    //verifica a primeira letra de identificacao da variavel recebida para atribuir a sua respectiva variavel
    msg.remove(0,1);
    tempAr = msg.toInt();
  } 
  if (msg.startsWith("H")) {
      msg.remove(0, 1);
      if (msg.toInt() != humidAr && msg.toInt() >10){
      humidAr = msg.toInt();
  }
  if (msg.startsWith("t1")) {
      msg.remove(0, 2);
      if (msg.toInt() != temp1 && msg.toInt() >10){
      temp1 = msg.toInt();
  }
  else if (msg.startsWith("t2")) {
      msg.remove(0, 2);
      if (msg.toInt() != temp2 && msg.toInt() >10){
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

  Firebase.setInt(firebaseData,"/ar/temperatura",tempAr);           //envia as variaveis recebidas pelo serial para o firebase
  delay(200);
  Firebase.setInt(firebaseData,"/ar/humidade", humidAr);
  delay(200);
  Firebase.setInt(firebaseData,"/solo1/temperatura", temp1);
  delay(200);
  Firebase.setInt(firebaseData,"/solo2/temperatura", temp2);
  delay(1000);
}
