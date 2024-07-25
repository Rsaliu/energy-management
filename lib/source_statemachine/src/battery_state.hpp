#ifndef __BATTERY_STATE_H__
#define __BATTERY_STATE_H__
#include "state_interface.hpp"
#include "solar_state.hpp"
#include "grid_state.hpp"
#include <state_machine.hpp>
class BatteryState :public StateInterface{
    public:
        BatteryState(StateActionInterface* stateActionInterface);
        void next(StateMachineInterface* machine,StateData& stateData) override;
        void printState() const override;
        void stateAction() const override;
    private:
        StateActionInterface* stateActionInterface;
};
#endif