#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__
#include "state_interface.hpp"
class StateMachineInterface{
    public:
        virtual void nextState(StateData stateData) = 0; 
        virtual void setState(StateInterface* state) =0;
        virtual ~StateMachineInterface(){

        }
};
class StateMachine: public StateMachineInterface{
    public:
        StateMachine(StateInterface* currentState);
        void nextState(StateData stateData) override;
        void setState(StateInterface* state) override;
        ~StateMachine(){

        }
    private:
        StateInterface* currentState;
};
#endif