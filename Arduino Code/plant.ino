//::::::::Temperature and humidity:::::::::::::::
 #include <dht.h>
 dht DHT;
 
//::::::::SOIL MOISTURE::::::::::::::::::::::::::
 int MoistureGotvalue;
 float value;
 float MoistureReadvalue;
 String DATA;
 
//::::::::LCD DISPLAY:::::::::::::::::::::::::::::
   #include <LiquidCrystal.h>
   LiquidCrystal LCD{10,9,5,4,3,2};
   int myCounter=0;
   #define dht_apin A0 // Analog Pin sensor is connected to
   
//:::::::::EXTRA::::::::::::::::::::::::::::::::::
   int waterpump = 11;
   float l;
   float p;
   float k;
   int buzzer=12;

int analogPin = A2;
int value1;
int blueLED=8;
float intensity;
float show;
//#include <IRremote.h>
//int IRpin = 11;  // pin for the IR sensor
//int LED = 13;    // LED pin  
//IRrecv irrecv(IRpin);
//decode_results results;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setup(){ 
  Serial.begin(115200);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  pinMode(A0,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(blueLED,OUTPUT);
  pinMode(A2,INPUT); 
  pinMode(waterpump,OUTPUT);
  LCD.begin(16,2);
  MoistureGotvalue = analogRead(A1);
  value=(100./1023.)*MoistureGotvalue ;
  MoistureReadvalue=100 - value ;
if(MoistureReadvalue>10){digitalWrite(waterpump,LOW);}
delay(100);
//  irrecv.enableIRIn();         
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
void loop(){
  photo();
  soil();
  read1();
}

//:::::::::PHOTORESISTOR:::::::::::::::::::::
void photo(){
  value1 = analogRead(analogPin); 
  intensity=(255./1023.)*value1;
  analogWrite(blueLED,intensity);
  show=(10./1023.)*value1;
  }




//::::::::SOIL MOISTURE::::::::::::::::::::::::::   
void soil(){
  MoistureGotvalue = analogRead(A1);
  value=(100./1023.)*MoistureGotvalue ;
  MoistureReadvalue=100 - value ;
  if(MoistureReadvalue<=10){tone(buzzer,250);}
  if(MoistureReadvalue>=9){noTone(buzzer);}
  if(MoistureReadvalue<=9){digitalWrite(waterpump,HIGH);}
  if(MoistureReadvalue>10){digitalWrite(waterpump,LOW);}
}

void read1(){
  
  Serial.print("your moisture value is = ");
  Serial.print(MoistureReadvalue);
  Serial.println(" %");
   delay(2000);
   
  Serial.print("sunlight value is =  ");
  Serial.print(show);
   Serial.println(" out of 10 ");
   delay(2000);

 //:::::::Temperature and humidity:::::::::::::::
   DHT.read11(dht_apin);
  Serial.print("Current humidity =  ");
  Serial.print(DHT.humidity);
  Serial.println("%  ");
  delay(1000);
  Serial.print("temperature =  ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");        
  LCD.setCursor(0,0);
  LCD.print("current humidity");               
  LCD.setCursor(0,1);
  LCD.print(DHT.humidity); 
  LCD.setCursor(7,1);
  LCD.print("% ");  
  delay(500);
  LCD.setCursor(0,0);
  LCD.print("                    ");
  LCD.setCursor(0,1);
  LCD.print("                    ");
  LCD.setCursor(0,0);
  LCD.print("temperature = ");
  LCD.setCursor(0,1);
  LCD.print(DHT.temperature);
  LCD.setCursor(5,1);
  LCD.print("C ");  
 delay(3000);

 Serial.println("    ");
}
//::::::::EXTRA::::::::::::::::::::::::::::::::



// put your main code here, to run repeatedly:
//l=analogRead(A3);
////Serial.println(a);
//p=(10./1023.)*l;
//k=10.-p;
//Serial.print("your light value is");
//Serial.println(p);
//Serial.println( );
//Serial.println( );
//delay(1000);

//if (irrecv.decode(&results)) {
//    Serial.println(results.value);
//    irrecv.resume(); 
//       if(results.value==3772793023) // Your ON button value                                       
//  {
//            digitalWrite(waterpump,HIGH);
//  }  else if(results.value == 3772783078 ) // Your OFF button value 
// {
//             digitalWrite(waterpump,LOW);
//  }
//                                }
