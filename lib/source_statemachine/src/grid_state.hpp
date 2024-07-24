#ifndef __GRID_STATE_H__
#define __GRID_STATE_H__
#include "state_interface.hpp"
#include "solar_state.hpp"
#include <state_machine.hpp>

class GridState :public StateInterface{
    public:
        GridState();
        void next(StateMachineInterface* machine,StateData& stateData);
        void printState() const override;
};
#endif