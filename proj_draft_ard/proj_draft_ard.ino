#include<SoftwareSerial.h>
#include<DS3231.h>

SoftwareSerial sw(52,53);


///////////////////////////////////////////////////////////////////////////////////////////////////PARKING / LANE 1/////////////////////////////////////////////////////////////////////////////////////////////
int ir_l1[]={A0,A1,A2,A3};
const int ir_l1_length=sizeof(ir_l1)/sizeof(ir_l1[0]);
int ir_park[]={A8,A9};
int ir_park_values[2];
int ir_l1_values[ir_l1_length];
int led_l1[]={11,10,9,8,7,6};
const int led_l1_length=sizeof(led_l1)/sizeof(led_l1[0]);
int led_l1_var[led_l1_length];
int led_park[]={22,23};


////////////////////////////////////////////////////////////////////////////////////////////////////////LDR////////////////////////////////////////////////////////////////////////////////////////////////////
int id[]={1,2};
int ldr[]={A10,A11};
const int ldr_length=sizeof(ldr)/sizeof(ldr[0]);
int ldr_values[ldr_length];
int y[ldr_length];


///////////////////////////////////////////////////////////////////////////////////////////////////////LANE 2//////////////////////////////////////////////////////////////////////////////////////////////////

int ir_l2[]={A7,A6,A5,A4};
const int ir_l2_length=sizeof(ir_l2)/sizeof(ir_l2[0]);
int ir_l2_values[ir_l2_length];
int led_l2[]={5,4,3};
int led_l2_var[led_l2_length];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////FUNCTIONS////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////RECIEVE SUBFUNC/////////////////////////////////////////////////////////////////////////////////////////////////
void cons(char bfr[4]){
  Serial.print("LANE ");
  Serial.print(bfr[1]+": ");
  Serial.print("LED ");
  Serial.print(bfr[2]+": ");
  int k=(int)bfr[2]-48;
  int lane=(int)bfr[1]-48;
  if(lane==1){
    if(bfr[3]=='O'){
      analogWrite(led_l1[k-1],255);
      Serial.println("ON");
    }else if(bfr[3]=='F'){
      analogWrite(led_l1[k-1],0);
      Serial.println("OFF");
    }
  }else if(lane==2){
    if(bfr[3]=='O'){
      analogWrite(led_l2[k-1],255);
      Serial.println("ON");
    }else if(bfr[3]=='F'){
      analogWrite(led_l2[k-1],0);
      Serial.println("OFF");
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////RECIEVE/////////////////////////////////////////////////////////////////////////////////////////////////
void recieve(){
  if(Serial.available()>0){
    char bfr[4];
    memeset(bfr,0,4);
    Serial.readBytesUntil('\n',bfr,3);
    Serial.println(bfr);
    cons(bfr); 
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void irmode_l2(){
  ldr_values[1]=analogRead(ldr[1]);
  y[1]=255-ldr_values[1];
  if(y[1]<0){
    y[1]=0;
  }
  for(int i=0;ir_l2_length;i++){
    ir_l2_values[i]=digitalRead(ir_l2[i]);
    if(ir_l2_values[i]==LOW){
      analogWrite(led_l2[i],255);
      analogWrite(led_l2[i+1],255);
    }
  }
  delay(100);
  for(int i=0;i<3;i++){
    analogWrite(led_l2[i],y[1]);
  }
  

  
  
}
void setup() {
  Serial.begin(115200);
  Serial.println("Interfacing with NodeMCU");
  sw.begin(115200);
  for(int i=0;i<2;i++){
    pinMode(ldr[i],INPUT);
    pinMode(ir_park[i],INPUT);
    pinMode(led_park[i],OUTPUT);
  }

  for(int i=0;i<3;i++){
    pinMode(led_l2[i],OUTPUT);
  }

  for(int i=0;i<4;i++){
    pinMode(ir_l1[i],INPUT);
    pinMode(ir_l2[i],INPUT);
  }

  for(int i=0;i<led_l1_length;i++){
    pinMode(led_l1[i],OUTPUT);
  }
}

void loop() {
  ldr_values[0]=analogRead(ldr[0]);
  ldr_values[1]=analogRead(ldr[1]);
  Serial.print("{\"sensorid\":");
  Serial.print(id[0]);
  Serial.print("\"ldr");
  Serial.print(1);
  Serial.print("\":");
  Serial.print(ldr_values[0]);
  Serial.print("}");
  Serial.println();
  Serial.print("{\"sensorid\":"};
  Serial.print(id[1]);
  Serial.print("\"ldr");
  Serial.print(2);
  Serial.print("\":");
  Serial.print(ldr_values[1]);
  Serial.print("}");
  Serial.println();

  sw.print("{\"sensorid\":");
  sw.print(id[0]);
  sw.print("\"ldr");
  sw.print(1);
  sw.print("\":");
  sw.print(ldr_values[0]);
  sw.print("}");
  sw.println();
  sw.print("{\"sensorid\":"};
  sw.print(id[1]);
  sw.print("\"ldr");
  sw.print(2);
  sw.print("\":");
  sw.print(ldr_values[1]);
  sw.print("}");
  sw.println();

  if(ldr_values[0]<100 || ldr_values[1]<100){
    
}
