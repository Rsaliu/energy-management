#ifndef __STATE_INTERFACE_H__
#define __STATE_INTERFACE_H__
#include <Arduino.h>
class StateMachineInterface;

struct StateData
{
    bool solarAboveThreshold;
    bool batteryAboveDoD;
};

class StateInterface{
    public:
        virtual void next(StateMachineInterface* machine,StateData& stateData)=0;
        virtual void printState() const = 0;
        virtual ~StateInterface(){

        }
};
#endif