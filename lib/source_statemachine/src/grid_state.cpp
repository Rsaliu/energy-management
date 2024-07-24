#include "grid_state.hpp"

GridState::GridState():StateInterface(){
    
}
void GridState::next(StateMachineInterface* machine,StateData& stateData){
    if (stateData.solarAboveThreshold) {
        machine->setState(new SolarState());
    }
}
void GridState::printState() const{
    Serial.println("State is Grid state");
}