#include <gtest/gtest.h>
#include "../include.h"
#include "../TrafficLight.hpp"
#include "../VehicleTrafficLight.hpp"
#include "../Controller.hpp"

// 3* component / interface tests
//   1/2/100 emergency cars passing by
//   every possible directions, make sure no crashing
//   error -> recover

// (pretend) a test driven based implementation

/* ------------------------------ */

class TrafficLightUnitTest : public ::testing::Test
{
protected:
    // use minimum delay = 0 ms
    VehicleTrafficLight light = VehicleTrafficLight(("Device Under Test (DUT)", 0));
    int vanillaPipe[2], colorPipe[2], statePipe[2];
    std::jthread *trafficLightsBehaviour;

    // run at the beginning of each test
    void SetUp() override
    {
        // set pipes for communication with the traffic light
        EXPECT_FALSE(pipe(vanillaPipe) < 0) << "error creating vanillaPipe";
        EXPECT_FALSE(pipe(colorPipe) < 0) << "error creating colorPipe";
        EXPECT_FALSE(pipe(statePipe) < 0) << "error creating statePipe";
        light.setPipe(vanillaPipe);
        light.setColorPipe(colorPipe);
        light.setStatePipe(statePipe);

        // keep the traffic light running autonomously
        trafficLightsBehaviour = new std::jthread(light.spawn());

        // init the light by writing ODD -> RED_TO_YELLOW
        int trans[2] = {TO_INT(Transition::ODD), TO_INT(NormalRoutineTransition::RED_TO_YELLOW)};
        int s = sizeof(trans) / sizeof(trans[0]);
        for (int i = 0; i < s; i++)
        {
            write(colorPipe[1], std::to_string(trans[i]).c_str(), 2);

            // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
            char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
            readBuf(pipeBuf, stateBuf);
        }
    }

    // // run at the end of each test
    // void TearDown() override
    // {
    //     trafficLightsBehaviour->std::jthread::~jthread();
    // }

    void readBuf(char pipeBuf[MSGSIZE], char stateBuf[MSGSIZE])
    {
        ssize_t nbytes;

        nbytes = -1;
        if ((nbytes = read(vanillaPipe[0], pipeBuf, MSGSIZE)) > 0)
        {
            nbytes = -1;
        }
        nbytes = -1;
        if ((nbytes = read(statePipe[0], stateBuf, MSGSIZE)) > 0)
        {
            nbytes = -1;
        }
    }
};

// Validation tests

TEST_F(TrafficLightUnitTest, CarLightNormalRoutine)
{
    NormalRoutineTransition inputs[] = {
        NormalRoutineTransition::RED_TO_YELLOW,
        NormalRoutineTransition::YELLOW_TO_GREEN,
        NormalRoutineTransition::GREEN_TO_YELLOW,
        NormalRoutineTransition::YELLOW_TO_RED};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expected[s] = {
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::GREEN,
        NormalRoutineState::YELLOW,
        NormalRoutineState::RED};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));
        // State state = static_cast<State>(std::stoi(std::string(stateBuf)));

        EXPECT_EQ(nrState, expected[i]) << "i: " << i;
        // ASSERT_STREQ(inbuf, ANSI_RED);
    }
}

TEST_F(TrafficLightUnitTest, CarLightUnchanged)
{
    Transition inputs[] = {
        Transition::NONE,
        Transition::RED_TO_YELLOW,
        Transition::NONE,
        Transition::YELLOW_TO_GREEN,
        Transition::NONE,
        Transition::GREEN_TO_YELLOW,
        Transition::NONE,
        Transition::YELLOW_TO_RED,
        Transition::NONE};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expected[s] = {
        NormalRoutineState::RED,
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::GREEN,
        NormalRoutineState::GREEN,
        NormalRoutineState::YELLOW,
        NormalRoutineState::YELLOW,
        NormalRoutineState::RED,
        NormalRoutineState::RED};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));
        // State state = static_cast<State>(std::stoi(std::string(stateBuf)));

        EXPECT_EQ(nrState, expected[i]) << "i: " << i;
        // ASSERT_STREQ(inbuf, ANSI_RED);
    }
}

TEST_F(TrafficLightUnitTest, CarLightBlinkingYellow)
{
    Transition inputs[] = {
        Transition::RED_TO_YELLOW,
        Transition::BLINKING_YELLOW,
        Transition::NONE,
        Transition::NONE,
        Transition::NONE,
        Transition::BLINKING_YELLOW_STOP,
        Transition::RED_TO_YELLOW};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expectedNrState[s] = {
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::YELLOW,
        NormalRoutineState::BLACK,
        NormalRoutineState::YELLOW,
        NormalRoutineState::BLACK,
        NormalRoutineState::RED,
        NormalRoutineState::YELLOWRED};
    State expectedState[s] = {
        State::NormalRoutine,
        State::BlinkingYellow,
        State::BlinkingYellow,
        State::BlinkingYellow,
        State::BlinkingYellow,
        State::NormalRoutine,
        State::NormalRoutine};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));
        State state = static_cast<State>(std::stoi(std::string(stateBuf)));

        EXPECT_EQ(nrState, expectedNrState[i]) << "i: " << i;
        EXPECT_EQ(state, expectedState[i]) << "i: " << i;
    }
}

