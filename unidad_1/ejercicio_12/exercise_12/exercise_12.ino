void task1()
{
    enum class Task1States    
    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;

    switch (task1State)
    {
    case Task1States::INIT:
    {
        Serial.begin(115200);
        task1State = Task1States::WAIT_DATA;
        break;
    }

    case Task1States::WAIT_DATA:
    {
        // evento 1:        // Ha llegado al menos un dato por el puerto serial?        
        if (Serial.available() > 0)
        {
            // DEBES leer ese dato, sino se acumula y el buffer de recepción            
            // del serial se llenará.            
            Serial.read();
            uint32_t var = 0;
            // Almacena en pvar la dirección de var.            
            uint32_t *pvar = &var;
            // Envía por el serial el contenido de var usando            
            // el apuntador pvar.            
            Serial.print("var content: ");
            Serial.print(*pvar);
            Serial.print('\n');
            // ESCRIBE el valor de var usando pvar            
            *pvar = 10;
            Serial.print("var content: ");
            Serial.print(*pvar);
            Serial.print('\n');
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
    task1();
}

void loop()
{
    task1();
}
