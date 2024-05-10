#include <pico/stdlib.h>
#include <hardware/adc.h>
#include <Arduino.h>

enum State {
    STATE_OFF,
    STATE_SETUP,
    STATE_SELECT_PARAMETERS,
    STATE_PLAYING
};
State currentState = STATE_OFF;

// Variables
float volume = 0.0; // 0 is mute
float volumeMax = 10.0;
float trackDuration = 0.0;
float selectedDuration = 0.0;
float currentTrack = 1.0;
float maxTrack = 10.0;
float trackJump = 1.0;
float volumeJump = 1.0;
bool ledState = false;
bool playerOn = false;
unsigned long lastStateChange = 0;

// Variables to store the previous values
float previousTemperature = 0.0;
float previousVolume = 0.0;
float previousCurrentTrack = 0.0;
float previousTrackDuration = 0.0;

// Song list
const char* songList[10] = {
        "1. Song One",
        "2. Song Two",
        "3. Song Three",
        "4. Song Four",
        "5. Song Five",
        "6. Song Six",
        "7. Song Seven",
        "8. Song Eight",
        "9. Song Nine",
        "10. Song Ten"
};

// Function to read temperature from built-in sensor
float readTemperature() {
    // select ADC input 4 (temperature sensor)
    adc_select_input(4);

    // perform an ADC conversion
    uint16_t result = adc_read();

    // calculate voltage from ADC result
    float voltage = result * (3.3f / 4096);

    // calculate temperature using the formula for RP2040
    float temperature = 27 - (voltage - 0.706) / 0.001721;

    return temperature;
}

// Function to calculate checksum for a float
uint8_t calculateChecksum(float value) {
    uint8_t* bytePointer = (uint8_t*)&value;
    uint8_t checksum = 0;
    for (size_t i = 0; i < sizeof(float); i++) {
        checksum += bytePointer[i];
    }
    return checksum;
}

// Function to calculate checksum for a received float
uint8_t calculateReceivedChecksum(float value) {
    uint8_t* bytePointer = (uint8_t*)&value;
    uint8_t checksum = 0;
    for (size_t i = 0; i < sizeof(float); i++) {
        checksum += bytePointer[i];
    }
    return checksum;
}

// Function to handle received data
void handleReceivedData(float temperature, float deltaTemperature, float volume, float deltaVolume, float currentTrack, float deltaCurrentTime, float trackDuration, float deltaTrackDuration, uint8_t receivedChecksum) {
    // Calculate the checksum of the received data
    uint8_t calculatedChecksum = calculateReceivedChecksum(temperature) ^ calculateReceivedChecksum(deltaTemperature) ^ calculateReceivedChecksum(volume) ^ calculateReceivedChecksum(deltaVolume) ^ 
            calculateReceivedChecksum(currentTrack) ^ calculateReceivedChecksum(deltaCurrentTime) ^ calculateReceivedChecksum(trackDuration) ^ calculateReceivedChecksum(deltaTrackDuration);

    // Compare the calculated checksum with the received checksum
    if (calculatedChecksum != receivedChecksum) {
        // If the checksums do not match, print an error message
        Serial.println("Error: Checksum does not match. Data may be corrupted.");
    } else {
        // If the checksums match, process the data
        // ...
    }
}

void offState() {
    if (millis() - lastStateChange >= 3000) {
        Serial.println("Player is off Press O to turn ON");
        lastStateChange = millis();
    }

    if (Serial.available() > 0) {
        uint8_t command = Serial.read();
        if (command == 'O') {
            currentState = STATE_SETUP;
            playerOn = true;
        }
    }
}

void selectParametersState() {
    Serial.println("Welcome to Bubble Pop music player setup. Please enter the following parameters:");
    Serial.println("Track number (1-10):");
    while (Serial.available() == 0) {}
    float selectedTrack = Serial.parseFloat();
    if (selectedTrack >= 1 && selectedTrack <= maxTrack) {
        currentTrack = selectedTrack;
        Serial.println("Initial track " + String(currentTrack));
    } else {
        Serial.println("Invalid track number, defaulting to track 1");
        currentTrack = 1;
    }

    Serial.println("Next set Volume (0-10):");
    while (Serial.available() == 0) {}
    float selectedVolume = Serial.parseFloat();
    if (selectedVolume >= 0 && selectedVolume <= volumeMax) {
        volume = selectedVolume;
        Serial.println("Volume set to " + String(volume));
    } else {
        Serial.println("Invalid volume value, defaulting to volume 0 (mute)");
        volume = 0;
    }

    Serial.println("Next set the Track duration (5-180 seconds):");
    while (Serial.available() == 0) {}
    selectedDuration = Serial.parseFloat();
    if (selectedDuration >= 5 && selectedDuration <= 180) {
        trackDuration = selectedDuration;
        Serial.println("Track duration set to " + String(trackDuration) + " seconds");
    } else {
        Serial.println("Invalid duration value, defaulting to 5 seconds");
        trackDuration = 5;
    }

    currentState = STATE_PLAYING;
}

