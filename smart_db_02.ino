/*PROJECT CODE MUNICIPAL CORPORATION SMART E DUST BIN

 All copy rights reserve to RAJASHEKHAR KANUKUNTLA KTECH SREE KANNA */

// library for servo,wire , lcdI2C.

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create an LCD object using I2C communication (0x27 is the default address).
  LiquidCrystal_I2C lcd(0x27, 16, 2);  

  // Create a servo motor object.
  Servo servo;

  // Stores a text message.
  String textMessage;

  // Pin definitions for LEDs indicating bin capacity and status.
  int led1 = 2;
  int led2 = 3;
  int led3 = 4;
  int led4 = 5;// used as led and relay

  // Ultrasonic sensor pins for measuring human distance.
  const int trigPins = 12;
  const int echoPins= 11;
  // Ultrasonic sensor pins for measuring bin level.
  const int trigPinl = 10;
  const int echoPinl= 9;

  // Pin for controlling the servo motor.
  const int servoPin = 6;
  
  void setup() {
    // Initialize serial communication at a baud rate of 9600.
    Serial.begin(9600);
    servo.attach(servoPin); // Attach the servo motor to its control pin.

    // Set pin modes for ultrasonic sensors and LEDs.
    pinMode(trigPins, OUTPUT);
    pinMode(echoPins, INPUT);
    pinMode(trigPinl, OUTPUT);
    pinMode(echoPinl, INPUT); 
  
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    
     // Initialize and configure the LCD screen.
    lcd.init();
    lcd.clear();
    lcd.begin(20, 4);
    lcd.backlight();  // Turn on the LCD backlight.
    lcd.setCursor(0, 0);
    lcd.print("MUNICIPAL CORPORATION"); //PRINT  MUNICIPAL CORPORATION ON LCD
    lcd.setCursor(0, 1);
    lcd.print("  SMART-E-DUSTBIN"); //PRINT  SMART-E-DUSTBIN ON LCD
}
  
  
  
  void loop()
  {
     // Measure the distance using the ultrasonic sensor for human detection.
    digitalWrite(trigPins, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPins, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins, LOW);
  
    long durations = pulseIn(echoPins, HIGH);
    int distances = durations * 0.034 / 2;

   // Measure the distance using the ultrasonic sensor for bin level.
    digitalWrite(trigPinl, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinl, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinl, LOW);
  
    long durationl = pulseIn(echoPinl, HIGH);
    int distancel = durationl * 0.034 / 2;
    
     // Determine the status of the bin level based on its distance.
   if (distancel <= 15 )
    {
       // Small bin is full.
      digitalWrite(led1,HIGH);    
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      lcd.setCursor(0, 2);
      lcd.print("BIN CAPACITY:FULL   ");
      sendsms(); // Send an SMS notification.
    } 
  
    else if (distancel <= 30)
     {
      // Small bin is half full.
      
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);  
  
      lcd.setCursor(0, 2);
      lcd.print("BIN CAPACITY:HALF   ");
      
    }
  
  
      else if (distancel <= 50)
     {
      // Small bin is medium full.
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH); 
      digitalWrite(led4,HIGH); 
  
      lcd.setCursor(0, 2);
      lcd.print("BIN CAPACITY:MEDIUM   ");
      
    }
  
  
    else if (distancel <= 65)
     {
      // Small bin is empty.
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,HIGH);
  
      lcd.setCursor(0, 2);
      lcd.print("BIN CAPACITY:EMPTY  ");
  
    }
  
 // Determine the status of the human detection based on its distance.
  if (distances <=50)
  {
    // bin lid is open.
    lcd.setCursor(0, 3);
    lcd.print("BIN STATUS : OPEN ");
        
    servo.write(30);// Open the bin.
    delay(2000);
  
  }
  
  else 
  {
    // bin lid is closed.
    lcd.setCursor(0, 3);
    lcd.print("BIN STATUS : CLOSE");
    servo.write(90);// Close the bin.
    
  }
  }

  // Function to send an SMS notification.
  void sendsms()
  {
    // Set the GSM module to text mode.
      Serial.print("AT+CMGF=1\r");
      delay(100);
      // Specify the recipient's phone number.
      Serial.println("AT+CMGS =\"+91**********\"");
      delay(100);
     // Send the SMS message.
     Serial.println("SMART BUSTBIN MC21 IS FULL AT O-CITY MILLS GROUND LOCATION : https://maps.app.goo.gl/xWGeAe6N2kBKGFR17"); // send loctaion address and link via text message.
      delay(100);
      // Send the control character for the SMS.
      Serial.println((char)26);
      delay(100);
      Serial.println();
      delay(30000); // Delay before sending another SMS.
  
  }
  // Compiled with riscduino and arduino boards 
  
  //  final code, no error all ok, tested by RAJASHEKHAR KANUKUNTLA KTECH SREE KANNA 
