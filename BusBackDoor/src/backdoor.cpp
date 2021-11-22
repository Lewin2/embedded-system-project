#include <Arduino.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <String.h>
#include <Wire.h>

#define sv 8

SoftwareSerial mySerial(6, 7);

// �� ��ȣ ����
const int pinServo = 3;
const int pinTrig = 2;
const int pinEcho = 4;

const int RS = 8; const int EN = 9;
const int D4 = 10; const int D5 = 11;
const int D6 = 12; const int D7 = 13;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// ��������
Servo servo;

// ������
int rangeMax = 200;
int rangeMin = 0;

long L;

boolean dooropen = false;
boolean openclose = false; // ���� ���ȴ� ����?
boolean isClosed = false;

unsigned long l1, l2;

// �����ǥ��
byte creat1[] = {
  B00000,
  B00000,
  B00110,
  B01000,
  B10000,
  B10000,
  B01001,
  B00110
};

byte creat2[] = {
  B10000,
  B00000,
  B10000,
  B10000,
  B11000,
  B01000,
  B01100,
  B00000
};

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);

    Wire.begin(sv);
    Wire.onReceive(receiveEvent);

    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);

    // ��������
    servo.attach(pinServo);
    servo.write(0);

    Serial.println("S - start");

    // LCD
    lcd.begin(16, 2);
    lcd.createChar(1, creat1);
    lcd.createChar(2, creat2);
}

String strOpen = "open";
String strClose = "close";
byte c = '1';

void loop() {
    // ������
    digitalWrite(pinTrig, LOW); delayMicroseconds(2);
    digitalWrite(pinTrig, HIGH); delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);

    L = pulseIn(pinEcho, HIGH) / 58.82;

    // �����ĺ��� ���ٴڱ��� �� 18cm
    // �����ĺ��� ���ٴ�(��)���� �� 12cm

    // UART���(������-��ư)  �������� ��ư�� ������ �޹� ����
    if (mySerial.available()) {
        // Serial.readStringUntil('\n') \n���ڸ� ������ ���� ���ڿ� �б�
        String inString = mySerial.readStringUntil('\n');
        boolean open = inString.equals(strOpen);
        boolean close = inString.equals(strClose);
        if (open) {
            servo.write(180);
            Serial.println("S - open");
            //lcd.clear();
            //lcd.setCursor(0, 0); lcd.print("                ");
            //lcd.setCursor(5, 0); lcd.print("OPEN!");
            lcd.setCursor(0, 1); lcd.print("                ");
        }
        else if (close) {
            servo.write(0);
            openclose = true;

            l1 = millis();
            isClosed = true;
            Serial.println("S - close");
            //lcd.clear();
            //lcd.setCursor(0, 0); lcd.print("                ");
            //lcd.setCursor(5, 0); lcd.print("CLOSE");
            lcd.setCursor(0, 1); lcd.print("                ");
        }
    }

    // ���(������-��ư) �����ķ� ���� ���� �������� ������ �����Ϳ� ���� ���ȴٰ� �˸�
    if (isClosed && openclose && L <= 10) {
        servo.write(180);
        dooropen = true;
        openclose = false;
        Serial.println("S - ������, open");
        lcd.setCursor(0, 1); lcd.print("                ");
        lcd.setCursor(1, 1); lcd.print("CHECK BACKDOOR");
        mySerial.write('1'); // ������ �߻��Ͽ� �������� close�� open���� �ٲ�
    }

    l2 = millis();
    if (l2 - l1 >= 3000) {
        isClosed = false;
    }

}

// I2C��� (������-���̽�ƽ) ���� ������ ���� ���� LCD�� ���� ���
void receiveEvent(int howMany) {
    char c = Wire.read();

    switch (c) {
    case '1':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("400");
        lcd.setCursor(0, 1); lcd.print("                ");
        lcd.setCursor(0, 1); lcd.write(1);
        lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(0, 1); lcd.print("SCH University");
        break;

    case '2':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("403");
        lcd.setCursor(0, 1); lcd.write(1);
        lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(0, 1); lcd.print("SCH University");
        break;

    case '3':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("410");
        lcd.setCursor(0, 1); lcd.write(1);
        lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(0, 1); lcd.print("SCH University");
        break;

    case '4':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("430");
        lcd.setCursor(0, 1); lcd.write(1);
        lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(0, 1); lcd.print("SCH University");
        break;

    case '5':
        lcd.setCursor(0, 0); lcd.print("                ");
        lcd.setCursor(5, 0); lcd.write(1);
        lcd.setCursor(6, 0); lcd.write(2);
        lcd.setCursor(8, 0); lcd.print("441");
        lcd.setCursor(0, 1); lcd.write(1);
        lcd.setCursor(1, 1); lcd.write(2);
        lcd.setCursor(0, 1); lcd.print("SCH University");
        break;
    }
}