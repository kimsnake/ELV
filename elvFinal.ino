#define floor1Btn  11
#define floor2Btn  12
#define floor3Btn  13

#define floor1Led  8
#define floor2Led  9
#define floor3Led  10

#define ledStep7  7
#define ledStep6  6
#define ledStep5  5
#define ledStep4  4
#define ledStep3  3
#define ledStep2  2
#define ledStep1  A0

int elvFloor = 1;
int step = 1;
int targetStep = 1;

bool floorFlag[4] = {NULL, false, false, false};

bool beforeFloorBtn[4] = {NULL,false, false, false};

unsigned long lastCallTimeFloor1 = 0;
unsigned long lastCallTimeFloor2 = 0;
unsigned long lastCallTimeFloor3 = 0;

unsigned long previousMillis = 0;
const long interval = 1000;  

bool goal = true;

int pushBtn();

int findNextTargetStep();

int elvLedOn(int step);
int elvLedOff(int step);

int floorLedOn(int floor);
int floorLedOff(int floor);

int checkFloorFlag(int argFloor);

int pushBtnfloor();

bool checkGaol();

const int ledStep[8] = {0,ledStep1,ledStep2,ledStep3,ledStep4,ledStep5,ledStep6,ledStep7};

const int floorLed[4] = {0, floor1Led, floor2Led, floor3Led};

const int floorBtn[4] = {0, floor1Btn, floor2Btn, floor3Btn};

void setup()
{
  for(int i = 1; i < 8; i++)
  {
    pinMode(ledStep[i], OUTPUT);
  }    

  for(int i = 1; i < 4; i++)
  {
    pinMode(floorLed[i], OUTPUT);
  }    

  for(int i = 1; i < 4; i++)
  {
    pinMode(floorBtn[i], INPUT);
  }    
  
  digitalWrite(ledStep[1], HIGH);
  
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis = millis();
  pushBtn();
  
  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    if(goal == false)
    {
      targetStep = findNextTargetStep();
    }

    if(targetStep > step)
    {
      elvLedOff(step);
      step++;
      elvLedOn(step);

    }
    else if(targetStep < step)
    {
      elvLedOff(step);
      step--;
      elvLedOn(step);    
    }
    else
    {
      //NONE
    }


    if(step % 3 == 1)
    {
      if(step == 1)
      {
        elvFloor = 1;
      } 
      else if(step == 4)
      {
        elvFloor = 2;
      }     
      else if(step == 7)
      {
        elvFloor = 3;
      }
      else
      {
        //NONE
      } 

      checkFloorFlag(elvFloor);
    }
    
    Serial.print(step);
    Serial.print(" ");
    Serial.print(targetStep);
    Serial.print(" ");
    Serial.print(elvFloor);
    Serial.print(" ");
    Serial.print(goal);
    Serial.print(" ");
    Serial.print(floorFlag[1]?" 1F TRUE":" 1F FALSE");
    Serial.print(" ");
    Serial.print(floorFlag[2]?" 2F TRUE":" 2F FALSE");
    Serial.print(" ");
    Serial.print(floorFlag[3]?" 3F TRUE":" 3F FALSE");
    Serial.print(" ");
    Serial.print(beforeFloorBtn[1]?" 1F bTRUE":" 1F bFALSE");
    Serial.print(" ");
    Serial.print(beforeFloorBtn[2]?" 2F bTRUE":" 2F bFALSE");
    Serial.print(" ");
    Serial.println(beforeFloorBtn[3]?" 3F bTRUE":" 3F bFALSE");
  
  } 
}


int findNextTargetStep()
{
  int returnStep = 0;
  
  if(elvFloor == 1)
  {
    if(floorFlag[2] == true && floorFlag[3] == true)
    {
      if(lastCallTimeFloor2 < lastCallTimeFloor3)
      {
        returnStep = 4;
      }
      else
      {
        returnStep = 7;
      }
    }
    else if(floorFlag[2] == true) returnStep = 4;
    else if(floorFlag[3] == true) returnStep = 7;
    else returnStep = 1;    
  }
  else if(elvFloor == 2)
  {	
    if(floorFlag[1] == true && floorFlag[3] == true)
    {
      if(lastCallTimeFloor1 < lastCallTimeFloor3)
      {
        returnStep = 1;
      }
      else
      {
        returnStep = 7;
      }
    }
    else if(floorFlag[1] == true) returnStep = 1;
    else if(floorFlag[3] == true) returnStep = 7;
    else returnStep = 4; 
  }
  else if(elvFloor == 3)
  {
    if(floorFlag[2] == true && floorFlag[1] == true)
    {
      if(lastCallTimeFloor2 < lastCallTimeFloor1)
      {
        returnStep = 4;
      }
      else
      {
        returnStep = 1;
      }
    }
  	else if(floorFlag[2] == true) returnStep = 4;
    else if(floorFlag[1] == true) returnStep = 1;
    else returnStep = 7; 
  }
    
  return returnStep;
}

