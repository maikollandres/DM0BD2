#include <OBD2UART.h>
#include <LiquidCrystal.h>

COBD obd;

//LCD
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{

  //LCD
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  lcd.print("RPM :");
  lcd.setCursor(6, 1);
  
  // we'll use the debug LED as output
  pinMode(13, OUTPUT);
  // start communication with OBD-II adapter
  obd.begin();
  // initiate OBD-II connection until success
  while (!obd.init());
}

void loop()
{
  lcd.setCursor(6, 1);
  lcd.print("");
  int value;
  // save engine RPM in variable 'value', return true on success
  if (obd.readPID(PID_RPM, value)) {
   // if (obd.readPID(PID_ENGINE_FUEL_RATE,value)){
    // light on LED on Arduino board when the RPM exceeds 3000
    digitalWrite(13, value > 2000 ? HIGH : LOW);
    lcd.setCursor(6, 1);
    lcd.print(value);
  }
}
