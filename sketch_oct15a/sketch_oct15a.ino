#include <DHT.h>
#include <Servo.h>

// set the DHT Pins
#define DHTPIN 7
#define DHTPIN1 3

// initialize the library with the numbers of the interface pins
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dhtInside(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino
DHT dhtOutside(DHTPIN1, DHTTYPE);

//define servo motor
Servo myservo;

const int rain_sensor_D = 2; // Rain Sensor Connection D0
const int rain_sensor_A = A0; // Rain Sensor Connection A0
const int servo_D = 9;
const int magnet_D = 4;
const int switch_auto_D = 5;
const int switch_open_D = 6;
const int switch_adjust_D=7;
const int button_temp1 = 8;
const int button_temp2 = 10;

//Variables
float humInside;  //Humidity Inside
float tempInside; //Temperature Inside
float humOutside;  //Humidity Outside
float tempOutside; // Temperature Outside
float dewInside; // Dew Point Inside
float dewOutside; // Dew Point Outside
int rainAnalog; // Analog Value of Rain Sensor

float prefferedTemp;

bool isSpinning = false; //servo is spinning
bool isAutomatic = true; //automated process is running (Determined by a switch)
bool isWindowOpen = false; //window is closed or open
bool isSwitchOpen = false; // switch for closing and opening window manually
bool isAdjustTemp = false; // system is in "Adjust preferred temperature" Mode

void setup()
{
  pinMode(rain_sensor_D, INPUT); // Set rain sensor D0 pin as INPUT
  pinMode(rain_sensor_A, INPUT); // Set rain sensor A0 pin as INPUT
  pinMode(servo_D, INPUT); // Set servo pin as INPUT
  pinMode(magnet_D, INPUT_PULLUP);
  pinMode(switch_auto_D, INPUT_PULLUP);
  pinMode(switch_open_D, INPUT_PULLUP);
  pinMode(switch_adjust_D, INPUT_PULLUP);
  pinMode(button_temp1, INPUT_PULLUP);
  pinMode(button_temp2, INPUT_PULLUP);


  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  delay(500);//Delay to let system boot

  dhtInside.begin();
  dhtOutside.begin();

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  delay(1000);//Wait before accessing Sensor
  isAutomatic = false;
  isSwitchOpen = false;
  isWindowOpen = true;


}

void loop() {

  isAutomatic = (!digitalRead(switch_auto_D));
  isAdjustTemp = (!digitalRead(switch_adjust_D));
  if (isAdjustTemp == true) {
    prefferedTemp=AdjustTemp(prefferedTemp);
  }
  else {

    if (isAutomatic == false) {
      isSwitchOpen = digitalRead(switch_open_D);
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
    delay(1000); //Wait 3 seconds before accessing sensor again.

  }
}

void OpenWindow() {
  if (isWindowOpen == false) {
    myservo.write(0); // start rotating to open window full-speed
    delay(3000);// takes 3 seconds to open window
    myservo.write(90); //stop rotating
    isWindowOpen = true;
  }

}

void CloseWindow() {
  if (isWindowOpen == true) {
    myservo.write(180); // start rotating to close window full-speed
    delay(100);

    while (digitalRead(magnet_D) == HIGH) {
      delay(100); // wait until magnetic connectors are close
    }

    myservo.write(90); // stop rotating
    isWindowOpen = false;


  }
}

float AdjustTemp(float temp){
    isAdjustTemp = (!digitalRead(switch_adjust_D));
  while(isAdjustTemp==true){
    if(!digitalRead(button_temp1)==HIGH){
      temp-=0.5;
      delay(500);
    }
    if(!digitalRead(button_temp2)==HIGH){
      temp+=0.5;
      delay(500);
    }
    return temp;
  }
}


void test()
{
  // Temperature and Humidity sensor inside
  humInside = dhtInside.readHumidity(); // read humidity from sensor
  tempInside = dhtInside.readTemperature(); // read temperature from sensor
  dewInside = (tempInside - (100 - humInside) / 5); // Calculate dew point

  humOutside = dhtOutside.readHumidity();
  tempOutside = dhtOutside.readTemperature();
  dewOutside = (tempOutside - (100 - humOutside) / 5);

  //Print temp and humidity values to serial monitor
  Serial.println("Humidity: ");
  Serial.println(humInside);
  Serial.println(humOutside);
  Serial.println();
  Serial.println("Temp: ");
  Serial.println(tempInside);
  Serial.println(tempOutside);
  Serial.println();


  if (digitalRead(rain_sensor_D) == LOW)
  {
    // it is raining
    Serial.println("Digital value : wet");
    delay(10);
  }
  else
  {
    // it is not raining
    Serial.println("Digital value : dry");
    delay(10);
  }

  // Print rain sensor value to serial monitor
  rainAnalog = analogRead(rain_sensor_A);
  Serial.print("Analog value : ");
  Serial.println(rainAnalog);
  Serial.println("");
  delay(100);

  // Case Distinction
  float tempMin = 18; // minimum healthy room temperature
  float tempMax = 24; // maximum healthy room temperature
  if (digitalRead(rain_sensor_D) == HIGH) {
    if ((tempInside >= tempMin && tempInside <= tempMax) ||
        (tempInside < tempMin && tempOutside >= tempMin) ||
        (tempInside > tempMax && tempOutside <= tempMax)) {
      // keeping a healthy room temperature
      if (dewOutside < 16.7 && dewOutside < dewInside)
      {
        // keeping healthy humidity levels
        OpenWindow();
      }
    }
  }
  else {
    CloseWindow();
  }




}