int pushBtn()
{
  if(elvFloor == 1)
  {
    if(digitalRead(floorBtn[1]) == true && beforeFloorBtn[1] == false && step != 1)
    {
      beforeFloorBtn[1] = digitalRead(floorBtn[1]);
      if (floorFlag[1] == false)
      {
        lastCallTimeFloor1 = millis();
      	floorFlag[1] = true;
      	floorLedOn(1);         
        goal = false;       
      }
      else
      {
      	floorFlag[1] = false;
      	floorLedOff(1);        
        goal = checkGaol(); 
      } 
    }

    if(digitalRead(floorBtn[2]) == true && beforeFloorBtn[2] == false)
    {
      beforeFloorBtn[2] = digitalRead(floorBtn[2]);
      if (floorFlag[2] == false)
      {
        lastCallTimeFloor2 = millis();
      	floorFlag[2] = true;
      	floorLedOn(2);      
        goal = false; 
      }
      else
      {
      	floorFlag[2] = false;
      	floorLedOff(2);        
        goal = checkGaol(); 
      }      
    }

    if(digitalRead(floorBtn[3]) == true && beforeFloorBtn[3] == false)
    {
      beforeFloorBtn[3] = digitalRead(floorBtn[3]);
      if (floorFlag[3] == false)
      {
        lastCallTimeFloor3 = millis();
      	floorFlag[3] = true;
      	floorLedOn(3);              
        goal = false;
      }
      else
      {
      	floorFlag[3] = false;
      	floorLedOff(3);       
        goal = checkGaol(); 
      }
    }
  }  

  else if(elvFloor == 2)
  {
    if(digitalRead(floorBtn[1]) == true && beforeFloorBtn[1] == false)
    {
      beforeFloorBtn[1] = digitalRead(floorBtn[1]);
      if (floorFlag[1] == false)
      {
        lastCallTimeFloor1 = millis();
      	floorFlag[1] = true;
      	floorLedOn(1);         
        goal = false;       
      }
      else
      {
      	floorFlag[1] = false;
      	floorLedOff(1);        
        goal = checkGaol(); 
      }      
    }

    if(digitalRead(floorBtn[2]) == true && beforeFloorBtn[2] == false && step != 4)
    {
      beforeFloorBtn[2] = digitalRead(floorBtn[2]);
      if (floorFlag[2] == false)
      {
        lastCallTimeFloor2 = millis();
      	floorFlag[2] = true;
      	floorLedOn(2);      
        goal = false;  
      }
      else
      {
      	floorFlag[2] = false;
      	floorLedOff(2);        
        goal = checkGaol(); 
      } 
    }

    if(digitalRead(floorBtn[3]) == true && beforeFloorBtn[3] == false)
    {
      beforeFloorBtn[3] = digitalRead(floorBtn[3]);
      if (floorFlag[3] == false)
      {
        lastCallTimeFloor3 = millis();
      	floorFlag[3] = true;
      	floorLedOn(3);       
        goal = false; 
      }
      else
      {
      	floorFlag[3] = false;
      	floorLedOff(3); 
        goal = checkGaol();        
      }      
    }
  }

  else if(elvFloor == 3)
  {
    if(digitalRead(floorBtn[1]) == true && beforeFloorBtn[1] == false)
    {
      beforeFloorBtn[1] = digitalRead(floorBtn[1]);
      if (floorFlag[1] == false)
      {
        lastCallTimeFloor1 = millis();
      	floorFlag[1] = true;
      	floorLedOn(1);   
        goal = false;     
      }
      else
      {
      	floorFlag[1] = false;
      	floorLedOff(1);     
        goal = checkGaol();    
      }      
    }

    if(digitalRead(floorBtn[2]) == true && beforeFloorBtn[2] == false)
    {
      beforeFloorBtn[2] = digitalRead(floorBtn[2]);
      if (floorFlag[2] == false)
      {
        lastCallTimeFloor2 = millis();
      	floorFlag[2] = true;
      	floorLedOn(2);      
        goal = false;  
      }
      else
      {
      	floorFlag[2] = false;
      	floorLedOff(2);        
        goal = checkGaol(); 
      }      
    }
    
    if(digitalRead(floorBtn[3]) == true && beforeFloorBtn[3] == false && step != 7)
    {
      beforeFloorBtn[3] = digitalRead(floorBtn[3]);
      if (floorFlag[3] == false)
      {
        lastCallTimeFloor3 = millis();
        floorFlag[3] = true;
        floorLedOn(3);       
        goal = false; 
      }
      else
      {
        floorFlag[3] = false;
        floorLedOff(3); 
        goal = checkGaol();        
      } 
    }
  } 

  else {} //NONE
  
  if(digitalRead(floorBtn[1]) == false && beforeFloorBtn[1] == true)
  {
    beforeFloorBtn[1] = digitalRead(floorBtn[1]);
  }
  if(digitalRead(floorBtn[2]) == false && beforeFloorBtn[2] == true)
  {
    beforeFloorBtn[2] = digitalRead(floorBtn[2]);
  }
  if(digitalRead(floorBtn[3]) == false && beforeFloorBtn[3] == true)
  {
    beforeFloorBtn[3] = digitalRead(floorBtn[3]);
  }
  
  return 0;
}


int elvLedOn(int step)
{
  digitalWrite(ledStep[step], HIGH);  
  return 0;
}

int elvLedOff(int step)
{
  digitalWrite(ledStep[step], LOW);  
  return 0;
}

int floorLedOn(int argFloor)
{
  digitalWrite(floorLed[argFloor], HIGH);  
  return 0;
}

int floorLedOff(int argFloor)
{
  digitalWrite(floorLed[argFloor], LOW);  
  return 0;
}

int checkFloorFlag(int argFloor)
{
  floorFlag[argFloor] = false;
  floorLedOff(argFloor);
  return 0;
}

bool checkGaol()
{
  return !(floorFlag[1]||floorFlag[2]||floorFlag[3]);
}