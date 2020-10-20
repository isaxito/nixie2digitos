
#include <Wire.h>
#include "RTClib.h"

#define punto 255

// SDA 5
// SCL 7

#define pinDato 3      // Pin conectado a DS pin 14 de 74HC595
#define pinClock 1  // Pin conectado a SHCP pin 11 de 74HC595
#define pinRegistro 4  // Pin conectado a STCP pin 12 de 74HC595
RTC_DS3231 rtc;
int horas, minutos;

int cambiar (int num);
void mostrarNum(int num);
int  decimalToBCD (int decimal);

void setup() {
  Wire.begin();
  pinMode(pinRegistro, OUTPUT);
  pinMode(pinClock, OUTPUT);
  pinMode(pinDato, OUTPUT);
  digitalWrite(pinRegistro, LOW);
}

void loop() {
  DateTime now = rtc.now();

  // Muestra la hora
  horas = now.hour();
  mostrarNum(cambiar(horas));
  delay(1000);

  // Muestra los puntos
  shiftOut(pinDato, pinClock, MSBFIRST, punto);
  digitalWrite(pinRegistro,HIGH);
  digitalWrite(pinRegistro,LOW);
  shiftOut(pinDato, pinClock, MSBFIRST, punto);
  digitalWrite(pinRegistro,HIGH);
  digitalWrite(pinRegistro,LOW);
  delay(700);

  // Apaga el punto y muestra los minutos
  minutos = now.minute();
  mostrarNum(cambiar(minutos));
  delay(1000);

  // BLANCO
  shiftOut(pinDato, pinClock, MSBFIRST, B10101010);
  digitalWrite(pinRegistro, HIGH);
  digitalWrite(pinRegistro, LOW);
  delay(500);
  

}

int cambiar(int num)
{
  int d1, d2, nfinal;
  d1 = num % 10;
  d2 = (num / 10) % 10;
  if (d1 == 0)
    d1 = 9;
  else
    d1--;
  if (d2 == 0)
    d2 = 9;
  else
    d2--;
  nfinal = d2 + d1 * 10;
  return nfinal;
}
void mostrarNum(int num)
{
  shiftOut(pinDato, pinClock, MSBFIRST, decimalToBCD(num));
  digitalWrite(pinRegistro, HIGH);
  digitalWrite(pinRegistro, LOW);
}

int  decimalToBCD (int decimal)
{
  return (((decimal / 10) << 4) | (decimal % 10));
}
