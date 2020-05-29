#include<SoftwareSerial.h>

SoftwareSerial sw(52, 53);

int ir_l1[] = {A0, A1, A2, A3};

int irm = 0;
int cars = 0;

int ir[] = {A0, A1, A2, A3, A7, A6, A5, A4};
const int irl = sizeof(ir) / sizeof(ir[0]);
int ir_values[irl];
int led[] = {11, 9, 8, 6, 5, 4, 3};
const int ledl = sizeof(led) / sizeof(led[0]);
int led_var[ledl];

int irp[] = {A8, A9};
int irp_values[2];
int ledp[] = {22, 23};
int ledp_var[2];

int ldr[] = {A10, A11};
int ldr_values[2];
int y[2];

void cons(char bfr[4]) {
  Serial.print("LANE ");
  Serial.print(bfr[1] + ": ");
  Serial.print("LED ");
  Serial.print(bfr[2] + ": ");
  int k = (int)bfr[2] - 48;
  int lane = (int)bfr[1] - 48;
  if (lane == 1) {
    if (bfr[3] == 'O') {
      if (k > 4) {
        digitalWrite(ledp[k - 5], HIGH);
      } else {
        digitalWrite(led[k - 1], HIGH);
      }
      Serial.println("ON");
    } else if (bfr[3] == 'F') {
      if (k > 4) {
        digitalWrite(ledp[k - 5], LOW);
      } else {
        digitalWrite(led[k - 1], LOW);
      }
      Serial.println("OFF");
    }
  } else if (lane == 2) {
    if (bfr[3] == 'O') {
      digitalWrite(led[k + 3], HIGH);
      Serial.println("ON");
    } else if (bfr[3] == 'F') {
      digitalWrite(led[k + 3], LOW);
      Serial.println("OFF");
    }
  }
}

void rec() {
  if (Serial.available() > 0) {
    char bfr[5];
    memset(bfr, 0, 6);
    Serial.readBytesUntil('\n', bfr, 4);
    Serial.println(bfr);
    cons(bfr);
  }
}

void irmode() {
  rec();
  if (irm == 0) {
    ldr_values[0] = analogRead(ldr[0]);
    ldr_values[1] = analogRead(ldr[1]);
    y[0] = 255 - ldr[0];
    y[1] = 255 - ldr[1];
    if (y[0] < 0) {
      y[0] = 0;
    }
    if (y[1] < 0) {
      y[1] = 0;
    }

    for (int i = 0; i < 4; i++) {
      analogWrite(led[i], y[0]);
    }
    for (int i = 4; i < 7; i++) {
      analogWrite(led[i], y[1]);
    }
    irm = irm + 1;
    return;
  }

  else {
    //    ldr_values[0] = analogRead(ldr[0]);
    //    ldr_values[1] = analogRead(ldr[1]);
    //    y[0] = 255 - ldr[0];
    //    y[1] = 255 - ldr[1];
    //    if (y[0] < 0) {
    //      y[0] = 0;
    //    }
    //    if (y[1] < 0) {
    //      y[1] = 0;
    //    }
    y[0] = 0;
    y[1] = 0;
    for (int i = 0; i < irl; i++) {
      ir_values[i] = digitalRead(ir[i]);
      if (ir_values[i] == LOW) {
        analogWrite(led[i], 255);
        analogWrite(led[i + 1], 255);
        led_var[i] = 1;
        led_var[i + 1] = 2;
        if (i > 0) {
          if (i < 4) {
            analogWrite(led[i - 1], y[0] );
          } else {
            analogWrite(led[i - 1], y[1]);
          }
          led_var[i - 1] = 0;
        }
      }
    }



    for (int i = 0; i < ledl; i++) {
      if (led_var[i] == 1) {
        analogWrite(led[i], 255);
        analogWrite(led[i + 1], 255);
      }
      else if (led_var[i] == 0) {
        if (i < 4) {
          analogWrite(led[i], y[0] );
        } else {
          analogWrite(led[i], y[1]);
        }
      }
    }

    for (int i = 0; i < 2; i++) {
      irp_values[i] = digitalRead(irp[i]);
      if (irp_values[i] == LOW) {
        if (cars == 0 || cars == 1) {
          cars = cars + 1;
        }
        digitalWrite(ledp[i], HIGH);
        if(i==1){
          analogWrite(led[i+1],y[0]);
          analogWrite(led[i+2],y[0]);
          led_var[i+1]=0;
          led_var[i+2]=0;
        }
      } else {
        if (cars > 0) {
          cars = cars - 1;
        }
        else {
          cars = 0;
        }

        delay(1000);
        digitalWrite(ledp[i], LOW);
      }
    }
    sw.print("C:");
    sw.println(cars);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Interfacing with NodeMCU");
  sw.begin(115200);
  for (int i = 0; i < irl; i++) {
    pinMode(ir[i], INPUT);
  }

  for (int i = 0; i < ledl; i++) {
    pinMode(led[i], OUTPUT);
  }

}

void loop() {
  ldr_values[0] = analogRead(ldr[0]);
  ldr_values[1] = analogRead(ldr[1]);
  delay(2000);
  Serial.print("{\"ldr");
  Serial.print(1);
  Serial.print("\":");
  Serial.print(ldr_values[0]);
  Serial.print(",\"ldr");
  Serial.print(2);
  Serial.print("\":");
  Serial.print(ldr_values[1]);
  Serial.print("}");
  Serial.println();

  sw.print("{\"ldr");
  sw.print(1);
  sw.print("\":");
  sw.print(ldr_values[0]);
  sw.print(",\"ldr");
  sw.print(2);
  sw.print("\":");
  sw.print(ldr_values[1]);
  sw.print("}");
  sw.println();

  if (Serial.available() > 0) {
    rec();
  } else {
    irmode();
  }
}
