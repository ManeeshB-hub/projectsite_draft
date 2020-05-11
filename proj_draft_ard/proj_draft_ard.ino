#include<SoftwareSerial.h>
#include<DS3231.h>

SoftwareSerial sw(52,53);


//////////////////////////////////////////////////PARKING / LANE 1/////////////////////////////////
int ir_l1[]={A0,A1,A2,A3};
const int ir_l1_length=sizeof(ir_l1)/sizeof(ir_l1[0]);
int ir_park[]={A8,A9};
int ir_park_values[2];
int ir_l1_values[ir_l1_length];
int led_l1[]={11,10,9,8,7,6};
const int led_l1_length=sizeof(led_l1)/sizeof(led_l1[0]);
int led_l1_var[led_l1_length];
int led_park[]={22,23};


////////////////////////////////////////////////LDR/////////////////////////////////////////////////
int id[]={1,2};
int ldr[]={A10,A11};
const int ldr_length=sizeof(ldr)/sizeof(ldr[0]);
int ldr_values[ldr_length];
int y[ldr_length];


////////////////////////////////////////////////LANE 2///////////////////////////////////////////////

int ir_l2[]={A7,A6,A5,A4};
const int ir_l2_length=sizeof(ir_l2)/sizeof(ir_l2[0]);
int ir_l2_values[ir_l2_length];
int led_l2[]={5,4,3};
int led_l2_var[led_l2_length];

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
