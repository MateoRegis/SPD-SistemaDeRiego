#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 8, 4, 7, 2); // rs, enabled, d4, d5, d6, d7

int pinSensorHumedad = A1;
int pinSensorTemperatura = A0;
int pinSensorLuz = A2;
int pinRiego = 10;
int pinVentilacion = 6;
int pinRojo = 3;
int pinVerde = 5;
int pinAzul = 9;

void setup() {
  lcd.begin(16, 2);
  pinMode(pinVentilacion, OUTPUT);
  pinMode(pinRiego, OUTPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
}

void loop() {
  lcd.scrollDisplayLeft();
  float humedad = analogRead(pinSensorHumedad);
  int porcentajeHumedad = map(humedad, 0, 876, 0, 100);
  
  lcd.setCursor(0,0);
  lcd.print("H: ");
  lcd.setCursor(4,0);
  lcd.print(porcentajeHumedad);
  lcd.print("% ");
  if(porcentajeHumedad<35){
    analogWrite(pinRiego, 255);// Como utilizamos un pin PWM , podemos setear la velocidad mandandole
    //un valor entre 0 y 255; (0 es el minimo, 255 el maximo);
    lcd.setCursor(11,0);
   lcd.print(" Muy seco ");
  } else if (porcentajeHumedad >= 35 && porcentajeHumedad < 60) {
    analogWrite(pinRiego, 150); //Bajamos la velocidad, ya que hay un mayor porcentaje de humedad
    lcd.setCursor(11, 0);
    lcd.print(" Suelo seco ");
  } else {
    digitalWrite(pinRiego, LOW);// Como el suelo esta muy humedo, apagamos el motor de riego
    lcd.setCursor(11, 0);
    lcd.print(" Humedo      ");
  }
  float valorLeidoTMP = analogRead(pinSensorTemperatura);
  float temperatura = (((5 * valorLeidoTMP * 100) / 1024) - 50);
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(temperatura);
  lcd.print("C ");
  if (temperatura > 30) {
    analogWrite(pinVentilacion, 255);// Usamos la maxima velocidad del motor de ventilacion
    lcd.print(" Mucho Calor ");
  }
  else if(temperatura >= 15 && temperatura <= 30)
  {
    lcd.print("  Buen Clima ");
    analogWrite(pinVentilacion, 90);// Bajamos la velocidad del motor de ventilacion, ya que tenemos una temperatura media
  } 
  else {
    analogWrite(pinVentilacion, 0);
    lcd.setCursor(11, 1);
    lcd.print(" Mucho Frio ");
  }
  
  delay(100);
  
  int foto = analogRead(pinSensorLuz);
  delay(100);
  if (foto > 500) {
    analogWrite(pinRojo, 200);
    analogWrite(pinAzul, 100);
    analogWrite(pinVerde, 0);
  } else {
   	analogWrite(pinRojo, 0);
    analogWrite(pinAzul, 0);
    analogWrite(pinVerde, 0);
  }
}
