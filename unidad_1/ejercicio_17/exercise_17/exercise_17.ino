void setup() 
{
 Serial.begin(115200);
}

void loop() 
{
 if(Serial.available() >= 2)
 {
    int dataRx1 = Serial.read();
    int dataRx2 = Serial.read();
    int dataRx3 = Serial.read();

    Serial.print("1:");
    Serial.print(dataRx1);
    Serial.print('\n');
    Serial.print("2:");
    Serial.print(dataRx2);
    Serial.print('\n');
    Serial.print("3:");
    Serial.print(dataRx3);
    Serial.print('\n');
}
}
