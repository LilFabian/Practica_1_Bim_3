/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Practica 1.
   Dev: Fabian Andree Sinay Canel
   Fecha: 8 de julio.
*/
#include <Wire.h>    
#include <LiquidCrystal_I2C.h>  

#define IN1  9
#define IN2  10
#define IN3  11
#define IN4  12

#define sensor_IR 2
#define sensor_H 3
#define direccion_lcd 0x27
#define filas 2
#define columnas 16
LiquidCrystal_I2C LCD(direccion_lcd, columnas, filas); 

bool state_sensor;
int contador = 0;
int Pot;
int paso [8][4] =
{
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

 int Interrupcion(){
  contador ++ ;
 }

void setup()
{
  LCD.init(); 
  LCD.backlight(); 
  LCD.print("Contador de rev.");  
  LCD.setCursor(0, 1);
  LCD.print("No.de rev.");  
  Serial.begin(9600); 
  
  
  pinMode(sensor_IR, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
 
  
void loop()
{ 
  attachInterrupt(digitalPinToInterrupt(sensor_H), Interrupcion, FALLING);
  Serial.println(contador);
  LCD.setCursor(12, 1);
  LCD.print(contador);  
 state_sensor = digitalRead(sensor_IR);

  if(state_sensor == LOW){
 Pot = map(analogRead(A0), 0, 1023, 0, 3);
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(Pot);
    }
    }
}