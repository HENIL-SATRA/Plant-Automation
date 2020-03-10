#include <dht.h>
#include <LiquidCrystal.h>
LiquidCrystal LCD{10,9,5,4,3,2};

#define OFF                 LOW
#define ON                  HIGH
#define dht_apin            A0
#define moisture_sensor     A1
#define photo_sensor        A2
#define buzzer              12
#define waterpump           11
#define blueLED             8
#define moisture_limit      15

int counter = 0;
float moisture, temperature, intensity, humidity;

dht DHT;
int myCounter=0;

void init1();
void get_moisture();
void get_temp_humid();
void get_photo_intensity();




void setup() 
{
  init1();
  init_esp();
}

void loop() 
{
  get_moisture();
  get_temp_humid();
  get_photo_intensity();
  Serial.print("moisture = ");
  Serial.print(moisture);
  Serial.print(" temperature = ");
  Serial.print(temperature);
  Serial.print(" intensity = ");
  Serial.print(intensity);
  Serial.print(" humidity = ");
  Serial.println(humidity);
  counter++;
  if (counter == 10)
  {
    send_data(moisture, temperature, intensity, humidity);
    counter = 0;
  }
  delay(2000);
}





void init1()
{
  Serial.begin(115200);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  pinMode(dht_apin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(photo_sensor, INPUT);
  pinMode(moisture_sensor, INPUT); 
  pinMode(waterpump, OUTPUT);
  LCD.begin(16,2);
  noTone(buzzer);
  digitalWrite(waterpump,OFF);
}

void get_moisture()
  {
    moisture = analogRead(moisture_sensor);
    moisture = 100 - (100.0/1023.0)*moisture;
    //Serial.print("Moisture = ");
    //Serial.println(moisture);
    
    if(moisture < 9)
      {
        tone(buzzer, 250);
        digitalWrite(waterpump,ON);
        while(1)
        {
          moisture = analogRead(moisture_sensor);
          moisture = 100 - (100.0/1023.0)*moisture;
          if(moisture >= moisture_limit)
          {
            noTone(buzzer);
            digitalWrite(waterpump,OFF);
            break;
          }
        }
      }    
  }


void get_temp_humid()
{
  DHT.read11(dht_apin);
  humidity = DHT.humidity;
  temperature = DHT.temperature; 
}

void get_photo_intensity()
{ 
  int val = analogRead(photo_sensor)/4;
  //Serial.print("val = ");
  //Serial.println((255-val));
  analogWrite(blueLED, (255-val));
  intensity = float(val/25.5);
  //Serial.print("intensity = ");
  //Serial.println(intensity);
}
