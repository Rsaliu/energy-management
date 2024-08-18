#include "load_state_machine.hpp"
#include <common_header.hpp>
#include <Arduino.h>

namespace LoadStateMachine
{
    StateMachine::StateMachine(States currentState, StateActionInterface *stateActionInterface) : currentState(currentState),
                                                                                                  stateActionInterface(stateActionInterface)
    {
        takeAction(currentState);
    }
    States StateMachine::getCurrentState(){
        return currentState;
    }
    void StateMachine::forceToState(States currentState){
        #ifdef PIO_UNIT_TESTING
            this->currentState = currentState;
        #endif
    }
    void StateMachine::nextState(Common::StateData stateData)
    {
        States previousState = currentState;
        switch (currentState)
        {
        case States::SOLAR_NOPEAK:
            if (stateData.sourceStateData.solarAboveThreshold)
            {
                if (stateData.sourcePeakData.peakAMOn)
                {
                    currentState = States::SOLAR_PEAKAM;
                }
                else if (stateData.sourcePeakData.peakPMOn)
                {
                    currentState = States::SOLAR_PEAKPM;
                }
                else
                    ;
            }
            else 
            {
                if(stateData.sourceStateData.batteryAboveDoD){
                    currentState = States::BATTERY;
                }else{
                    currentState = States::GRID_NOPEAK;
                }
                
            }
            break;
        case States::SOLAR_PEAKAM:
            if (stateData.sourceStateData.solarAboveThreshold)
            {
                if (stateData.sourcePeakData.peakPMOn)
                {
                    currentState = States::SOLAR_PEAKPM;
                }
                else if (!stateData.sourcePeakData.peakPMOn && !stateData.sourcePeakData.peakAMOn)
                {
                    currentState = States::SOLAR_NOPEAK;
                }
                else
                    ;
            }
            else
            {
                if(stateData.sourceStateData.batteryAboveDoD){
                    currentState = States::BATTERY;
                }else{
                    currentState = States::GRID_NOPEAK;
                }
            }
            break;
        case States::SOLAR_PEAKPM:
            if (stateData.sourceStateData.solarAboveThreshold)
            {
                if (stateData.sourcePeakData.peakAMOn)
                {
                    currentState = States::SOLAR_PEAKAM;
                }
                else if (!stateData.sourcePeakData.peakPMOn && !stateData.sourcePeakData.peakAMOn)
                {
                    currentState = States::SOLAR_NOPEAK;
                }
                else
                    ;
            }
            else
            {
                if(stateData.sourceStateData.batteryAboveDoD){
                    currentState = States::BATTERY;
                }else{
                    currentState = States::GRID_NOPEAK;
                }
            }
            break;
        case States::BATTERY:
            if (stateData.sourceStateData.solarAboveThreshold)
            {
                currentState = States::SOLAR_NOPEAK;
            }
            else if (!stateData.sourceStateData.batteryAboveDoD)
            {
                currentState = States::GRID_NOPEAK;
            }
            else
                ;

            break;
        case States::GRID_NOPEAK:
            if (!stateData.sourceStateData.solarAboveThreshold && ! stateData.sourceStateData.batteryAboveDoD)
            {
                if (stateData.sourcePeakData.peakAMOn)
                {
                    currentState = States::GRID_PEAKAM;
                }
                else if (stateData.sourcePeakData.peakPMOn)
                {
                    currentState = States::GRID_PEAKPM;
                }
                else
                    ;
            }
            else
            {
                if(stateData.sourceStateData.solarAboveThreshold){
                    currentState = States::SOLAR_NOPEAK;
                }else{
                    currentState = States::BATTERY;
                }
            }
            break;
        case States::GRID_PEAKAM:
            if (!stateData.sourceStateData.solarAboveThreshold && ! stateData.sourceStateData.batteryAboveDoD)
            {
                if (stateData.sourcePeakData.peakPMOn)
                {
                    currentState = States::GRID_PEAKPM;
                }
                else if (!stateData.sourcePeakData.peakPMOn && !stateData.sourcePeakData.peakAMOn)
                {
                    currentState = States::GRID_NOPEAK;
                }
                else
                    ;
            }
            else
            {
                if(stateData.sourceStateData.solarAboveThreshold){
                    currentState = States::SOLAR_NOPEAK;
                }else{
                    currentState = States::BATTERY;
                }
            }
            break;
        case States::GRID_PEAKPM:
            if (!stateData.sourceStateData.solarAboveThreshold && ! stateData.sourceStateData.batteryAboveDoD)
            {
                if (stateData.sourcePeakData.peakAMOn)
                {
                    currentState = States::GRID_PEAKAM;
                }
                else if (!stateData.sourcePeakData.peakPMOn && !stateData.sourcePeakData.peakAMOn)
                {
                    currentState = States::GRID_NOPEAK;
                }
                else
                    ;
            }
            else
            {
                if(stateData.sourceStateData.solarAboveThreshold){
                    currentState = States::SOLAR_NOPEAK;
                }else{
                    currentState = States::BATTERY;
                }
            }
            break;
        default:
            break;
        }
        if (previousState != currentState)
        {
            char buff[200];
            sprintf(buff, "<<<<< Load SM >>>>>>>>\nprevious state is: %d\nnew state is:  %d\n",
                    (int)previousState, (int)currentState);
            Common::println(buff);

            Common::println("<<<<<<<<<<>>>>>>>>>>>>");
            takeAction(currentState);
        }
    }

    void StateMachine::takeAction(States currentState)
    {
        if (!stateActionInterface)
        {

            Common::println("StateAction interface cannot be null");
        }
        switch (currentState)
        {
        case States::SOLAR_NOPEAK:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON});
            break;
        case States::SOLAR_PEAKAM:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::OFF});
            break;
        case States::SOLAR_PEAKPM:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON, LoadState::OFF, LoadState::ON});
            break;
        case States::BATTERY:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON});
            break;
        case States::GRID_NOPEAK:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON});
            break;
        case States::GRID_PEAKAM:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON, LoadState::OFF, LoadState::ON});
            break;
        case States::GRID_PEAKPM:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::OFF});
            break;
        default:
            break;
        }
    }
}