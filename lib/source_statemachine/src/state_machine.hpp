#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__
#include <state_actions.hpp>
namespace SourceStateMachine
{
    struct StateData
    {
        bool solarAboveThreshold;
        bool batteryAboveDoD;
        bool peakPeriod;
    };

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
        void nextState(StateData stateData);
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