#include "state_machine.hpp"
#include <Arduino.h>
namespace SourceStateMachine
{
    StateMachine::StateMachine(States currentState, StateActionInterface *stateActionInterface) : currentState(currentState),
                                                                                                  stateActionInterface(stateActionInterface)
    {
    }
    void StateMachine::nextState(Common::StateData stateData)
    {
        States previousState = currentState;
        switch (currentState)
        {
        case States::SOLAR:
            if (!stateData.solarAboveThreshold && stateData.batteryAboveDoD)
            {
                currentState = States::BATTERY;
            }
            else if (!stateData.solarAboveThreshold && !stateData.batteryAboveDoD)
            {
                currentState = States::GRID;
            }
            else
                ;
            break;
        case States::BATTERY:
            if (stateData.solarAboveThreshold)
            {
                currentState = States::SOLAR;
            }
            else if (!stateData.batteryAboveDoD)
            {
                currentState = States::GRID;
            }
            else
                ;
            break;
        case States::GRID:
            if (stateData.solarAboveThreshold)
            {
                currentState = States::SOLAR;
            }
            break;

        default:
            break;
        }
        if (previousState != currentState)
        {
            takeAction(currentState);
        }
    }

    void StateMachine::takeAction(States currentState)
    {
        if(!stateActionInterface){
            Serial.println("StateAction interface cannot be null");
        }
        switch (currentState)
        {
        case States::SOLAR:
            stateActionInterface->feedFromSolar();
            break;
        case States::GRID:
            stateActionInterface->feedFromGrid();
            break;
        case States::BATTERY:
            stateActionInterface->feedFromBattery();
            break;
        default:
            break;
        }
    }
}