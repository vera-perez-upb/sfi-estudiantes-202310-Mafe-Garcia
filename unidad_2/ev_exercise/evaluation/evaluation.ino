void task()
{
    enum class TaskStates
    {
        INIT,
        WAIT_INIT,
        SEND_EVENT
    };
    static TaskStates taskState = TaskStates::INIT;
    static uint32_t previous = 0;
    static uint32_t toPrint = 3;

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
                    previous = 0; // Force to send the first value immediately
                    taskState = TaskStates::SEND_EVENT;
                }
            }
            break;
        }
        case TaskStates::SEND_EVENT:
        {
            uint32_t current = millis();
            if ((current - previous) > 3000)
            {
                previous = current;
                Serial.print(toPrint);
                toPrint=toPrint+3;
            }
            if (Serial.available() > 0)
            {
                if (Serial.read() == '2')
                {
                    taskState = TaskStates::WAIT_INIT;
                }
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
