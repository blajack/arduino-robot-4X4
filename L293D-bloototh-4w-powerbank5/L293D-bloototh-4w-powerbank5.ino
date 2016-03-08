
// ВЕРСИЯ С BLOOTOTH И ПОВОРОТОМ БАШНИ

// ПРОВЕРКА BLOOTOTH
// ПОДКЛЮЧЕНИЕ 3,3V-3,3V , GND, TX->RX, RX->TX
// СОЗДАТЬ ПАРУ В БЛЮТУС УСТРОЙСТВАХ (ПАРОЛЬ:1234)
// ПОДКЛЮЧЕНИЕ С МАКА. В ТЕРМИНАЛЕ
// ls /dev/tty.*
// screen /dev/tty.HC-06-DevB

/* УПРАВЛЕНИЕ
 * 1-5 переключение скоростей
 * W - вперед
 * S - назад
 * F - вправо
 * A - влево
 * Space/=/0 - остановка
 * 
 * ПОВОРОТ БАШНИ
 * I/O/P/[/]
 */

#include <Servo.h> 
Servo myservo;



int IN1 = 8; //input1 подключен к выводу 8 
int IN2 = 7;
int IN3 = 2;
int IN4 = 4;

int EN1 = 11;
int EN2 = 6;
int i;

int MaxSpeed = 150;
int SlowSpeed = 0; // переменная для плавного старта

char val; // variable to receive data from the serial port
int ledpin = 13; // LED connected to pin 13 (on-board LED)

int HeadPosition = 100;

