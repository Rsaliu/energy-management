#include "sensor_values.hpp"
#include <Arduino.h>

 // Threshold values
#define SolarThreshold 100
#define batteryThreshold 150

using namespace SensorRead;

void setup() {
    // Initialize Serial for debugging
    Serial.begin(9600);

    // Pin configuration
    SensorPinConfig sensorPinConfig = {
        .solarPin = A0,
        .batteryPin = A1,
        .peakAm = 2,
        .peakPm = 3,
    };

    // Initialize the pins
    pinMode(sensorPinConfig.solarPin, INPUT);
    pinMode(sensorPinConfig.batteryPin, INPUT);
    pinMode(sensorPinConfig.peakAm, INPUT);
    pinMode(sensorPinConfig.peakPm, INPUT);

   

    // Create sensor instances
    LDR ldr(SolarThreshold, sensorPinConfig.solarPin);
    Battery battery(batteryThreshold, sensorPinConfig.batteryPin);
    Grid grid(sensorPinConfig.peakAm, sensorPinConfig.peakPm);

    // Example usage
    Serial.print("LDR Sensor Value: ");
    Serial.println(ldr.readSensor());
    Serial.print("LDR Sensor State: ");
    Serial.println(ldr.getState() ? "High" : "Low");

    Serial.print("Battery Sensor Value: ");
    Serial.println(battery.readSensor());
    Serial.print("Battery Sensor State: ");
    Serial.println(battery.getState() ? "High" : "Low");

    Serial.print("Grid Sensor State: ");
    int gridState = grid.readSensor();
    if (gridState == 1) {
        Serial.println("Peak PM");
    } else if (gridState == 2) {
        Serial.println("Peak AM");
    } else {
        Serial.println("No Peak");
    }
}

void loop() {
    // Your main loop code
}
