#include "state_machine.hpp"
#include <common_header.hpp>
#include <Arduino.h>

namespace SourceStateMachine
{
    StateMachine::StateMachine(States currentState, StateActionInterface *stateActionInterface) : currentState(currentState),
                                                                                                  stateActionInterface(stateActionInterface)
    {
        takeAction(currentState);
    }
    States StateMachine::getCurrentState(){
        return currentState;
    }
    void StateMachine::nextState(Common::SourceStateData stateData)
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
            else if (!stateData.batteryAboveDoD && !stateData.solarAboveThreshold)
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
            else if(!stateData.solarAboveThreshold && stateData.batteryAboveDoD){
                currentState = States::BATTERY;
            }
            else;
            break;

        default:
            break;
        }
        if (previousState != currentState)
        {
            char buff[100];
            sprintf(buff,"<<<<< Source SM >>>>>>>> \nprevious state is:  %d\nnew state is: %d\n<<<<<<<<<<>>>>>>>>>>>>",
            (int)previousState,(int)currentState);
            Common::println(buff);
            takeAction(currentState);
        }
    }

    void StateMachine::takeAction(States currentState)
    {
        if(!stateActionInterface){
            
            Common::println("StateAction interface cannot be null");
            
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