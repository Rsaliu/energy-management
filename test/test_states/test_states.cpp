#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <state_actions.hpp>
#include <solar_state.hpp>
#include <grid_state.hpp>
#include <battery_state.hpp>


class MockStateActions: public StateActionInterface
{
    public: 
        MOCK_METHOD((void), feedFromSolar, (), (override));
        MOCK_METHOD((void), feedFromBattery, (), (override));
        MOCK_METHOD((void), feedFromGrid, (), (override));

};

class StatesTest: public ::testing::Test
{
    protected:
        virtual void SetUp()
        {      
            solar = new SolarState(&mockStateActions);
            battery = new BatteryState(&mockStateActions);
            grid = new GridState(&mockStateActions);
        }

        virtual void TearDown()
        {
            delete solar;
            delete battery;
            delete grid;
 
        }
    SolarState* solar;
    BatteryState* battery;
    GridState* grid;
    MockStateActions mockStateActions;
};

TEST_F(StatesTest, StateActionTest) {
    EXPECT_CALL(mockStateActions,feedFromSolar()).Times(AtLeast(1));
    solar->stateAction()
}