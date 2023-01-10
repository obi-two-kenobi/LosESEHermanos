#include <pt.h>

int measures[2000] = {};
int i=0;
struct pt pt1;
struct pt pt2;
struct pt pt3;
enum class Transition {
  ERROR = 0,
  ERROR_FIXED = 1,
  EMERGENCY_VEHICLE_PASSED = 2,
  EMERGENCY_VEHICLE = 3,
  ERROR_UNFIXABLE = 4,
  NONE = 5,
  BLINKING_YELLOW = 6,
  BLINKING_YELLOW_STOP = 7
};
//std::ostream& operator << ( std::ostream& outs, const Transition& p );


enum class NormalRoutineTransition {
  RED_TO_YELLOW = 0,
  YELLOW_TO_GREEN = 1,
  GREEN_TO_YELLOW = 2,
  YELLOW_TO_RED = 3

};
NormalRoutineTransition &operator++(NormalRoutineTransition &c);
NormalRoutineTransition operator++(NormalRoutineTransition &c, int);
//std::ostream& operator << ( std::ostream& outs, const NormalRoutineTransition& p );

NormalRoutineTransition &operator++(NormalRoutineTransition &c) {
  ;
  c = static_cast<NormalRoutineTransition>(static_cast<int>(c) + 1);
  if (c == static_cast<NormalRoutineTransition>(4))
    c = static_cast<NormalRoutineTransition>(0);
  return c;
}

// Special behavior for Colors++
NormalRoutineTransition operator++(NormalRoutineTransition &c, int) {
  NormalRoutineTransition result = c;
  ++c;
  return result;
}


enum class NormalRoutineState {
  RED = 8,
  YELLOW = 9,
  GREEN = 10,
  ERROR = 4
};
enum class State {

  SafeMode,
  BlinkingRed,
  BlinkingYellow,
  NormalRoutine,
  Idle

};






static uint8_t _pinRed = 2;
static uint8_t _pinYellow = 3;
static uint8_t _pinGreen = 4;
State _state = State::Idle;
NormalRoutineState _normalRoutineState = NormalRoutineState::RED;
NormalRoutineTransition _transition = NormalRoutineTransition::RED_TO_YELLOW;




bool IsWorkintTime() {
  delay(6000);
  /*
  long randNumber;
     randNumber = random(1, 11);
    if(randNumber  <= 4 )
        return true;
    else
        return false;*/
  return true;
}


bool IsBlinkingYellowTime() {
  long randNumber;
  randNumber = random(1, 11);
  if (randNumber <= 1)
    return true;
  else
    return false;
}

bool sim_IsVehicleComing() {
  long randNumber;
  randNumber = random(1, 11);
  if (randNumber <= 1)
    return true;
  else
    return false;
}

bool sim_IsVehicleThrough() {

  delay(6000);
  /*
  long randNumber;
     randNumber = random(1, 11);
    if(randNumber  <= 4 )
        return true;
    else
        return false;*/
  return true;
}





static void BlinkingYellowRoutine(struct pt *pt) {
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while (_state == State::BlinkingYellow) {
    digitalWrite(_pinYellow, HIGH);
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 250);
    digitalWrite(_pinYellow, LOW);
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 250);
  }
  PT_END(pt);
}

static void EmergencyVehicleRoutine(struct pt *pt) {
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while (_state == State::BlinkingRed) {
    digitalWrite(_pinRed, HIGH);
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 250);
    digitalWrite(_pinRed, 0);
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 250);

  }
  PT_END(pt);
}





void TurnLEDsOFF() {
  digitalWrite(_pinRed, LOW);
  digitalWrite(_pinYellow, LOW);
  digitalWrite(_pinGreen, LOW);
}



void NormalRoutine(struct pt *pt) {
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while (_state == State::NormalRoutine) {
    //Serial.println(int(_transition));
    switch (_normalRoutineState) {
      case NormalRoutineState::RED:
       
        digitalWrite(_pinYellow, LOW);
        digitalWrite(_pinGreen, LOW);
        digitalWrite(_pinRed, HIGH);
        lastTimeBlink = millis();
        PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 2000);
       if (_transition == NormalRoutineTransition::RED_TO_YELLOW) {
          _normalRoutineState = NormalRoutineState::YELLOW;
          _transition = NormalRoutineTransition::YELLOW_TO_GREEN;
         break;
        }
        
        break;

      case NormalRoutineState::YELLOW:
        digitalWrite(_pinYellow, HIGH);
        digitalWrite(_pinGreen, LOW);
        digitalWrite(_pinRed, LOW);

        if (_transition == NormalRoutineTransition::YELLOW_TO_GREEN) {
          //("OO");
          _normalRoutineState = NormalRoutineState::GREEN;
          _transition = NormalRoutineTransition::GREEN_TO_YELLOW;
          digitalWrite(_pinRed, HIGH);
          lastTimeBlink = millis();
          PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 2000);
          break;

        } else if (_transition == NormalRoutineTransition::YELLOW_TO_RED) {
          lastTimeBlink = millis();
          PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 2000);
          _normalRoutineState = NormalRoutineState::RED;
          _transition = NormalRoutineTransition::RED_TO_YELLOW;
        break;
        } else {
         // _normalRoutineState = NormalRoutineState::ERROR;
          //Serial.println("AA");
        }
        break;

      case NormalRoutineState::GREEN:
        digitalWrite(_pinYellow, LOW);
        digitalWrite(_pinRed, LOW);
        digitalWrite(_pinGreen, HIGH);
        lastTimeBlink = millis();
        PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 2000);
        if (_transition == NormalRoutineTransition::GREEN_TO_YELLOW) {
          _normalRoutineState = NormalRoutineState::YELLOW;
          _transition = NormalRoutineTransition::YELLOW_TO_RED;
          break;
        }
        //_normalRoutineState = NormalRoutineState::ERROR;
        break;

      default:
        _state = State::SafeMode;
        break;
    }
    //_transition++;
  }
  PT_END(pt);
  //this->TurnLEDsOFF();
}

