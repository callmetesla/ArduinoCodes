#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial my(9, 10);
char d, r[12], welcome[] = "RFID authentication system";
int rcnt = 0;
bool flag = false;
// Enter your keys here
char key[][12] = { "530095F66858", "1121212" };
char userdata[][22] = { "Arun Baalaaji", "Abhijit" };
void setup()
{
    lcd.begin(16, 2);
    my.begin(9600);
    Serial.begin(9600);
    lcd.print("RFID");
    lcd.setCursor(0, 1);
    lcd.print("Authentication");
    delay(5000);
    lcd.clear();
}
void loop()
{
    if (my.available()) {
        r[rcnt] = my.read();
        rcnt++;
    }
    if (rcnt == 12) {
        Serial.print("Read Data:");
        for (int i = 0; i < 12; i++) {
            Serial.write(r[i]);
        }
        Serial.println();
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 12; j++) {
                if (key[i][j] == r[j])
                    flag = true;
                else
                    flag = false;
            }
            if (flag == true) {
                lcd.setCursor(0, 0);
                lcd.print("User Name:");
                Serial.print("User Name:");
                for (int k = 0; k < strlen(userdata[i]); k++) {
                    Serial.write(userdata[i][k]);
                }
                lcd.setCursor(0, 1);
                lcd.print(userdata[i]);
                Serial.println();
                delay(3000);
                lcd.clear();
            }
        }
        rcnt = 0;
    }
    delay(100);
}
