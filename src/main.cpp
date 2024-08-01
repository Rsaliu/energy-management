#include "sensor_values.hpp"
#include <Arduino.h>

#define SolarThreshold 100
#define batteryThreshold 150

using namespace SensorRead;

void setup() {
    
    Serial.begin(9600);

    
    SensorPinConfig sensorPinConfig = {
        .solarPin = A0,
        .batteryPin = A1,
        .peakAm = 2,
        .peakPm = 3,
    };

  
    pinMode(sensorPinConfig.solarPin, INPUT);
    pinMode(sensorPinConfig.batteryPin, INPUT);
    pinMode(sensorPinConfig.peakAm, INPUT);
    pinMode(sensorPinConfig.peakPm, INPUT);

   

  
    LDR ldr(SolarThreshold, sensorPinConfig.solarPin);
    Battery battery(batteryThreshold, sensorPinConfig.batteryPin);
    PeakPeriod peakPeriod(sensorPinConfig.peakAm, sensorPinConfig.peakPm);

  
    Serial.print("LDR Sensor Value: ");
    Serial.println(ldr.readSensor());
    Serial.print("LDR Sensor State: ");
    Serial.println(ldr.getState() ? "High" : "Low");

    Serial.print("Battery Sensor Value: ");
    Serial.println(battery.readSensor());
    Serial.print("Battery Sensor State: ");
    Serial.println(battery.getState() ? "High" : "Low");

    Serial.print("Peak Sensor State: ");
    int peakState = peakPeriod.readSensor();
    if (peakState == 1) {
        Serial.println("Peak PM");
    } else if (peakState == 2) {
        Serial.println("Peak AM");
    } else {
        Serial.println("No Peak");
    }
}

void loop() {
    
}
