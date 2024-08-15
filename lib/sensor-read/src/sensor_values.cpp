#include "sensor_values.hpp"

#include <Arduino.h>


using namespace SensorRead;


SensorReadingInterface::SensorReadingInterface(int pinNumber)
    :  pinNumber(pinNumber) {}


LDR::LDR(int threshold, int pinNumber) 
    : SensorReadingInterface(pinNumber),threshold(threshold)  {}

int LDR::readSensor()
{
    
        return analogRead(pinNumber);

    
}

bool LDR::getState()
{
    int val = readSensor();
    Serial.println("LDR value is: "+(String)val);
    return val >= threshold;
}


Battery::Battery(int threshold, int pinNumber) 
    : SensorReadingInterface(pinNumber),threshold(threshold) {}

int Battery::readSensor()
{
    
        return analogRead(pinNumber);
    

}

bool Battery::getState()
{
    int val = readSensor();
    Serial.println("Battery value is: "+(String)val);
    return val >= threshold;
}


PeakPeriod::PeakPeriod(int pinNumber) 
    : SensorReadingInterface(pinNumber) {}

int PeakPeriod::readSensor()
{
    
        return digitalRead(pinNumber);
    
}

bool PeakPeriod::getState()
{
    return readSensor() == LOW;
}


