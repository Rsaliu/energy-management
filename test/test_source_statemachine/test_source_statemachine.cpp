#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <state_machine.hpp>
#include <state_actions.hpp>
#include <common_header.hpp>
class MockStateActions : public SourceStateMachine::StateActionInterface
{
public:
    MOCK_METHOD((void), feedFromSolar, (), (override));
    MOCK_METHOD((void), feedFromBattery, (), (override));
    MOCK_METHOD((void), feedFromGrid, (), (override));
};

class StatesTest : public ::testing::Test
{
protected:
    void Init(SourceStateMachine::States sourceInitState)
    {
        sourceStateMachine = new SourceStateMachine::StateMachine(sourceInitState, &mockStateActions);
    }

    virtual void TearDown()
    {
        delete sourceStateMachine;
    }

    SourceStateMachine::StateMachine *sourceStateMachine;
    MockStateActions mockStateActions;
};

TEST_F(StatesTest, GridStateToSolar)
{
    Init(SourceStateMachine::States::GRID);
    std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, feedFromSolar()).Times( ::testing::AtLeast(1));
    Common::SourceStateData stateData(true,true);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::SOLAR, sourceStateMachine->getCurrentState());
}

TEST_F(StatesTest, GridStateToBattery)
{
    Init(SourceStateMachine::States::GRID);
    std::cout<<"<<<<<< firing tests >>>>>>>>"<<std::endl;
    EXPECT_CALL(mockStateActions, feedFromSolar()).Times( ::testing::AtLeast(1));
    Common::SourceStateData stateData(true,true);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::SOLAR, sourceStateMachine->getCurrentState());
}

TEST_F(StatesTest, SolarStateToGrid)
{
    Init(SourceStateMachine::States::SOLAR);
    EXPECT_CALL(mockStateActions, feedFromGrid()).Times( ::testing::AtLeast(1));
    Common::SourceStateData stateData(false,false);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::GRID, sourceStateMachine->getCurrentState());
}

TEST_F(StatesTest, SolarStateToBattery)
{
    Init(SourceStateMachine::States::SOLAR);
    EXPECT_CALL(mockStateActions, feedFromBattery()).Times( ::testing::AtLeast(1));
    Common::SourceStateData stateData(false,true);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::BATTERY, sourceStateMachine->getCurrentState());
}


TEST_F(StatesTest, BatteryStateToSolar)
{
    Init(SourceStateMachine::States::BATTERY);
    EXPECT_CALL(mockStateActions, feedFromSolar()).Times( ::testing::AtLeast(1));
    Common::SourceStateData stateData(true,true);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::SOLAR, sourceStateMachine->getCurrentState());
}

TEST_F(StatesTest, BatteryStateToGrid)
{
    Init(SourceStateMachine::States::BATTERY);
    EXPECT_CALL(mockStateActions, feedFromGrid()).Times( ::testing::AtLeast(1));
    Common::SourceStateData stateData(false,false);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::GRID, sourceStateMachine->getCurrentState());
}

TEST_F(StatesTest, StayInGrid)
{
    Init(SourceStateMachine::States::GRID);
    Common::SourceStateData stateData(false,false);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::GRID, sourceStateMachine->getCurrentState());
}

TEST_F(StatesTest, StayInSolar)
{
    Init(SourceStateMachine::States::SOLAR);
    Common::SourceStateData stateData(true,false);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::SOLAR, sourceStateMachine->getCurrentState());
    stateData = Common::SourceStateData(true,true);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::SOLAR, sourceStateMachine->getCurrentState());
}

TEST_F(StatesTest, StayInBattery)
{
    Init(SourceStateMachine::States::BATTERY);
    Common::SourceStateData stateData(false,true);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::BATTERY, sourceStateMachine->getCurrentState());
}

int main(int argc, char** argv) {
    // Initialize Google Test and Google Mock
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    // Run all tests
    return RUN_ALL_TESTS();
}