
#include <Wire.h> //Libreria para utilizar el modulo I2C
#include <LiquidCrystal_I2C.h>//Libreria para utilizar el modulo LCD
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define PULSO 5 // Pin del Relay
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Crea la instancia MFRC522
LiquidCrystal_I2C lcd(0x27,16,2); //Función constructor, crea un 
//objeto de la clase LiquidCrystal_I2C, con dirección, columnas y filas indicadas.

void setup() 
  {Serial.begin(9600);   // Inicializa la comunicacion serial
  SPI.begin();          // Inicializa el bus SPI
  mfrc522.PCD_Init();   // Inicializa el MFRC522
  pinMode(PULSO, OUTPUT);
  digitalWrite(PULSO, LOW);
  Serial.println("Ponga su Tarjeta para la lectura...");
  Serial.println();
  lcd.init();//Inicializa el modulo adaptador LCD a I2C, 
  //esta función internamente configura e inicializa el I2C y el LCD.
  lcd.backlight();}
  void loop() 
  {lcd.print(" IDENTIFICACION");
  
  lcd.setCursor(0,1);
  lcd.print("TARJETA-LLAVERO");
  // Mirando para nuevas tarjeras
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {return;  }
  // Selecciona una de las tarjetas
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}
  // Muestra el UID sobre el Monitor Serial
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
   Serial.print(mfrc522.uid.uidByte[i], HEX);
   content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
   content.concat(String(mfrc522.uid.uidByte[i], HEX));}
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "49 37 4C D3") //CODIGO DE LA TARJETA
  {Serial.println("Acceso Autorizado");lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     ABIERTO   ");
  lcd.setCursor(0,1);
  lcd.print("Acceso Autorizado");
  digitalWrite(PULSO, HIGH);  delay(1000);  digitalWrite(PULSO,LOW); lcd.clear();}

  //if (content.substring(1) == "82 B5 59 1C") //codigo tarjeta
  //{
    //Serial.println("Acceso Autorizado");
    //lcd.clear();
  // lcd.setCursor(0,0);
  //lcd.print("     ABIERTO");
  //lcd.setCursor(0,1);
 // lcd.print("TARJETA INGRESADA ");
  //digitalWrite(PULSO, HIGH);
  //delay(1000);
  //digitalWrite(PULSO,LOW);
  //lcd.clear();
  //}
  else
  {
    Serial.println("Acceso Denegado");
    lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("     CERRADO");
  lcd.setCursor(0,1);
  lcd.print("Acceso Denegado ");
  digitalWrite(PULSO,LOW);
  delay(1000);
  lcd.clear();
  }

}
