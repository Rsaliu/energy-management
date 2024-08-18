#ifndef __LOAD_STATE_MACHINE_H__
#define __LOAD_STATE_MACHINE_H__
#include <load_state_actions.hpp>
#include <common_header.hpp>
namespace LoadStateMachine
{

    enum class States
    {
        SOLAR_NOPEAK,
        SOLAR_PEAKAM,
        SOLAR_PEAKPM,
        GRID_NOPEAK,
        GRID_PEAKAM,
        GRID_PEAKPM,
        BATTERY,
    };
    class StateMachine
    {
    public:
        StateMachine(States currentState, StateActionInterface *stateActionInterface);
        void nextState(Common::StateData stateData);
        States getCurrentState();
        void forceToState(States currentState);
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