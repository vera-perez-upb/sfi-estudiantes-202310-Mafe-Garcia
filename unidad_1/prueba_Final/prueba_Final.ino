void setup() 
{
  task1();
}

void loop() 
{
 task1();
}

void task1()
{
  enum class Task1States
  {
    INIT,
    COMP
  };

  static Task1States task1State=Task1States::INIT;
  static char contra[5];
  static uint8_t dataCounter=0;

  switch (task1State)
  {
    case Task1States::INIT:
    {
      Serial.begin(115200);
      task1State=Task1States::COMP;
      break;
    }
    case Task1States::COMP:
    {
      if (Serial.available()>0)
      {
        contra[dataCounter]=Serial.read();
        dataCounter++;
        if(dataCounter==5)
        {
          string result=" ";
          compareData(contra, dataCounter,result);
          dataCounter=0;
          Serial.print("result: ");
          Serial.print(result);
          Serial.print('\n');
        }
      }
    }
  }
}
static void compareData(char *pass, uint8_t size, string *res)
{
  char compare[5]={'C','1','2','3','4'};
  bool same=true;

  while(same=true)
  {
    for(int i=0;i<size;i++)
    {
      
    }
  }
}
