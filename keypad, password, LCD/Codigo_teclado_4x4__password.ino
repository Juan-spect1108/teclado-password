#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Password.h> //Incluimos la libreria Password
#include <Keypad.h> //Incluimos la libreria Keypad
 
Password password = Password("1234A");  //Definimos el Password
int dlugosc = 5;                        //Largo del Password
 
int buzzer = 12; //Creamos las Variables de salida

int ilosc; //Numero de Clicks
 
const byte ROWS = 4; // Cuatro Filas
const byte COLS = 4; // Cuatro Columnas

// Definimos el Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 9,8,7,6 };// Conectar los keypads ROW1, ROW2, ROW3 y ROW4 a esos Pines de Arduino.
byte colPins[COLS] = { 5,4,3,2, };// Conectar los keypads COL1, COL2, COL3 y COL4 a esos Pines de Arduino.
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27,16,2);

Servo servo;

int estado;
void setup(){
  servo.attach(11);
  lcd.init();                         
  lcd.backlight();
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);  
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print(" clave: ");
  lcd.setCursor(0,1);
  lcd.print(" Inserte el pin ");
  servo.write(0);
}
 
void loop()
{
  keypad.getKey();
}
void keypadEvent(KeypadEvent eKey)
{
  switch (keypad.getState())
  {
    case PRESSED:
   
int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(200);            
  digitalWrite(buzzer, LOW);  
  delay(100);      
}    
 
Serial.print("Pressed: ");
Serial.println(eKey);
 
switch (eKey)
{
/*
case '#':
break;
 
case '*':
break;
*/
 
default:
ilosc=ilosc+1;
password.append(eKey);
}
//Serial.println(ilosc);
 
if(ilosc == 1)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("*_");
}
if(ilosc == 2)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("**_");
}
if(ilosc == 3)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("***_");
}
if(ilosc == 4)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("****_");
}
if(ilosc == 5)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("*****_");
}

 if(ilosc == dlugosc){
delay(250);
checkPassword();
ilosc = 0;
}
}
}
 
void checkPassword()
{
  if (password.evaluate())
  {
int i;
for( i = 1; i <= 3; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(120);            
  digitalWrite(buzzer, LOW);  
  delay(70);      
}    
    ilosc = 0;
    password.reset();
    Serial.println("Correcto");    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(" CORRECTO :)");    
    delay(2000);
    servo.write(90);
delay(3000);
servo.write(0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CLAVE:");
    
  }  
  else  
  {
int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(300);            
  digitalWrite(buzzer, LOW);  
  delay(100);      
}  
    ilosc = 0;  
    password.reset();
    Serial.println("Error");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(" INCORRECTO :(");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Bienvenido ");
    lcd.setCursor(0,1);
    lcd.print("Clave:"); 
   
  }
  
}