unsigned long test;

void HandleTransition(Transition transition) {
  switch (_state) {
    case State::NormalRoutine:
      {
        
        

        if ((transition == Transition::EMERGENCY_VEHICLE || sim_IsVehicleComing() ) && (millis() - test > 10000)) {
          test = millis();
          _state = State::BlinkingRed;
          TurnLEDsOFF();
          return;
        }
        

        unsigned long start = micros();
/*SECOND BRANCH*/
        if ((IsBlinkingYellowTime() || transition == Transition::BLINKING_YELLOW) && (millis() - test > 10000)) {
          _state = State::BlinkingYellow;
          TurnLEDsOFF();
          test = millis();
          return;
        }
        unsigned long end = micros();
        unsigned long delta = end - start;
        /*END SECOND BRANCH*/



        measures[i] = delta;
        NormalRoutine(&pt1);
      }
      break;
    case State::Idle:
      // following the state machine, it goes directly to the normal routine
      // we initialize it as well
      _state = State::NormalRoutine;
      //_normalRoutineState = NormalRoutineState::RED;
      //_transition = NormalRoutineTransition::RED_TO_YELLOW;
      break;
    case State::BlinkingYellow:

      /*
             Blink Yellow
             */

      BlinkingYellowRoutine(&pt2);
      /* if(transition == Transition::EMERGENCY_VEHICLE || sim_IsVehicleComing())
            {
                 TurnLEDsOFF();
                _state=State::BlinkingRed;
                _normalRoutineState = NormalRoutineState::RED;
                return;
            }
            */
      //if ( IsWorkintTime() || transition == Transition::BLINKING_YELLOW_STOP)
      if (millis() - test > 3000) {
        _state = State::NormalRoutine;
        _transition = NormalRoutineTransition::RED_TO_YELLOW;
        _normalRoutineState = NormalRoutineState::RED;
        test = millis();
        TurnLEDsOFF();
        return;
      }


      break;
    case State::BlinkingRed:
      /*
             Blink Red
             */
      EmergencyVehicleRoutine(&pt3);
      //if (transition == Transition::EMERGENCY_VEHICLE_PASSED || sim_IsVehicleThrough() )
      if (millis() - test > 3000) {

        _state = State::NormalRoutine;
        _normalRoutineState = NormalRoutineState::RED;
        _transition = NormalRoutineTransition::RED_TO_YELLOW;
        
        test = millis();
        TurnLEDsOFF();
        return;
      }



      break;
    case State::SafeMode:
      //in this case, we are going to just quit;
      //std::cout << "\n\n THE ERROR WAS UNFIXABLE \n\n";
      //Serial.print(" THE ERROR WAS UNFIXABLE");
      //exit(1);
    default:
      break;
  }
}



char *toChar(int p) {
  switch (p) {
    case int(State::Idle):
      return "Idle";
      break;
    case int(State::NormalRoutine):
      return "NormalRoutine";
      break;
    case int(State::SafeMode):
      return "SafeMode";
      break;
    case int(State::BlinkingRed):
      return "BlinkingRed";
      break;
    case int(State::BlinkingYellow):
      return "BlinkingYellow";
      break;
    case int(NormalRoutineState::RED):
      return "RED";
      break;
    case int(NormalRoutineState::YELLOW):
      return "YELLOW";
      break;
    case int(NormalRoutineState::GREEN):
      return "GREEN";
      break;
    default:
      return "ERROR";
      break;
  }
}

void Feedback() {
  Serial.print("[");
  Serial.print(toChar(int(_state)));
  Serial.print("]->[");
  Serial.print(toChar(int(_normalRoutineState)));
  Serial.print("]\n");
  //Serial.println(int(_transition));
}


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  pinMode(_pinRed, OUTPUT);
  pinMode(_pinGreen, OUTPUT);
  pinMode(_pinYellow, OUTPUT);
  PT_INIT(&pt1);
  PT_INIT(&pt3);
  PT_INIT(&pt2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(1){
    HandleTransition(Transition::NONE);
    /*i++;
    if(i == 2000)
    {
      for(int j = 0;j<2000;j++){
            Serial.print(measures[j]);
            Serial.print(",");
      }
      Serial.print("}\n");
    }*/
  }
  
  //Feedback();
  //delay(100);
}
