/**
  ******************************************************************************
  * @file    Main.c
  * @author  Muhammad Shahzad
  * @version V1.0
  * @date    12-April-2017
  * @brief   Main function which run all function from this file
  ******************************************************************************
  */
char recv_data[150];
int Relay_2 = 6;

void (*reset_function)(void)=0;
int reset_cnt=0;
#define reset_eth_pin A3
#define config_eth_pin A4
/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup(void)
{

  //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
 Initlization();
  
  Serial.begin(9600);
  Serial.println("Barrier V1.0   itzshahzad@gmail.com");Serial.print("Time:");
  Serial.print(__TIME__);Serial.print(" Date:");Serial.println(__DATE__);
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
  --------------------------------------------------------------------------------------*/
void loop(void)
{
  static char cnt=0, heart_beat;
  static int ledcnt;
  reset_cnt=0;
  ledcnt++;
  if(ledcnt> 500){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    ledcnt=0;
    heart_beat++;
  }
  delay(1);
  if(heart_beat >30){
    heart_beat=0;
    Serial.print("T1$");
  }
  while(Serial.available()){
    recv_data[cnt++] =Serial.read(); 
    if(cnt>30)break;
      
  }
  if(cnt>1){
    if(strstr(recv_data,"B1$")!=0 ){
      
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.print(recv_data);
      digitalWrite(Relay_2, HIGH); // Turn ON Relay
      delay(2500);
      digitalWrite(Relay_2, LOW); // Turn OFF Relay
      
      cnt =0;      
      GSM_str_clear();
    }
    if(cnt>30)cnt=0;
  }
 }


  /***************************************************************************/
 /***************************************************************************/
 
 void GSM_str_clear(void){
   unsigned int i;   
   for(i=0;i<150;i++)
     recv_data[i]=0;     
 }
