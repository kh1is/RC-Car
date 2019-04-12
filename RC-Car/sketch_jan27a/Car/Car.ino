 /* JoyStick module receiver code
 - CONNECTIONS: nRF24L01 Modules See:
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 6
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
 */
 
/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AFMotor.h>

/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN 18
#define CSN_PIN 19

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

#define light_Front  17     //LED Front Right   pin A4 for Arduino Uno
#define light_Back   16     //LED Back Right    pin A5 for Arduino Uno
#define horn_Buzz    15     

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

/*-----( Declare Variables )-----*/
//6 element array holding Joystick readings
int joystick[6];
int  xAxis=500, yAxis=500;

// the four button variables from joystick
int buttonUp;
int buttonRight;
int buttonDown;
int buttonLeft;

// the four car wheel motors
AF_DCMotor motor1(1);  // Left front
AF_DCMotor motor2(2);  // Left back
AF_DCMotor motor3(3);  // Right front
AF_DCMotor motor4(4);  // Right back

void setup()
{
  
  pinMode(light_Front, OUTPUT);
  pinMode(light_Back, OUTPUT);
  pinMode(horn_Buzz, OUTPUT);
  
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0,pipe);
  radio.startListening();
}

void loop()
{      
  if ( radio.available() ){
      radio.read( joystick, sizeof(joystick) );
      xAxis = joystick[0];
      yAxis = joystick[1];

      Serial.print("x= ");
      Serial.print(xAxis);
      Serial.print("   ");
      Serial.print("y= ");
      Serial.println(yAxis);
      
      
      // the four button variables from joystick array
      int buttonUp    = joystick[2];
      int buttonRight = joystick[3];
      int buttonDown  = joystick[4];
      int buttonLeft  = joystick[5];

      // Horn
      if (buttonUp == HIGH){
          digitalWrite(horn_Buzz, LOW);
      }else {
          digitalWrite(horn_Buzz, HIGH);
      }

      // Light front
      if (buttonRight == HIGH){
          digitalWrite(light_Front, LOW);
      }else {
          digitalWrite(light_Front, HIGH);
      }
      
      // Light back
      if (buttonLeft == HIGH){
          digitalWrite(light_Back, LOW);
      }else {
          digitalWrite(light_Back, HIGH);
      }

      if(yAxis > 1100 || yAxis < 0 || xAxis > 1100 || xAxis < 0){
        xAxis = 500;
        yAxis = 500;
      }
        
      // Forward 
      if(yAxis > 550 && xAxis < 550 && xAxis > 470){
         motor1.setSpeed(255);
         motor1.run(BACKWARD);
         
         motor2.setSpeed(255);
         motor2.run(BACKWARD);
         
         motor3.setSpeed(255);
         motor3.run(BACKWARD);
         
         motor4.setSpeed(255);
         motor4.run(BACKWARD);
      }
      
      // Backward
      else if(yAxis < 470 && xAxis < 550 && xAxis > 470){
         motor1.setSpeed(255);
         motor1.run(FORWARD);
         
         motor2.setSpeed(255);
         motor2.run(FORWARD);
         
         motor3.setSpeed(255);
         motor3.run(FORWARD);
         
         motor4.setSpeed(255);
         motor4.run(FORWARD);
      }
  
      // Right
      else if(xAxis > 550 && yAxis < 550 && yAxis > 470){
         motor1.setSpeed(255);
         motor1.run(BACKWARD);
         
         motor2.setSpeed(255);
         motor2.run(BACKWARD);
         
         motor3.setSpeed(255);
         motor3.run(FORWARD);
         
         motor4.setSpeed(255);
         motor4.run(FORWARD);
      }
  
      // Left
      else if(xAxis < 470 && yAxis < 550 && yAxis > 470){
        motor1.setSpeed(255);
        motor1.run(FORWARD);
         
        motor2.setSpeed(255);
        motor2.run(FORWARD);
  
        motor3.setSpeed(255);
        motor3.run(BACKWARD);
         
        motor4.setSpeed(255);
        motor4.run(BACKWARD);
      }
  
      // Forward Right
      else if(xAxis > 550 && yAxis > 550){
         motor1.setSpeed(255);
         motor1.run(BACKWARD);
         
         motor2.setSpeed(255);
         motor2.run(BACKWARD);
  
         motor3.run(RELEASE);

         motor4.run(RELEASE);
      }
  
      // Forward Left
      else if(xAxis < 470 && yAxis > 550){
         motor1.run(RELEASE);

         motor2.run(RELEASE);
  
         motor3.setSpeed(255);
         motor3.run(BACKWARD);
         
         motor4.setSpeed(255);
         motor4.run(BACKWARD);
      }
  
      // Backward Right
      else if(xAxis > 550 && yAxis < 470){
         motor1.setSpeed(255);
         motor1.run(FORWARD);
         
         motor2.setSpeed(255);
         motor2.run(FORWARD);

         motor3.run(RELEASE);

         motor4.run(RELEASE);
      }
  
      // Backward Left
      else if(xAxis < 470 && yAxis < 470){
         motor1.run(RELEASE);

         motor2.run(RELEASE);
         
         motor3.setSpeed(255);
         motor3.run(FORWARD);
         
         motor4.setSpeed(255);
         motor4.run(FORWARD);
      }
  
      // No Move
      else{
        motor1.run(RELEASE);
         
        motor2.run(RELEASE);
  
        motor3.run(RELEASE);
         
        motor4.run(RELEASE);
      } 
  }
}













  
