// Definición de estados y variable de estado
enum class Task1States{
  INIT,
  WAIT_TIMEOUT
};

// Definición de variables static (conservan su valor entre llamadas a task1)
static Task1States task1State = Task1States::INIT;
static uint32_t lastTime = 0;

// Constantes
constexpr uint32_t INTERVAL = 1000;

void task1(){
  // MÁQUINA de ESTADOS 
  switch(task1State){
    case Task1States::INIT:{
      // Acciones
      Serial.begin(115200);
      
      // Garantiza los valores iniciales para el siguiente estado
      lastTime = millis();
      task1State = Task1States::WAIT_TIMEOUT;

      Serial.print("Task1States::WAIT_TIMEOUT\n");

      break;
    }
    case Task1States::WAIT_TIMEOUT:{
      uint32_t currentTime = millis();
      // Evento
      if ((currentTime - lastTime) >= INTERVAL){
        // Acciones:
        lastTime = currentTime;
        Serial.print(currentTime);
        Serial.print('\n');
      }
      break;
    }
    default:{
      Serial.print("Error");
      break;
    }
  }
}

void setup() {
  task1();
}

void loop() {
  task1();
}