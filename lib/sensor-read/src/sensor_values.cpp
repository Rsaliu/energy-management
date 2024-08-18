#include "sensor_values.hpp"
#include <common_header.hpp>
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
    char buff[50];
    sprintf(buff,"LDR value is: %d\n",val);
    Common::println(buff);
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
    char buff[50];
    sprintf(buff,"Battery value is: %d\n",val);
    Common::println(buff);
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


