/*
 * DEBER 5.1: MEMORIA EEPROM
 * NOMBRE: RAFAEL FARINANGO
 */
 
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Keypad.h> 

LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'7','8','9','A'},
  {'4','5','6','B'},
  {'1','2','3','C'},
  {'*','0','#','D'}
};

byte pinesFilas[FILAS] = {13,12,11,10};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {9,8,7,6}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

const int led1 = 5;
const int sw = 4;
char c;
int bb;
int cont = 0;
String palabra;

void setup() {
  Serial.begin(9600);
  lcd.begin(20,2);
  lcd.setCursor(0,0);
  lcd.print(" Almacenar de Datos");
  pinMode(led1,OUTPUT);   
}

void loop() {
  c = teclado.getKey();
  if(c){
    if(c != '#' && cont < 15){
      cont++;
      palabra +=c;
      bb = int(c);
      Serial.println(c);
      EEPROM.write((cont-1),c);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(String("Dato N: ")+String(cont));
      lcd.setCursor(0,1);
      lcd.print(c);
      digitalWrite(led1,HIGH);
      delay(500);
      digitalWrite(led1,LOW);
      delay(100);
    }
    else{
      Serial.println("Lectura de Datos");
      Serial.println(palabra);
      cont = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Lectura de Datos");
      //lcd.setCursor(0,1);
      //lcd.print(palabra);
      palabra = " ";
      for(int j=0; j<15; j++){
        lcd.setCursor(j+j,1);
        lcd.print(EEPROM.read(j));         
      }
    }
  }

}