TEST_F(TrafficLightUnitTest, CarLightEmergency)
{
    Transition inputs[] = {
        Transition::RED_TO_YELLOW,
        Transition::EMERGENCY_VEHICLE,
        Transition::NONE,
        Transition::NONE,
        Transition::NONE,
        Transition::EMERGENCY_VEHICLE_PASSED,
        Transition::RED_TO_YELLOW};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expectedNrState[s] = {
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::RED,
        NormalRoutineState::BLACK,
        NormalRoutineState::RED,
        NormalRoutineState::BLACK,
        NormalRoutineState::RED,
        NormalRoutineState::YELLOWRED};
    State expectedState[s] = {
        State::NormalRoutine,
        State::BlinkingRed,
        State::BlinkingRed,
        State::BlinkingRed,
        State::BlinkingRed,
        State::NormalRoutine,
        State::NormalRoutine};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));
        State state = static_cast<State>(std::stoi(std::string(stateBuf)));

        EXPECT_EQ(nrState, expectedNrState[i]) << "i: " << i;
        EXPECT_EQ(state, expectedState[i]) << "i: " << i;
    }
}

TEST_F(TrafficLightUnitTest, CarLightNormalToError)
{
    Transition inputs[] = {
        Transition::YELLOW_TO_GREEN,
        Transition::ERROR_FIXED};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expected[s] = {
        NormalRoutineState::ERROR,
        NormalRoutineState::RED};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));

        EXPECT_EQ(nrState, expected[i]) << "i: " << i;
    }
}

// Defect tests

TEST_F(TrafficLightUnitTest, CarLightInvalidTransition)
{
    int inputs[] = {
        -1};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expected[s] = {
        NormalRoutineState::ERROR};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string((inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));

        EXPECT_EQ(nrState, expected[i]) << "i: " << i;
    }
}

TEST_F(TrafficLightUnitTest, CarLightEmergencyToBlinkingYellow)
{
    Transition inputs[] = {
        // normal -> emergency -> blinking yellow -> normal
        Transition::RED_TO_YELLOW,
        Transition::EMERGENCY_VEHICLE,
        Transition::BLINKING_YELLOW,
        Transition::EMERGENCY_VEHICLE_PASSED,
        Transition::BLINKING_YELLOW_STOP,
        Transition::RED_TO_YELLOW};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expectedNrState[s] = {
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::RED,
        NormalRoutineState::RED,
        NormalRoutineState::YELLOW,
        NormalRoutineState::RED,
        NormalRoutineState::YELLOWRED};
    State expectedState[s] = {
        State::NormalRoutine,
        State::BlinkingRed,
        State::BlinkingRed,
        State::BlinkingYellow,
        State::NormalRoutine,
        State::NormalRoutine};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));
        State state = static_cast<State>(std::stoi(std::string(stateBuf)));

        EXPECT_EQ(nrState, expectedNrState[i]) << "i: " << i;
        EXPECT_EQ(state, expectedState[i]) << "i: " << i;
    }
}

TEST_F(TrafficLightUnitTest, CarLightBlinkingYellowToEmergencyToBlinkingYellow)
{
    Transition inputs[] = {
        // normal -> blinking yellow -> emergency -> blinking yellow -> normal
        Transition::RED_TO_YELLOW,
        Transition::BLINKING_YELLOW,
        Transition::EMERGENCY_VEHICLE,
        Transition::EMERGENCY_VEHICLE_PASSED,
        Transition::BLINKING_YELLOW_STOP,
        Transition::RED_TO_YELLOW};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expectedNrState[s] = {
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::YELLOW,
        NormalRoutineState::RED,
        NormalRoutineState::YELLOW,
        NormalRoutineState::RED,
        NormalRoutineState::YELLOWRED};
    State expectedState[s] = {
        State::NormalRoutine,
        State::BlinkingYellow,
        State::BlinkingRed,
        State::BlinkingYellow,
        State::NormalRoutine,
        State::NormalRoutine};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));
        State state = static_cast<State>(std::stoi(std::string(stateBuf)));

        EXPECT_EQ(nrState, expectedNrState[i]) << "i: " << i;
        EXPECT_EQ(state, expectedState[i]) << "i: " << i;
    }
}

