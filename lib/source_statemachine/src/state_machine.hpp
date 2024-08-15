#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__
#include <state_actions.hpp>
#include <common_header.hpp>
namespace SourceStateMachine
{

    enum class States
    {
        SOLAR,
        BATTERY,
        GRID
    };
    class StateMachine
    {
    public:
        StateMachine(States currentState, StateActionInterface *stateActionInterface);
        void nextState(Common::StateData stateData);
        States getCurrentState();
        ~StateMachine()
        {
        }

    private:
        States currentState;
        StateActionInterface *stateActionInterface;
        void takeAction(States currentState);
    };
}
#endif