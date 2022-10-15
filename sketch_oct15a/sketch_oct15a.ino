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

bool isSpinning = false; //servo is spinning
bool isAutomatic = true; //automated process is running (Determined by a switch)
bool isWindowOpen = false; //window is closed or open
bool isSwitchOpen = false; // switch for closing and opening window manually

void setup()
{
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);
  Serial.begin(9600);
  dhtInside.begin();
  dhtOutside.begin();

  pinMode(11, INPUT);

  //myservo.write(pos); // put it before the attach() so it goes straight to that position
  //myservo.writeMicroseconds(1300);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object


  /*
    myservo.write(45);
    delay(4500);
    myservo.write(90);
    delay(1000);
    myservo.write(135);
    delay(4500);
    myservo.write(90);
  */
}

void loop() {
  //isAutomatic=digitalRead(); //TBD
  isAutomatic = true;
  if (isAutomatic == false) {
    //isSwitchOn=digitalRead(); //TBD

    if (isSwitchOpen == true) {
      OpenWindow();
    }
    else if (isSwitchOpen == false) {
      CloseWindow();
    }
  }
  else {
    test();
  }
}

void OpenWindow() {
  if (isWindowOpen == false) {
    myservo.write(0);
    delay(3000);
    myservo.write(90);
    isWindowOpen = true;
  }

}

void CloseWindow() {
  if (isWindowOpen == true) {
    myservo.write(180);
    delay(100);
    while (digitalRead(11) == LOW) {
      delay(10);
    }

    myservo.write(90);
    isWindowOpen = false;


  }
}


void test()
{

  humInside = dhtInside.readHumidity();
  tempInside = dhtInside.readTemperature();
float dewInside = (tempInside - (100 - humInside) / 5);
  humOutside = dhtOutside.readHumidity();
  tempOutside = dhtOutside.readTemperature();
float dewOutside = (tempOutside - (100 - humOutside) / 5);
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



  if (digitalRead(capteur_D) == LOW)
  {
    Serial.println("Digital value : wet");
    delay(10);
  }
  else
  {
    Serial.println("Digital value : dry");
    delay(10);
  }
  val_analogique = analogRead(capteur_A);
  Serial.print("Analog value : ");
  Serial.println(val_analogique);
  Serial.println("");
  delay(1000);

    


 
    float tempMin=18;
    float tempMax=24;
    if(digitalRead(capteur_D) == HIGH) {
    if((tempInside>=tempMin && tempInside<=tempMax) || (tempInside<tempMin && tempOutside>=tempMin) || (tempInside>tempMax && tempOutside<=tempMax))
      if(dewOutside<16.7 && dewOutside<dewInside)
      {
        OpenWindow();
      }}
      else{
        CloseWindow();
      }
 



}
