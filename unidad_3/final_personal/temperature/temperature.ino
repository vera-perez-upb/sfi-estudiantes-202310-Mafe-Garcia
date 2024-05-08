#include <pico/stdlib.h>
#include <hardware/adc.h>

void setup() {
  // initialize serial communication
  Serial.begin(115200);
  //initialize ADC
  adc_init();
  //enable temperature sensor
  adc_set_temp_sensor_enabled(true);
}

void loop() {
  // select ADC input 4
adc_select_input(4);

//perform an ADC conversation
uint16_t result = adc_read();

//calculate voltage from ADC result
float voltage = result*(3.3f/4096);

//calculate temperature using the formula for RP2040
float temperature = 27 - (voltage - 0.706) / 0.001721;

//print the temperature to serial monitor
Serial.print(temperature);
Serial.print("°c\n");

// delay 2 seconds
delay(2000);
}
