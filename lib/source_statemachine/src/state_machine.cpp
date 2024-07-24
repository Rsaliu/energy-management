#include "state_machine.hpp"

StateMachine::StateMachine(StateInterface* currentState):currentState(currentState){

}
void StateMachine::nextState(StateData stateData){
    StateInterface* temp = currentState;
    currentState->next(this,stateData);
    delete temp;
}
void StateMachine::setState(StateInterface* state){
    currentState = state;
    currentState->printState();
}