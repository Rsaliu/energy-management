#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <load_state_actions.hpp>
#include <load_state_machine.hpp>
#include <common_header.hpp>
#include <memory>
class MockStateActions : public LoadStateMachine::StateActionInterface
{
public:
    MOCK_METHOD((void), setLoad, (LoadStateMachine::LoadPattern pattern), (override));
};

class StatesTest : public ::testing::Test
{
protected:
    void Init(LoadStateMachine::States loadInitState)
    {
        loadStateMachine = new LoadStateMachine::StateMachine(loadInitState, &mockStateActions);
    }

    virtual void TearDown()
    {
        delete loadStateMachine;
    }

    LoadStateMachine::StateMachine *loadStateMachine;
    MockStateActions mockStateActions;
};
using namespace LoadStateMachine;

TEST_F(StatesTest, SolarNoPeakToPeakAM)
{
    Init(LoadStateMachine::States::SOLAR_NOPEAK);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::OFF})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(true,false,true,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_PEAKAM, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, SolarNoPeakToPeakPM)
{
    Init(LoadStateMachine::States::SOLAR_NOPEAK);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::OFF, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(true,false,false,true);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_PEAKPM, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, SolarPeakAMToSolarNoPeak)
{
    Init(LoadStateMachine::States::SOLAR_PEAKAM);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(true,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_NOPEAK, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, SolarPeakAMToSolarPeakPM)
{
    Init(LoadStateMachine::States::SOLAR_PEAKAM);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::OFF, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(true,false,false,true);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_PEAKPM, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, SolarPeakPMToSolarPeakAM)
{
    Init(LoadStateMachine::States::SOLAR_PEAKPM);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::OFF})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(true,false,true,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_PEAKAM, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, SolarPeakPMToSolarNoPeak)
{
    Init(LoadStateMachine::States::SOLAR_PEAKPM);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(true,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_NOPEAK, loadStateMachine->getCurrentState());
}

TEST(SolarStatesToBatteryTest, SolarStatesToBattery)
{
    MockStateActions mockStateActions;
    std::unique_ptr<LoadStateMachine::StateMachine> loadStateMachine(
        new LoadStateMachine::StateMachine(States::SOLAR_NOPEAK, &mockStateActions)
    );
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(3));
    Common::StateData stateData(false,true,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());
    loadStateMachine->forceToState(States::SOLAR_PEAKPM);
    stateData = Common::StateData(false,true,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());   
    loadStateMachine->forceToState(States::SOLAR_PEAKAM);
    stateData = Common::StateData(false,true,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());  
}

TEST(SolarStatesToGridTest, SolarStatesToGrid)
{
    MockStateActions mockStateActions;
    std::unique_ptr<LoadStateMachine::StateMachine> loadStateMachine(
        new LoadStateMachine::StateMachine(States::SOLAR_NOPEAK, &mockStateActions)
    );
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(3));
    Common::StateData stateData(false,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_NOPEAK, loadStateMachine->getCurrentState());
    loadStateMachine->forceToState(States::SOLAR_PEAKPM);
    stateData = Common::StateData(false,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_NOPEAK, loadStateMachine->getCurrentState());   
    loadStateMachine->forceToState(States::SOLAR_PEAKAM);
    stateData = Common::StateData(false,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_NOPEAK, loadStateMachine->getCurrentState());

}



TEST_F(StatesTest, GridNoPeakToPeakAM)
{
    Init(LoadStateMachine::States::GRID_NOPEAK);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::OFF, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(false,false,true,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_PEAKAM, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, GridNoPeakToPeakPM)
{
    Init(LoadStateMachine::States::GRID_NOPEAK);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::OFF})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(false,false,false,true);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_PEAKPM, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, GridPeakAMToGridNoPeak)
{
    Init(LoadStateMachine::States::GRID_PEAKAM);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(false,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_NOPEAK, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, GridPeakAMToGridPeakPM)
{
    Init(LoadStateMachine::States::GRID_PEAKAM);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::OFF})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(false,false,false,true);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_PEAKPM, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, GridPeakPMToGridPeakAM)
{
    Init(LoadStateMachine::States::GRID_PEAKPM);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::OFF, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(false,false,true,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_PEAKAM, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, GridPeakPMToGridNoPeak)
{
    Init(LoadStateMachine::States::GRID_PEAKPM);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(false,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_NOPEAK, loadStateMachine->getCurrentState());
}

TEST(GridStatesToBatteryTest, GridStatesToBattery)
{
    MockStateActions mockStateActions;
    std::unique_ptr<LoadStateMachine::StateMachine> loadStateMachine(
        new LoadStateMachine::StateMachine(States::GRID_NOPEAK, &mockStateActions)
    );
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(3));
    Common::StateData stateData(false,true,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());
    loadStateMachine->forceToState(States::GRID_PEAKPM);
    stateData = Common::StateData(false,true,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());   
    loadStateMachine->forceToState(States::GRID_PEAKAM);
    stateData = Common::StateData(false,true,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());  
}

TEST(GridStatesToSolarTest, GridStatesToSolar)
{
    MockStateActions mockStateActions;
    std::unique_ptr<LoadStateMachine::StateMachine> loadStateMachine(
        new LoadStateMachine::StateMachine(States::GRID_NOPEAK, &mockStateActions)
    );
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(3));
    Common::StateData stateData(true,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_NOPEAK, loadStateMachine->getCurrentState());
    loadStateMachine->forceToState(States::GRID_PEAKPM);
    stateData = Common::StateData(true,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_NOPEAK, loadStateMachine->getCurrentState());   
    loadStateMachine->forceToState(States::GRID_PEAKAM);
    stateData = Common::StateData(true,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_NOPEAK, loadStateMachine->getCurrentState());

}

TEST_F(StatesTest, BatteryToSolar)
{
    Init(LoadStateMachine::States::BATTERY);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(true,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::SOLAR_NOPEAK, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, BatteryToGrid)
{
    Init(LoadStateMachine::States::BATTERY);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(1));
    Common::StateData stateData(false,false,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::GRID_NOPEAK, loadStateMachine->getCurrentState());
}

TEST_F(StatesTest, StayInState)
{
    Init(LoadStateMachine::States::BATTERY);
    // std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, setLoad(LoadPattern{LoadState::ON, LoadState::ON, LoadState::ON})).Times( ::testing::AtLeast(0));
    Common::StateData stateData(false,true,false,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());
    stateData = Common::StateData(false,true,false,true);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());
    stateData = Common::StateData(false,true,true,false);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());
    stateData = Common::StateData(false,true,true,true);
    loadStateMachine->nextState(stateData);
    EXPECT_EQ(States::BATTERY, loadStateMachine->getCurrentState());
}



int main(int argc, char** argv) {
    // Initialize Google Test and Google Mock
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    // Run all tests
    return RUN_ALL_TESTS();
}