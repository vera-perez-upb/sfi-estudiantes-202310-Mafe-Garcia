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
    WAIT_DATA
  };
  static Task1States task1State = Task1States::INIT;
  static uint32_t data[32];
  static uint32_t dataCounter=0;

  switch (task1State)
  {
    case Task1States::INIT:
    {
      Serial.begin(115200);
      task1State=Task1States::WAIT_DATA;
      break;
    }
    case Task1States::WAIT_DATA:
    {
      while (dataCounter<32)
      {
        if (Serial.available()>0)
        {
          data[dataCounter]=Serial.read();
          dataCounter++;          
        }
      }
      if (dataCounter==32)
      {
        Serial.print("Se ha llegado a los 32 registros, que son los siguientes:");
        for (int i=0;i<32;i++)
        {
          Serial.print("Registro");
          Serial.print(i+1);
          Serial.print(":");
          Serial.print(data[i]-0x30);
          Serial.print('\n');
        }
        dataCounter=0;
      }
    }
  }
}
