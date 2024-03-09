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
    constexpr uint32_t INTERVAL = 1001;
    constexpr uint32_t INTERVAL2 = 3001;
    constexpr uint32_t INTERVAL3 = 6001;

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
               
        if ((currentTime - lastTime) == (INTERVAL3))
        {
              Serial.print("Ya volveremos a empezar :D");
              Serial.print('\n');
              lastTime = 0;
              task1State = Task1States::INIT;                       
        }
        else if ((currentTime - lastTime) == (INTERVAL2))
        {
            Serial.print("Van 2 segundos");
            Serial.print('\n');
        }
        else if ((currentTime - lastTime) == INTERVAL)
        {            
            Serial.print("Hola");
            Serial.print('\n');               
     
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
