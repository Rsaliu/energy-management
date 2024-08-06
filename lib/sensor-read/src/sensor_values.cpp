#include "sensor_values.hpp"
#include <Arduino.h>

using namespace SensorRead;


SensorReadingInterface::SensorReadingInterface(int threshold, int pinNumber)
    : threshold(threshold), pinNumber(pinNumber) {}


LDR::LDR(int threshold, int pinNumber) 
    : SensorReadingInterface(threshold, pinNumber) {}

int LDR::readSensor()
{
    return analogRead(pinNumber);
}

bool LDR::getState()
{
    return readSensor() >= threshold;
}


Battery::Battery(int threshold, int pinNumber) 
    : SensorReadingInterface(threshold, pinNumber) {}

int Battery::readSensor()
{
    return analogRead(pinNumber);
}

bool Battery::getState()
{
    return readSensor() >= threshold;
}


PeakPeriod::PeakPeriod(int pinNumber) 
    : SensorReadingInterface(0, pinNumber) {}

int PeakPeriod::readSensor()
{
    return digitalRead(pinNumber);
}

bool PeakPeriod::getState()
{
    return readSensor() == HIGH;
}


