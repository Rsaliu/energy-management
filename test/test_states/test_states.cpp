#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <load_state_actions.hpp>
#include <load_state_machine.hpp>
#include <state_machine.hpp>
#include <state_actions.hpp>

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
    virtual void SetUp()
    {
        sourceStateMachine = new SourceStateMachine::StateMachine(sourceInitState, &mockStateActions);
    }

    virtual void TearDown()
    {
        delete sourceStateMachine;
    }

    SourceStateMachine::States sourceInitState = SourceStateMachine::States::GRID;
    SourceStateMachine::StateMachine *sourceStateMachine;
    MockStateActions mockStateActions;
};

TEST_F(StatesTest, StateMachineToSolarFromGrid)
{
    EXPECT_CALL(mockStateActions, feedFromSolar()).Times( ::testing::AtLeast(1));
    Common::StateData stateData(true,true,false,false);
    sourceStateMachine->nextState(stateData);
    EXPECT_EQ(SourceStateMachine::States::SOLAR, sourceStateMachine->getCurrentState());
}

int main(int argc, char** argv) {
    // Initialize Google Test and Google Mock
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    // Run all tests
    return RUN_ALL_TESTS();
}