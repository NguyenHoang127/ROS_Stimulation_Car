#define on 9
#define off 8
#define increse 10
#define decrease 11
#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 7
#define ON_button 12

//---------------------------------------------------------------------------------------------------------------------------------------------------------

int Car_State = 0;
int Car_Level = 1;
int bientroX = A0 ; 
int bientroY = A1 ;

char Value_X[4];
char Value_Y[4];
byte state = 0, state1 = 0;

//----------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() 
{
  pinMode(on, INPUT);
  pinMode(off,INPUT);
  pinMode(increse, INPUT);
  pinMode(decrease, INPUT);
  pinMode(ON_button, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(115200); // Default communication rate of the Bluetooth module
}
void(* resetFunc) (void) = 0;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
char* Number_to_Char(uint16_t num,char Chuoi[])
{
    uint8_t count = 1;
    uint16_t n = num; 
    
    while(n/10)       
    {
        count++;      //1234-123-12-1
        n = n/10;
    }

    for(int i = 0;i<4;i++)
    {
        Chuoi[i] = ((char)((num%10)+48));
        num = num/10;
    }

    return Chuoi;
}

void Send_Data4(char Chuoi[])
{
  for(int i=3;i>=0;i--)
    {
      Serial.print(Chuoi[i]);
    }
}

void Check_state()
{
  if(digitalRead(on) == HIGH)
  {
    while(digitalRead(on) == HIGH) {}
    Car_State = 1;
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if(digitalRead(off) == HIGH)
  {
    while(digitalRead(off) == HIGH) {}
    Car_State = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void Level_state()
{
  if(digitalRead(increse) == HIGH)
  {
    while(digitalRead(increse) == HIGH) {}
    Car_Level=Car_Level+1;
    if(Car_Level>4){Car_Level=4;}
  }

  if(digitalRead(decrease) == HIGH)
  {
    while(digitalRead(decrease) == HIGH) {}
    Car_Level=Car_Level-1;
    if(Car_Level<1){Car_Level=1;}
  }
}

void Led_state(int Level)
{
  switch(Level)
  {
    case 1:
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    break;
    case 2:
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    break;
    case 3:
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    break;
    case 4:
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    break;
   
  } 
}

void loop() 
{
  bool button_on = 0;
  button_on = digitalRead(ON_button);
  if(button_on == 1 && state == 0)  state = 1;
  if(button_on == 0 && state == 1)  state = 2;
  while(state == 2){
  Serial.print((char)(23));
  
    Check_state();
    Level_state();
    Led_state(Car_Level);
  //  Serial.println(Car_Level);
    int x = analogRead(bientroX);  // doc gia tri cua truc X
    int y = analogRead(bientroY);  // doc gia tri cua truc Y
    
    Serial.print((char)(Car_State+48));
    Serial.print((char)(Car_Level+48));
  //  Serial.print("State:   ");
  
    Send_Data4(Number_to_Char(x,Value_X));
    //Serial.print(" Gia Tri X");
  
    Send_Data4(Number_to_Char(y,Value_Y));
    Serial.println("");
  
    delay(10);
    button_on = digitalRead(ON_button);
    if(button_on == 1)  state1 = 1;
    if(button_on == 0 && state1 == 1)  resetFunc();

  }
}