void task() {
    if (Serial.available() > 0) {
        uint8_t command = Serial.read();
        switch (command) {
            case 'P': // Play
                currentState = STATE_PLAYING;
                break;
            case 'S': // Stop
                currentState = STATE_OFF;
                playerOn = false;
                break;
            case 'N': // Next track
                if (currentTrack < maxTrack) {
                    currentTrack += trackJump;
                } else {
                    currentTrack = 1;
                }
                Serial.println("Playing track " + String(currentTrack));
                break;
            case 'V': // Adjust volume
                if (Serial.available() >= 1) {
                    float newVolume = Serial.parseFloat();
                    if (newVolume >= 0 && newVolume <= volumeMax) {
                        volume = newVolume;
                        Serial.println("Volume set to " + String(volume));
                    } else {
                        Serial.println("Invalid volume value");
                    }
                }
                break;
            case 'D': // Adjust track duration
                if (Serial.available() >= 1) {
                    float newDuration = Serial.parseFloat();
                    if (newDuration >= 0 && newDuration <= 180) {
                        trackDuration = newDuration;
                        Serial.println("Track duration set to " + String(trackDuration) + " seconds");
                    } else {
                        Serial.println("Invalid duration value");
                    }
                }
                break;
            case 'Z': // Read variables
            {
                float temperature = readTemperature();
                float deltaTemperature = temperature - previousTemperature;
                previousTemperature = temperature;

                float deltaVolume = volume - previousVolume;
                previousVolume = volume;

                float deltaCurrentTrack = currentTrack - previousCurrentTrack;
                previousCurrentTrack = currentTrack;

                float deltaTrackDuration = trackDuration - previousTrackDuration;
                previousTrackDuration = trackDuration;

                // Send the variables as binary data
                Serial.write((byte*)&temperature, sizeof(temperature));
                Serial.write((byte*)&deltaTemperature, sizeof(deltaTemperature));
                Serial.write((byte*)&volume, sizeof(volume));
                Serial.write((byte*)&deltaVolume, sizeof(deltaVolume));
                Serial.write((byte*)&currentTrack, sizeof(currentTrack));
                Serial.write((byte*)&deltaCurrentTrack, sizeof(deltaCurrentTrack));
                Serial.write((byte*)&trackDuration, sizeof(trackDuration));
                Serial.write((byte*)&deltaTrackDuration, sizeof(deltaTrackDuration));

                // Send the "enabled" status of each variable
                uint8_t temperatureEnabled = (temperature > 0) ? 1 : 0;
                uint8_t volumeEnabled = (volume > 0) ? 1 : 0;
                uint8_t currentTrackEnabled = (currentTrack > 0) ? 1 : 0;
                uint8_t trackDurationEnabled = (trackDuration > 0) ? 1 : 0;

                Serial.write(temperatureEnabled);
                Serial.write(volumeEnabled);
                Serial.write(currentTrackEnabled);
                Serial.write(trackDurationEnabled);

                uint8_t checksum = calculateChecksum(temperature) ^ calculateChecksum(deltaTemperature) ^ calculateChecksum(volume) ^ 
                        calculateChecksum(deltaVolume) ^ calculateChecksum(currentTrack) ^ calculateChecksum(deltaCurrentTrack) ^ calculateChecksum(trackDuration) ^ calculateChecksum(deltaTrackDuration);
                Serial.write(checksum);

                // Call handleReceivedData() with the received data
                handleReceivedData(temperature, deltaTemperature,  volume, deltaVolume, currentTrack, deltaCurrentTrack, trackDuration,  deltaTrackDuration, checksum);
                break;
            }
            default:
                Serial.println("Invalid command");
                break;
        }
    }
}

void playingState() {
    if (playerOn) {
        task();
        if (currentState == STATE_PLAYING){
            // Print the current temperature
            float temperature = readTemperature();
            Serial.print("Current temperature: ");
            Serial.println(temperature);
            Serial.println("\n");

            // Check if the temperature reaches a certain value
            if (temperature >= 45.0) {
                // If the temperature is too high, turn off the player             
                Serial.println("Player turned off due to high temperature.");
                playerOn = false;
                currentState = STATE_OFF;
                return; // Exit the function early
            }
            
            if (trackDuration > 0) {
                trackDuration--;
                Serial.println("Track duration: " + String(trackDuration) + " seconds");
            }
            delay(1000);

            if (trackDuration == 0){
                currentTrack++;
                volume += volumeJump;
                trackDuration = selectedDuration;

                if (currentTrack >= maxTrack){
                    currentTrack = 0;
                }
            }

            // Send information about the current song
            Serial.print("Current song: ");
            Serial.println(songList[(int)currentTrack - 1]);
        } else {
            currentState = STATE_SETUP; // Go back to the setup state
        }

    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    adc_init();
  //enable temperature sensor
  adc_set_temp_sensor_enabled(true);
    currentState = STATE_OFF;
}

void loop() {
    switch (currentState) {
        case STATE_OFF:
            offState();
            break;
        case STATE_SETUP:
            selectParametersState();
            break;
        case STATE_PLAYING:
            playingState();
            break;
    }

    // Keep the LED blinking at 1 Hz
    uint32_t currentTime = millis();
    if ((currentTime - lastStateChange) >= 500) { // Blink every 500 ms (0.5 seconds)
        lastStateChange = currentTime;
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
    }
}
