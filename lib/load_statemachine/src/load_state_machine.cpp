#include "load_state_machine.hpp"
namespace LoadStateMachine
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
        case States::OFF:
            if (stateData.solarAboveThreshold )
            {
                currentState = States::SOLAR_NOPEAK;
            }
            else if (!stateData.solarAboveThreshold && stateData.batteryAboveDoD)
            {
                currentState = States::BATTERY;
            }
            else if (!stateData.solarAboveThreshold && !stateData.batteryAboveDoD)
            {
                currentState = States::GRID_NOPEAK;
            }
            else
                ;
            break;
        case States::SOLAR_NOPEAK:
            if (stateData.solarAboveThreshold)
            {
                if(stateData.peakAMOn){
                    currentState = States::SOLAR_PEAKAM;
                }
                else if(stateData.peakPMOn){
                    currentState = States::SOLAR_PEAKPM;
                }else;
            }
            else{
                currentState = States::BATTERY;
            }
            break;
        case States::SOLAR_PEAKAM:
            if (stateData.solarAboveThreshold)
            {
                if(stateData.peakPMOn){
                    currentState = States::SOLAR_PEAKPM;
                }
                else if(!stateData.peakPMOn && !stateData.peakAMOn){
                    currentState = States::SOLAR_NOPEAK;
                }else;
            }
            else{
                currentState = States::BATTERY;
            }
            break;
        case States::SOLAR_PEAKPM:
            if (stateData.solarAboveThreshold)
            {
                if(stateData.peakAMOn){
                    currentState = States::SOLAR_PEAKAM;
                }
                else if(!stateData.peakPMOn && !stateData.peakAMOn){
                    currentState = States::SOLAR_NOPEAK;
                }else;
            }
            else{
                currentState = States::BATTERY;
            }
            break;
        case States::BATTERY:
            if (stateData.solarAboveThreshold)
            {
                currentState = States::SOLAR_NOPEAK;
            }
            else if(!stateData.batteryAboveDoD){
                currentState = States::GRID_NOPEAK;
            }
            else;
        
            break;
        case States::GRID_NOPEAK:
            if (!stateData.solarAboveThreshold)
            {
                if(stateData.peakAMOn){
                    currentState = States::GRID_PEAKAM;
                }
                else if(stateData.peakPMOn){
                    currentState = States::GRID_PEAKPM;
                }else;
            }
            else{
                currentState = States::SOLAR_NOPEAK;
            }
            break;
        case States::GRID_PEAKAM:
            if (!stateData.solarAboveThreshold)
            {
                if(stateData.peakPMOn){
                    currentState = States::GRID_PEAKPM;
                }
                else if(!stateData.peakPMOn && !stateData.peakAMOn){
                    currentState = States::GRID_NOPEAK;
                }else;
            }
            else{
                currentState = States::SOLAR_NOPEAK;
            }
            break;
        case States::GRID_PEAKPM:
            if (!stateData.solarAboveThreshold)
            {
                if(stateData.peakAMOn){
                    currentState = States::GRID_PEAKAM;
                }
                else if(!stateData.peakPMOn && !stateData.peakAMOn){
                    currentState = States::GRID_NOPEAK;
                }else;
            }
            else{
                currentState = States::SOLAR_NOPEAK;
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
        switch (currentState)
        {
        case States::SOLAR_NOPEAK:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON,LoadState::ON,LoadState::ON});
            break;
        case States::SOLAR_PEAKAM:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON,LoadState::ON,LoadState::OFF});
            break;
        case States::SOLAR_PEAKPM:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON,LoadState::OFF,LoadState::ON});
            break;
        case States::BATTERY:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON,LoadState::ON,LoadState::ON});
            break;
        case States::GRID_NOPEAK:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON,LoadState::ON,LoadState::ON});
            break;
        case States::GRID_PEAKAM:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON,LoadState::OFF,LoadState::ON});
            break;
        case States::GRID_PEAKPM:
            stateActionInterface->setLoad(LoadPattern{LoadState::ON,LoadState::ON,LoadState::OFF});
            break;
        default:
            break;
        }
    }
}