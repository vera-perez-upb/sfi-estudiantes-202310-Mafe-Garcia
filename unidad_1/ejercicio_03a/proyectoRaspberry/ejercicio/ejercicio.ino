void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  static uint32_t previousTime = 0; 
  static bool ledState = true; //de lo que entiendo cuando esta en true significa prendido, sin embargo empieza apagado por default, creo

  uint32_t currentTime = millis(); //Cuenta los milisegundos desde que empieza a correr el programa, por lo que current time son los milisegundos que han pasado desde 0

  if( (currentTime - previousTime) > 500){ //el if se realiza si lleva mas de 500 milisegundos --> 501-0 > 500
    previousTime = currentTime; // hace que current time vuelva a ser 0, por lo que el estado del bombillo cambiara cuando vuelvan a pasar 500 milisegundos
    ledState = !ledState; // cambia el estado del led
    digitalWrite(LED_BUILTIN, ledState); //le dice al led que debe cambiar
  }
}
