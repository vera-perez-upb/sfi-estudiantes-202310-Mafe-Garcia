void task()
{
    enum class TaskStates
    {
        INIT,
        WAIT_INIT,
        SEND_EVENT
    };
    static TaskStates taskState = TaskStates::INIT;
    float num = 3.8;  // 40 73 33 33
    static uint8_t arr[4] = {0};

    switch (taskState)
    {
        case TaskStates::INIT:
        {
            Serial.begin(115200);
            taskState = TaskStates::WAIT_INIT;
            break;
        }
        case TaskStates::WAIT_INIT:
        {
            if (Serial.available() > 0)
            {
                if (Serial.read() == '1')
                {
                    taskState = TaskStates::SEND_EVENT;
                }
            }
            break;
        }
        case TaskStates::SEND_EVENT:
        {
          memcpy(arr,(uint8_t *)&num,4);
          for(int8_t i = 3; i >= 0; i--){
          Serial.write(arr[i]);
          }          
            break;
        }
        default:
        {
            break;
        }
    }
}

void setup()
{
    task();
}

void loop()
{
    task();
}
