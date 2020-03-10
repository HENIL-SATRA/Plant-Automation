

String cmd,data_cmd;
String my_SSID        =   "airtel_71AF9B";          //use your wifi SSID
String my_password    =   "3333LNHU3E";             //use your wifi password
String API_key        =   "4C9HP6HVLIKGTY2A";     //use your thigspeak API
String my_temp, my_humid, my_inten, my_moist;
long timeout          =   15000; //milliseconds
int sensor_data       =   0;

int str_len;


void send_cmd(String cmd)
{
  cmd = cmd + '\r' + '\n';
  str_len = cmd.length() + 1; 
  char char_array[str_len];
  cmd.toCharArray(char_array, str_len);
  for(int i = 0; i < str_len; i++)
  {
    Serial1.write(char_array[i]);
  }
  
}

void get_response()
{
  long deadline;
  if (cmd == "AT+RST")
  {
    deadline = millis() + 30000;
  }
  else
  {
    deadline = millis() + timeout;  
  }
  
  while(millis() < deadline)
    {
      if (Serial1.available())
      {
        char ch = Serial1.read();
        Serial.write(ch);
      }
    }
}




 
void init_esp()
{
  Serial1.begin(115200);
  delay(100);
  
  pinMode(10, OUTPUT);             //Reset pin no 10
  pinMode(9, OUTPUT);             //EN pin no 9
  Serial.println("Resetting ESP01");               
  digitalWrite(10, LOW);       
  digitalWrite(9, LOW);
  delay(100);
  digitalWrite(10, HIGH);       
  digitalWrite(9, HIGH);
  delay(30000);
  while (Serial1.available()) 
    {
      Serial.write(Serial1.read());
    }
  Serial.println("Reset complete"); 
  Serial1.flush();
  cmd = "AT";
  send_cmd(cmd);
  get_response();
  cmd = "AT+RST";
  send_cmd(cmd);
  //delay(10000);
  get_response();
  cmd = "AT+CWJAP=\"" + my_SSID + "\",\"" + my_password + '\"';
  send_cmd(cmd);
  //delay(10000);
  get_response();
  cmd = "AT+CIPMUX=0";
  send_cmd(cmd);
  //delay(10000);
  get_response();
  Serial.println("ESP initialization complete"); 
  
    
}
 
void send_data(float temp, float humid, float inten, float moist)
{
  my_temp = String(temp);
  my_humid = String(humid);
  my_inten = String(inten);
  my_moist = String(moist);
  cmd = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80";
  send_cmd(cmd);
  get_response();
  //String str = sensor_data;
  data_cmd = "GET https://api.thingspeak.com/update?api_key=" + API_key +"&field1=" + my_temp +"&field2=" + my_humid +"&field3=" + my_inten +"&field4=" + my_moist;
  cmd = "AT+CIPSEND=" + String(data_cmd.length()+2);
  send_cmd(cmd);
  get_response();
  //data_cmd = "GET https://api.thingspeak.com/update?api_key=" + API_key +"&field1=" + sensor_data;
  send_cmd(data_cmd);
  get_response();
  //cmd = "AT+CIPCLOSE";
  //send_cmd(cmd);
  //get_response();
  //delay(10000);
    
}
