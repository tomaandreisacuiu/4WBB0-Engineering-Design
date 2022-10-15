#include <DHT.h> // Library for DHT22 Temperature and Humidity Sensor

//temp sensor
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT22 Temperature and Humidity Sensor
DHT dhtInside(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
#define DHTPIN1 3
DHT dhtOutside(DHTPIN1, DHTTYPE);

const int capteur_D = 4; // Rain Sensor Connection D0
const int capteur_A = A0; // Rain Sensor Connection A0

//temp sensor
float humInside;  // Humidity Inside the Room
float tempInside; // Temperature Inside
float humOutside;  // Humidity Outside
float tempOutside;  // Temperature Outside
float dewInside; // Dew-Point Inside
float dewOutside;// Dew-Point Inside

int val_analogique; // Rain Sensor Analog Value

void setup()
{
  pinMode(capteur_D, INPUT);
  pinMode(capteur_A, INPUT);
  Serial.begin(9600);
  dhtInside.begin();
  dhtOutside.begin();
}

void loop()
{
  humInside = dhtInside.readHumidity(); // read humidity from sensor
  tempInside = dhtInside.readTemperature(); // read temperature from sensor
  dewInside = (tempOutside - (100 - humOutside) / 5); // calculate dew point

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
  delay(3000);


  // Rain Sensor:
  if (digitalRead(capteur_D) == LOW)
  {
    Serial.println("Digital value : wet"); // Low Output Voltage = Rain
    delay(10);
  }
  else
  {
    Serial.println("Digital value : dry"); // High Output Voltage = Dry
    delay(10);
  }
  val_analogique = analogRead(capteur_A);
  Serial.print("Analog value : ");
  Serial.println(val_analogique); // print analog rain sensor value for testing
  Serial.println("");
  delay(1000);


  // Case Distinction
  float tempMin = 18; // Default Minimum Healthy Room Temperature
  float tempMax = 24; // Default Maximum Healthy Room Temperature
  if (val_analogique > 300) // no rain {
    if ((tempInside >= tempMin && tempInside <= tempMax) || (tempInside < tempMin && tempOutside >= tempMin) || (tempInside > tempMax && tempOutside <= tempMax))
      if (dewOutside < 16.7 && dewOutside < dewInside))
      {
        // dew point is acceptable
        //TODO: Open window
      }
      else {
        //TODO: Close window
      }
  }