TEST_F(TrafficLightUnitTest, CarLightBlinkingYellowToEmergency)
{
    Transition inputs[] = {
        // normal -> blinking yellow -> emergency -> normal
        Transition::RED_TO_YELLOW,
        Transition::BLINKING_YELLOW,
        Transition::EMERGENCY_VEHICLE,
        Transition::BLINKING_YELLOW_STOP,
        Transition::EMERGENCY_VEHICLE_PASSED,
        Transition::RED_TO_YELLOW};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expectedNrState[s] = {
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::YELLOW,
        NormalRoutineState::RED,
        NormalRoutineState::BLACK,
        NormalRoutineState::RED,
        NormalRoutineState::YELLOWRED};
    State expectedState[s] = {
        State::NormalRoutine,
        State::BlinkingYellow,
        State::BlinkingRed,
        State::BlinkingRed,
        State::NormalRoutine,
        State::NormalRoutine};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));
        State state = static_cast<State>(std::stoi(std::string(stateBuf)));

        EXPECT_EQ(nrState, expectedNrState[i]) << "i: " << i;
        EXPECT_EQ(state, expectedState[i]) << "i: " << i;
    }
}

TEST_F(TrafficLightUnitTest, CarLightMultiEmergency)
{
    Transition inputs[] = {
        Transition::RED_TO_YELLOW,
        Transition::EMERGENCY_VEHICLE,
        Transition::EMERGENCY_VEHICLE,
        Transition::EMERGENCY_VEHICLE_PASSED,
        Transition::NONE,
        Transition::EMERGENCY_VEHICLE_PASSED,
        Transition::RED_TO_YELLOW};
    const int s = sizeof(inputs) / sizeof(inputs[0]);
    NormalRoutineState expectedNrState[s] = {
        NormalRoutineState::YELLOWRED,
        NormalRoutineState::RED,
        NormalRoutineState::BLACK,
        NormalRoutineState::RED,
        NormalRoutineState::BLACK,
        NormalRoutineState::RED,
        NormalRoutineState::YELLOWRED};
    State expectedState[s] = {
        State::NormalRoutine,
        State::BlinkingRed,
        State::BlinkingRed,
        State::BlinkingRed,
        State::BlinkingRed,
        State::NormalRoutine,
        State::NormalRoutine};

    for (int i = 0; i < s; i++)
    {
        write(colorPipe[1], std::to_string(TO_INT(inputs[i])).c_str(), 2);

        // read pipe buffer, because somthing exists in pipe buffer indicates that the light has finished transition
        char pipeBuf[MSGSIZE], stateBuf[MSGSIZE];
        readBuf(pipeBuf, stateBuf);
        NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(pipeBuf)));
        State state = static_cast<State>(std::stoi(std::string(stateBuf)));

        EXPECT_EQ(nrState, expectedNrState[i]) << "i: " << i;
        EXPECT_EQ(state, expectedState[i]) << "i: " << i;
    }
}

// Component tests

class ControllerTest : public ::testing::Test
{
protected:
    const int _numberTrafficLights = 4;
    const int amount_before_blinking_yellow = 8;
    const int amount_before_blinking_red = 16;
    const int amount_before_normal_again = 24;
    // extra 4 iterations for transition from EMERGENCY to NORMAL_ROUTINE
    const int amount_complete_loop = amount_before_normal_again + 4;

    Controller *conM;
    std::jthread *conThd;
    int testPipe[2];

    // run at the beginning of each test
    void SetUp() override
    {
        conM = new Controller(_numberTrafficLights, amount_before_blinking_yellow, amount_before_blinking_red, amount_before_normal_again);
        EXPECT_FALSE(pipe(testPipe) < 0) << "error creating testPipe";
        conM->setTestPipe(testPipe);

        conThd = new std::jthread(conM->spawn());
    }

    // // run at the end of each test
    // void TearDown() override {}

    void readBuf(char nrsBuf[10][MSGSIZE], char stateBuf[10][MSGSIZE])
    {
        ssize_t nbytes;

        nbytes = -1;
        if ((nbytes = read(testPipe[0], nrsBuf, sizeof(char) * 10 * MSGSIZE)) > 0)
        {
            nbytes = -1;
        }

        nbytes = -1;
        if ((nbytes = read(testPipe[0], stateBuf, sizeof(char) * 10 * MSGSIZE)) > 0)
        {
            nbytes = -1;
        }
    }

    bool canCarPassThrough(State state, NormalRoutineState nrState)
    {
        if (state == State::NormalRoutine && (nrState == NormalRoutineState::GREEN || nrState == NormalRoutineState::YELLOW))
        {
            return true;
        }
        // let's ignore BLINKING_YELLOW for now
        return false;
    }
};

