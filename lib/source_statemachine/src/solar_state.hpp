#ifndef __SOLAR_STATE_H__
#define __SOLAR_STATE_H__
#include "state_interface.hpp"
#include "battery_state.hpp"
#include "grid_state.hpp"
#include <state_machine.hpp>
class SolarState :public StateInterface{
    public:
        SolarState();
        void next(StateMachineInterface* machine,StateData& stateData) override;
        void printState() const override;
};
#endif