void task1()
{
    // Definición de estados y variable de estado
    enum class Task1States
    {
        INIT,
        WAIT_TIMEOUT
    };
    static Task1States task1State = Task1States::INIT;

    // Definición de variables static (conservan su valor entre llamadas a task1)
    static uint32_t lastTime = 0;

    // Constantes
    constexpr uint32_t INTERVAL = 1000;

    // MÁQUINA de ESTADOS
    switch (task1State)
    {
    case Task1States::INIT:
    {
        // Acciones:
        Serial.begin(115200);

        // Garantiza los valores iniciales para el siguiente estado.
        lastTime = millis();
        task1State = Task1States::WAIT_TIMEOUT;


        break;
    }
    case Task1States::WAIT_TIMEOUT:
    {
        uint32_t currentTime = millis();

        // Evento
        if ((currentTime - lastTime) >= INTERVAL)
        {
            // Acciones:
            lastTime = currentTime;
            Serial.print("Hola");
            Serial.print('\n');
            INTERVAL = 2000;

            if ((currentTime - lastTime) >= INTERVAL)
            {
            // Acciones:
            lastTime = currentTime;
            Serial.print("Van 2 segundos");
            Serial.print('\n');
                        
                        if ((currentTime - lastTime) >= INTERVAL)
                {
                  // Acciones:
                 lastTime = currentTime;
                 Serial.print("Ya volveremos a empezar :D");
                 Serial.print('\n');            
                }

            }

            task1State = Task1States::INIT;
        }
        
        break;
    }
    default:
    {
        Serial.println("Error");
    }
    }
}

void setup()
{
    task1();
}

void loop()
{
    task1();
}
