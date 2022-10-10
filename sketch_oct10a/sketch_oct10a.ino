#include <DHT.h>
#include <Servo.h>

//temp sensor
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dhtInside(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
#define DHTPIN1 3
DHT dhtOutside(DHTPIN1, DHTTYPE);
//define servo motor
Servo myservo;

const int capteur_D = 4;
const int capteur_A = A0;

int pos = 0;    // variable to store the servo position

//temp sensor
int chk;
float humInside;  //Stores humidity value
float tempInside; //Stores temperature value
float humOutside;  //Stores humidity value
float tempOutside; 

int val_analogique;

void setup()
{
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);
  Serial.begin(9600);
  dhtInside.begin();
  dhtOutside.begin();

  //myservo.write(pos); // put it before the attach() so it goes straight to that position
  //myservo.writeMicroseconds(1300); 

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
  myservo.write(45); 
  delay(4500);
  myservo.write(90);
  delay(1000);
  myservo.write(135);
  delay(4500);
  myservo.write(90);

}

void loop()
{

  humInside = dhtInside.readHumidity();
  tempInside = dhtInside.readTemperature();

  humOutside = dhtOutside.readHumidity();
  tempOutside = dhtOutside.readTemperature();
  /*
  //Print temp and humidity values to serial monitor
  Serial.println("Humidity: ");
  Serial.println(humInside);
  Serial.println(humOutside);
  Serial.println();
  Serial.println("Temp: ");
  Serial.println(tempInside);
  Serial.println(tempOutside);
  Serial.println();
  delay(3000);
  */

  /*  
  if(digitalRead(capteur_D) == LOW) 
    {
      Serial.println("Digital value : wet"); 
      delay(10); 
    }
  else
    {
      Serial.println("Digital value : dry");
      delay(10); 
    }
  val_analogique=analogRead(capteur_A); 
  Serial.print("Analog value : ");
  Serial.println(val_analogique); 
  Serial.println("");
  delay(1000);
  */

  /*
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */  

  //myservo.write(0);
  //delay(3000);
  /*
  delay(3000);
  myservo.write(90);
  delay(3000);
  myservo.write(180);
  delay(3000);
  */

  //myservo.writeMicroseconds(1300); 
  //myservo.detach();
  //delay(10000);

  /*
  float tempMin=18;
  float tempMax=24;
  int rainSensor=500;
  if (rainSeonsor>300){
    if((tempInside>=tempMin && tempInside<=tempMax) || (tempInside<tempMin && tempOutside>=tempMin) || (tempInside>tempMax && tempOutside<=tempMax))
      if(dewOutside<16.7 && dewOutside<dewInside))
      {
        //TODO: Open window
      }
      else{
        //TODO: Close window
      }
     */

   
}