TEST_F(ControllerTest, CrossRoadNormalRoutine)
{
    char nrsBuf[10][MSGSIZE], stateBuf[10][MSGSIZE];

    // 2 complete loops to make sure the transtion from 1 loop to another is alright
    for (int j = 0; j < amount_complete_loop * 2; j++)
    {
        readBuf(nrsBuf, stateBuf);
        NormalRoutineState nrState[_numberTrafficLights];
        State state[_numberTrafficLights];
        for (int i = 0; i < _numberTrafficLights; i++)
        {
            nrState[i] = static_cast<NormalRoutineState>(std::stoi(std::string(nrsBuf[i])));
            state[i] = static_cast<State>(std::stoi(std::string(stateBuf[i])));
            // std::cout << i << ' ' << state[i] << ' ' << nrState[i] << std::endl;
        }

        // checking: cars won't bump into other cars
        for (int i = 0; i < _numberTrafficLights; i++)
        {
            switch (i)
            {
            // 0: top; 2: bottom
            case 0:
            case 2:
                if (canCarPassThrough(state[i], nrState[i]))
                {
                    EXPECT_FALSE(canCarPassThrough(state[1], nrState[1]));
                    EXPECT_FALSE(canCarPassThrough(state[3], nrState[3]));
                }
                break;

            // 1: left; 3: right
            case 1:
            case 3:
                if (canCarPassThrough(state[i], nrState[i]))
                {
                    EXPECT_FALSE(canCarPassThrough(state[0], nrState[0]));
                    EXPECT_FALSE(canCarPassThrough(state[2], nrState[2]));
                }
                break;

            default:
                break;
            }
        }
    }
    // std::cout << std::endl;
}

TEST_F(ControllerTest, CrossRoadBlinkingYellow)
{
    char nrsBuf[10][MSGSIZE], stateBuf[10][MSGSIZE];

    // blinking: ON -> OFF -> ON -> OFF...
    bool blinking_on = true;

    // 2 complete loops to make sure the transtion from 1 loop to another is alright
    for (int j = 0; j < amount_complete_loop * 2; j++)
    {
        readBuf(nrsBuf, stateBuf);
        NormalRoutineState nrState[_numberTrafficLights];
        State state[_numberTrafficLights];

        std::cout << "j: " << j << " blinking_on: " << std::boolalpha << blinking_on << std::endl;
        for (int i = 0; i < _numberTrafficLights; i++)
        {
            nrState[i] = static_cast<NormalRoutineState>(std::stoi(std::string(nrsBuf[i])));
            state[i] = static_cast<State>(std::stoi(std::string(stateBuf[i])));
            std::cout << i << ' ' << state[i] << ' ' << nrState[i] << std::endl;
        }
        // checking: whether blinking at BLINKING_YELLOW state
        if (j % amount_complete_loop >= amount_before_blinking_yellow && j % amount_complete_loop < amount_before_blinking_red)
        {
            for (int i = 0; i < _numberTrafficLights; i++)
            {
                EXPECT_EQ(state[i], State::BlinkingYellow) << "wrong state at iteration " << j;
                EXPECT_EQ(nrState[i], blinking_on ? NormalRoutineState::YELLOW : NormalRoutineState::BLACK) << "wrong NRState at iteration " << j;
            }
            blinking_on = !blinking_on;
        }
        else
        {
            blinking_on = true;
        }
    }
    // std::cout << std::endl;
}

TEST_F(ControllerTest, CrossRoadBlinkingRed)
{
    char nrsBuf[10][MSGSIZE], stateBuf[10][MSGSIZE];

    // blinking: ON -> OFF -> ON -> OFF...
    bool blinking_on = true;

    // 2 complete loops to make sure the transtion from 1 loop to another is alright
    for (int j = 0; j < amount_complete_loop * 2; j++)
    {
        readBuf(nrsBuf, stateBuf);
        NormalRoutineState nrState[_numberTrafficLights];
        State state[_numberTrafficLights];

        std::cout << "j: " << j << " blinking_on: " << std::boolalpha << blinking_on << std::endl;
        for (int i = 0; i < _numberTrafficLights; i++)
        {
            nrState[i] = static_cast<NormalRoutineState>(std::stoi(std::string(nrsBuf[i])));
            state[i] = static_cast<State>(std::stoi(std::string(stateBuf[i])));
            std::cout << i << ' ' << state[i] << ' ' << nrState[i] << std::endl;
        }
        // checking: whether blinking at BLINKING_RED state
        if (j % amount_complete_loop >= amount_before_blinking_red && j % amount_complete_loop < amount_before_normal_again)
        {
            for (int i = 0; i < _numberTrafficLights; i++)
            {
                EXPECT_EQ(state[i], State::BlinkingRed) << "wrong state at iteration " << j;
                EXPECT_EQ(nrState[i], blinking_on ? NormalRoutineState::RED : NormalRoutineState::BLACK) << "wrong NRState at iteration " << j;
            }
            blinking_on = !blinking_on;
        }
        else
        {
            blinking_on = true;
        }
    }
    // std::cout << std::endl;
}
