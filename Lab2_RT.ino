byte numbers[10] = { B11111100, // 0
                     B01100000, // 1
                     B11011010, // 2
                     B11110010, // 3
                     B01100110, // 4
                     B10110110, // 5
                     B10111110, // 6
                     B11100000, // 7
                     B11111110, // 8
                     B11110110};// 9}
int Apin = 2;
int Bpin = 3;
int Cpin = 4;
int Dpin = 5;
int Epin = 6;
int Fpin = 7;
int Gpin = 8;
int DPpin = 9;
void writeDigitN(int, int);
unsigned long lastTime = 0;
unsigned long lastTime1 = 0;
int currDig = 0;
byte ledDigits[4] = {0, 0, 0, 0};
byte section1 = 0;
byte section2 = 0;
byte section3 = 0;
byte section4 = 0;
bool isPaused = true;
int pauseButton = 14;
int setZeroButton = 15;
int startButton = 16;
void writeDigitN(int num, int n)
{
 // Сначала выключим все 4 разряда
 for (int i = 10; i <= 13; i++)
 digitalWrite(i, HIGH);
 // На аноды подадим значения для цифры num
 for (int i = 0; i < 7; i++) // Цикл по сегментам
 {
 digitalWrite(Apin + i, bitRead(numbers[num],7 - i));
 }
 // Включим только разряд n
 digitalWrite(n + 10, LOW);
}

void setup() {
  for (int i = Apin; i <= DPpin; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);  
  }
  digitalWrite(DPpin, HIGH);

  
  for (int i = 10; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);  
  }

  for (int i = 14; i <= 16; i++)
  {
    pinMode(i, INPUT);
    digitalWrite(i, LOW);  
  }
  // put your setup code here, to run once:

}

void DisplayNumbers()
{
  if (micros() - lastTime > 5000)
 {
   lastTime = micros();
   // Отображаем цифру №(currDig) в разряде currDig
   writeDigitN(ledDigits[currDig], currDig);
   currDig++; // Переходим к следующему разряду
 if (currDig > 3) currDig = 0; // Зацикливаем
 }
}
void loop()
{

  
  if (micros() - lastTime1 > 10000)
  {
    lastTime1 = micros();
    if (digitalRead(setZeroButton))
    {
      ledDigits[0] = 0;
      ledDigits[1] = 0;
      ledDigits[2] = 0;
      ledDigits[3] = 0;
    }
    if (!isPaused)
    {
      if(digitalRead(pauseButton)) isPaused = true;
        
      if (section4 < 9) section4++;
      else 
      {
        section4 = 0;
        if (section3 < 9) section3++;
        else
        {
          section3 = 0;
          if (section2 < 6) section2++;
          else
          {
            section2 = 0;
            if (section1 < 6) section1++;
            else section1 = 0; 
          }  
        }
        
    }
    ledDigits[0] = section1;
    ledDigits[1] = section2;
    ledDigits[2] = section3;
    ledDigits[3] = section4;

    DisplayNumbers();
    }
    else 
    {
      if(digitalRead(startButton)) isPaused = false;  
    }
    
  }
  
}
