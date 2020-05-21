#include<ESP8266WiFi.h>
#include<PubSubClient.h>
#include<SoftwareSerial.h>

SoftwareSerial s(4,5);

const char* ssid="Sreelath";
const char* password="9849444584";
const char* mqtt_server="broker.mqttdashboard.com";

#define MQTT_PUB "/Sensors"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

//////////////////////////////////////////////////////////////////////////////////////////////////WiFi SETUP////////////////////////////////////////////////////////////////////////////////////////////////////
void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

//////////////////////////////////////////////////////////////////////////////////////////////////RECONNECT/////////////////////////////////////////////////////////////////////////////////////////////////////
void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting MQTT connection..");
    client.publish("outTopic","hello");
    if(client.connect("ESP8266Client123456789")){
      Serial.println("connected");
      client.subscribe("/Lane1");
      client.subscribe("/Lane2");
    }
    else{
      Serial.print("failed,rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////CALLBACK////////////////////////////////////////////////////////////////////////////////////////////////////
void callback(const char* topic,byte* payload,unsigned int length1){
  Serial.print("Message arrived[");
  Serial.print(topic);
  Serial.print("]");

  char t1[]="/Lane1";
  char t2[]="/Lane2";

  String msgt;

  for(int i=0;i<length1;i++){
    Serial.print((char)payload[i]);
    msgt+=(char)payload[i];
  }
  Serial.println();

  String so="L";
  
  if(strcmp(topic,t1)==0){
    so=so+"1";
  }else if(strcmp(topic,t2)==0){
    so=so+"2";
  }
  so=so+msgt;
  s.println(so);
  Serial.println(so);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////PUBLISHING////////////////////////////////////////////////////////////////////////////////////////////////
void publishSerialData(char *serialData){
  if(!client.connected()){
    reconnect();
  }
  Serial.println(serialData);
  client.publish(MQTT_PUB,serialData);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  s.begin(115200);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
  reconnect();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////LOOP///////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  client.loop();

  if(Serial.available()>0){
    char bfr[101];
    memset(bfr,0,101);
    Serial.readBytesUntil('\n',bfr,100);
    publishSerialData(bfr);
  }
}
