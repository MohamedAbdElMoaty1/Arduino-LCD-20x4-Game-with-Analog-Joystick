#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 4, 20);

int vx = A1;
int vy = A0;
byte sw = A3;
int readx = 0;
int ready = 0;
int mapX = 0;
int mapY = 0;
int x;
int y;
byte moveY;
byte moveX;
byte i = 19;
int Score = 0;
byte counter = 0;
long t;
long t1;

long Time;
bool cs = false;
byte d[] = {
    B00110,
    B01110,
    B01111,
    B00111,
    B10110,
    B01110,
    B00100,
    B00100};
byte a[] = {
    B00011,
    B00111,
    B01111,
    B11111,
    B11111,
    B01111,
    B00111,
    B00011};

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    pinMode(sw, INPUT_PULLUP);
    pinMode(vx, INPUT);
    pinMode(vy, INPUT);
}

void joystick()
{
    lcd.createChar(0, d);
    lcd.setCursor(x, y);
    lcd.write(byte(0));
    readx = analogRead(vx);
    ready = analogRead(vy);
    mapX = map(readx, 0, 1023, -512, 512);
    mapY = map(ready, 0, 1023, -512, 512);

    if ((mapX == 0) && (mapY == 512))
    {
        y--;
        lcd.createChar(0, d);
        lcd.setCursor(x, y);
        lcd.write(byte(0));
        lcd.setCursor(x, y + 1);
        lcd.print(" ");
        delay(50);
    }
    if ((mapX == 0) && (mapY == -512))
    {
        y++;
        lcd.createChar(0, d);
        lcd.setCursor(x, y);
        lcd.write(byte(0));
        lcd.setCursor(x, y - 1);
        lcd.print(" ");
        delay(50);
    }
    if ((mapX == -512) && (mapY == 0))
    {
        x++;
        lcd.createChar(0, d);
        lcd.setCursor(x, y);
        lcd.write(byte(0));
        lcd.setCursor(x - 1, y);
        lcd.print(" ");
        delay(50);
    }
    if ((mapX == 512) && (mapY == 0))
    {
        x--;
        lcd.createChar(0, d);
        lcd.setCursor(x, y);
        lcd.write(byte(0));
        lcd.setCursor(x + 1, y);
        lcd.print(" ");
        delay(50);
    }
    if ((y > 3) || (y < 0) || (x > 19) || (x < 0))
    {
        y = 0;
        x = 0;
        i = 19;
        moveY = 0;
        moveX = 0;
        counter = 0;
        Serial.println("Game Over");
        Serial.print("Score = ");
        Serial.println(Score);
        Serial.println("_________________________________________________________");
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print(" Game Over ");
        lcd.setCursor(4, 2);
        lcd.print(" Score = ");
        lcd.print(Score);

        delay(1000);
        lcd.clear();
        lcd.createChar(0, d);
        lcd.setCursor(0, 0);
        lcd.write(byte(0));
        Score = 0;
    }
}

void motion()
{
    joystick();
    moveY = random(4);
    moveX = random(4);
    for (byte i = 19; i >= 0; i--)
    {
        counter++;
        joystick();
        lcd.createChar(1, a);
        lcd.setCursor(i, moveY);
        lcd.write(byte(1));
        lcd.setCursor(i + 1, moveY);
        lcd.print(" ");
        delay(30);
        lcd.createChar(1, a);
        lcd.setCursor(i + 2, moveY);
        lcd.write(byte(1));
        lcd.setCursor(i + 3, moveY);
        lcd.print(" ");
        t1=millis();
        delay(30);
        if (i > 19)
        {
            motion();
        }
        if (counter == 16)
        {
            lcd.createChar(1, a);
            lcd.setCursor(i + 3, moveY);
            lcd.write(byte(1));
            cs = true;
            t=millis();
        }
            if (( cs==true && (y == moveY) && (x == (i)) ))
            {
                Score++;
                cs = false;
                Serial.print("Score = ");
                Serial.println(Score);
            }
        
        if ((y == moveY) && (x == (i)))
        {
            y = 0;
            x = 0;
            i = 19;
            moveY = 0;
            moveX = 0;
            counter = 0;
            Serial.println("Game Over");
            Serial.print("Score = ");
            Serial.println(Score);
            Serial.println("_________________________________________________________");

            lcd.clear();
            lcd.setCursor(4, 1);
            lcd.print(" Game Over ");
            lcd.setCursor(4, 2);
            lcd.print(" Score = ");
            lcd.print(Score);

            delay(1000);
            lcd.clear();
            lcd.createChar(0, d);
            lcd.setCursor(0, 0);
            lcd.write(byte(0));
            Score = 0;
        }
    }
}

void loop()
{
    motion();
}
