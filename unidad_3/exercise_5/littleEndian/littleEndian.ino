void setup() {
    Serial.begin(115200);
}

void loop() {
// 45 2f d3 36  y  44 45 63 d7// https://www.h-schmidt.net/FloatConverter/IEEE754.htmlstatic 
float num = 2813.2007;
float wow = 789.56;
static uint8_t arr[4] = {0};

if(Serial.available()){
if(Serial.read() == 's'){
            memcpy(arr,(uint8_t *)&num,4);
for(int8_t i = 3; i >= 0; i--){
              Serial.write(arr[i]);
}
}
else if(Serial.read() == 'a'){
            memcpy(arr,(uint8_t *)&wow,4);
for(int8_t i = 3; i >= 0; i--){
              Serial.write(arr[i]);
            }
        }
    }
}