void setup()
{
  pinMode (EN1, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (EN2, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (IN3, OUTPUT);

  // ПОДКЛЮЧАЕМ BLOOTOTH

    pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
    Serial.begin(9600);       // start serial communication

  // Камеру ставим по центу
  myservo.attach(9);
  myservo.write(HeadPosition);
}


void loop()
{

if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();  
  }

  if( val == 'W' )               // Вперед
  {
  digitalWrite (IN2, HIGH);
  digitalWrite (IN1, LOW); 
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW); 

  //Цифра 1,2,3,4 - это направление, 
  //цифра берется по часовой (1-вперед,
  //2 - вправо, 3-назад, 4-влево
  //нужно для плавного набора скорости
  //если направление выбрано в первый раз
  
    if ( SlowSpeed != 1 )         
    {
      for (int i=0; i <= MaxSpeed; i=i+5)
      {
        analogWrite(EN1, i);
        analogWrite(EN2, i);
        delay(10);
      }
      SlowSpeed = 1;
    }
    else
    {
      analogWrite(EN1, MaxSpeed);
      analogWrite(EN2, MaxSpeed);
    }
  }

  if( val == 'D' )               // Вправо
  {
    digitalWrite (IN1, HIGH);
    digitalWrite (IN2, LOW); 
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW); 
  
    analogWrite(EN1, 0); // стопим левые колеса
  
    if ( SlowSpeed != 2 )
      {
        for (int i=0; i <= 200 ; i=i+5)
        {
          analogWrite(EN2, i);
          delay(10);
        }
        SlowSpeed = 2;
      }
      else
      {
          analogWrite(EN2, 250);
      }
  }

 
  if( val == 'E' )               // Вправо-второй парой колес
  {
    digitalWrite (IN1, HIGH);
    digitalWrite (IN2, LOW); 
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW); 
  
    analogWrite(EN2, 0); // стопим левые колеса
  
    if ( SlowSpeed != 2 )
      {
        for (int i=0; i <= 200 ; i=i+5)
        {
          analogWrite(EN1, i);
          delay(10);
        }
        SlowSpeed = 2;
      }
      else
      {
          analogWrite(EN1, 250);
      }
  }





  if( val == 'A' )               // Влево
  {
    digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW); 
    digitalWrite (IN3, HIGH);
    digitalWrite (IN4, LOW); 
  
    analogWrite(EN2, 0);   // СТОПИМ ПРАВЫЕ КОЛЕСА
    
    if ( SlowSpeed != 4 )
      {
        for (int i=0; i <= 200 ; i=i+5)
        {
          analogWrite(EN1, i);
          delay(10);
        }
        SlowSpeed = 4;
      }
      else
      {
        analogWrite(EN1, 250);
      }
    
  }

  if( val == 'Q' )               // Влево-второй парой колес
  {
    digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW); 
    digitalWrite (IN3, HIGH);
    digitalWrite (IN4, LOW); 
  
    analogWrite(EN1, 0);   // СТОПИМ ПРАВЫЕ КОЛЕСА
    
    if ( SlowSpeed != 4 )
      {
        for (int i=0; i <= 200 ; i=i+5)
        {
          analogWrite(EN2, i);
          delay(10);
        }
        SlowSpeed = 4;
      }
      else
      {
        analogWrite(EN2, 250);
      }
    
  }


   
  if( val == 'S' )               // Назад
  {
    digitalWrite (IN1, HIGH);
    digitalWrite (IN2, LOW); 
    digitalWrite (IN3, HIGH);
    digitalWrite (IN4, LOW); 
  
    if ( SlowSpeed != 3 )
      {
        for (int i=0; i <= MaxSpeed; i=i+5)
        {
          analogWrite(EN1, i);
          analogWrite(EN2, i);
          delay(10);
        }
        SlowSpeed = 3;
      }
      else
      {
        analogWrite(EN1, MaxSpeed);
        analogWrite(EN2, MaxSpeed);
      }
  }

   


  // выбор максимальной скорости
  // и остановка робота
  if( val == ' ' || val == '='   )               // Остановка
  {
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
  }
  
  if( val == '0' )               // Остановка и средняя скорость
  {
    SlowSpeed = 0;
    MaxSpeed = 150;
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
  }

  if( val == '1' )               
  {
    MaxSpeed = 50;
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
  }


  if( val == '2' )               
  {
    MaxSpeed = 100;
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
  }

  if( val == '3' )               
  {
    MaxSpeed = 150;
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
  }

  if( val == '4' )               
  {
    MaxSpeed = 200;
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
  }
  
  if( val == '5' )               
  {
    MaxSpeed = 250;
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
  }

  //Поворот камеры
  if( val == 'P' )      // ПО ЦЕНТРУ         
  {

    
    if (HeadPosition >= 100)
      {
        while (HeadPosition >=100)
        {
           myservo.write(HeadPosition);
           HeadPosition = HeadPosition -2;
           delay (30);
        }
      }
    else
    {
        for (i=HeadPosition; i<=100; i=i+2)
      {
        myservo.write(i);
        delay (30); 
      }
    }

    HeadPosition = 100;
  }   


 if( val == 'O' )      // ПО ЦЕНТРУ         
  {
    
    if (HeadPosition >=146)
      {
        while (HeadPosition >=146)
        {
           myservo.write(HeadPosition);
           HeadPosition = HeadPosition -2;
           delay (30);
        }
      }
    else
    {
        for (i=HeadPosition; i<=146; i=i+2)
      {
        myservo.write(i);
        delay (30); 
      }
    }
    HeadPosition = 146;
    
  }   


   if( val == '[' )      //        
  {
    
    if (HeadPosition >=46)
      {
        while (HeadPosition >=46)
        {
           myservo.write(HeadPosition);
           HeadPosition = HeadPosition -2;
           delay (30);
        }
        
      }
    else
    {
        for (i=HeadPosition; i<=46; i=i+2)
      {
        myservo.write(i);
        delay (30); 
      }
    }
    HeadPosition = 46;
  }   


  if( val == 'I' )      //        
  {
    
    if (HeadPosition >=180)
      {
        while (HeadPosition >=180)
        {
           myservo.write(HeadPosition);
           HeadPosition = HeadPosition -2;
           delay (30);
        }
        
      }
    else
    {
        for (i=HeadPosition; i<=180; i=i+2)
      {
        myservo.write(i);
        delay (30); 
      }
    }
    HeadPosition = 180;
  }  
    
  if( val == ']' )      //        
  {
    
    if (HeadPosition >=10)
      {
        while (HeadPosition >=10)
        {
           myservo.write(HeadPosition);
           HeadPosition = HeadPosition -2;
           delay (30);
        }
        
      }
    else
    {
        for (i=HeadPosition; i<=10; i=i+2)
      {
        myservo.write(i);
        delay (30); 
      }
    }
    HeadPosition = 10;
  }  
  


   
  
 
  
  
  delay(50);
  val=0;
  
  
}
