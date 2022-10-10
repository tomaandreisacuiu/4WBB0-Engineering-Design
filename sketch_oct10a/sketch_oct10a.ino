#include <DHT.h>

//temp sensor
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dhtInside(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
#define DHTPIN1 3
DHT dhtOutside(DHTPIN1, DHTTYPE);

const int capteur_D = 4;
const int capteur_A = A0;

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
}

void loop()
{
  humInside = dhtInside.readHumidity();
  tempInside = dhtInside.readTemperature();
  float dewInside = (tempOutside - (100 - humOutside) / 5);

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
}
