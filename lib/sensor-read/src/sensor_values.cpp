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


Grid::Grid(int pinPeakAm, int pinPeakPm) 
    : SensorReadingInterface(0, 0), pinPeakAm(pinPeakAm), pinPeakPm(pinPeakPm) {}

int Grid::readSensor()
{
    if (digitalRead(pinPeakPm) == HIGH) return 1;
    if (digitalRead(pinPeakAm) == HIGH) return 2;
    return 0;
}

bool Grid::getState()
{
    return readSensor() != 0;
}
