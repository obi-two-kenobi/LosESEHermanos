#include <pt.h>

#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLACK   "\x1b[0m"


enum class Transition
{
    ERROR  = 0,
    ERROR_FIXED = 1,
    EMERGENCY_VEHICLE_PASSED = 2,
    EMERGENCY_VEHICLE = 3,
    ERROR_UNFIXABLE = 4,
    NONE = 5,
    BLINKING_YELLOW  =6,
    BLINKING_YELLOW_STOP = 7
};
//std::ostream& operator << ( std::ostream& outs, const Transition& p );


enum class NormalRoutineTransition
{
    RED_TO_YELLOW = 0,
    YELLOW_TO_GREEN = 1,
    GREEN_TO_YELLOW = 2,
    YELLOW_TO_RED = 3
    
};
NormalRoutineTransition& operator++( NormalRoutineTransition &c ) ;
NormalRoutineTransition operator++( NormalRoutineTransition &c, int );
//std::ostream& operator << ( std::ostream& outs, const NormalRoutineTransition& p );

enum class NormalRoutineState
{
    RED,
    YELLOW,
    GREEN,
    ERROR
};
enum class State
{
    
    SafeMode,
    BlinkingRed,
    BlinkingYellow,
    NormalRoutine,
    Idle
    
};

//std::ostream& operator << ( std::ostream& outs, const NormalRoutineState& p );
//std::ostream& operator << ( std::ostream& outs, const State& p );


class TrafficLight
{
public:
    virtual ~TrafficLight() = default;
    
    virtual void Update()=0;
    virtual void Feedback() = 0;
    virtual void Delay(unsigned int milliseconds)=0;
    virtual bool IsWorkintTime();
    virtual bool IsBlinkingYellowTime();
    virtual void NormalRoutine(struct pt *pt);
  	void TurnLEDsOFF();
    virtual void EmergencyVehicleRoutine(struct pt *pt);
    virtual void BlinkingYellowRoutine(struct pt *pt);
};


enum class Mode
{
    SIMPLE,
    DOUBLE,
    QUADRI
};
//std::ostream& operator << ( std::ostream& outs, const Mode& p );
Mode& operator--( Mode &c ) ;
Mode operator--( Mode &c, int );

Mode& operator++( Mode &c ) ;
Mode operator++( Mode &c, int );






NormalRoutineTransition& operator++( NormalRoutineTransition &c ) {
    ;
  c = static_cast<NormalRoutineTransition>( static_cast<int>(c) + 1 );
  if ( c == static_cast<NormalRoutineTransition>(4) )
    c = static_cast<NormalRoutineTransition>(0);
  return c;
}

// Special behavior for Colors++
NormalRoutineTransition operator++( NormalRoutineTransition &c, int ) {
  NormalRoutineTransition result = c;
  ++c;
  return result;
}



Mode& operator--( Mode &c )
{
    
  c = static_cast<Mode>( static_cast<int>(c) - 1 );
  if ( c == static_cast<Mode>(-1) )
    c = static_cast<Mode>(2);
  return c;
}
Mode operator--( Mode &c, int )
{
    Mode result = c;
  --c;
  return result;
}


Mode& operator++( Mode &c )
{
    
  c = static_cast<Mode>( static_cast<int>(c) + 1 );
  if ( c == static_cast<Mode>(3) )
    c = static_cast<Mode>(0);
  return c;
}
Mode operator++( Mode &c, int )
{
    Mode result = c;
  ++c;
  return result;
}



bool TrafficLight::IsWorkintTime()
{
  long randNumber;
    randNumber = random(1, 11);
    if(randNumber  <= 3 )
        return true;
    else
        return false;
}


bool TrafficLight::IsBlinkingYellowTime()
{
  long randNumber;
     randNumber = random(1, 11);
    if(randNumber  <= 1 )
        return true;
    else
        return false;
}

bool sim_IsVehicleComing()
{
  long randNumber;
     randNumber = random(1, 11);
    if(randNumber  <= 1 )
        return true;
    else
        return false;
}

bool sim_IsVehicleThrough()
{
  long randNumber;
     randNumber = random(1, 11);
    if(randNumber  <= 4 )
        return true;
    else
        return false;
}





////SIMPLE TRAFFIC LIGHT

class SimpleTrafficLight: public TrafficLight
{
public:

    SimpleTrafficLight(State state = State::Idle,
                       NormalRoutineTransition transition = NormalRoutineTransition::RED_TO_YELLOW,
                       char* name = "TRAFFIC LIGHT",
                       double delay = 1000, 
                       uint8_t pinRed = 2,
                       uint8_t pinYellow = 3,
                       uint8_t pinGreen = 4
                       );
    void Update();
    
    void Feedback();
    
    void Delay(unsigned int milliseconds);
    
    void InitialFeedback();
    void NormalRoutine(struct pt *pt);
    char* toChar ( NormalRoutineState p );
  	char* toChar (  State p );
    
    struct pt pt1;
    
    void TurnLEDsOFF()
    {
      digitalWrite(_pinRed, LOW);
      digitalWrite(_pinYellow, LOW);
      digitalWrite(_pinGreen, LOW);
    }
    
    int protothreadBlinkLED1(struct pt *pt)
    {
      static unsigned long lastTimeBlink = 0;
      PT_BEGIN(pt);
      while(1) {
        lastTimeBlink = millis();
        PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 1000);
        digitalWrite(6, HIGH);
        lastTimeBlink = millis();
        PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 1000);
        digitalWrite(6, LOW);
      }
      PT_END(pt);
    }
    void EmergencyVehicleRoutine(struct pt *pt);
    void BlinkingYellowRoutine(struct pt *pt);

private:
    void HandleTransition(Transition transition = Transition::NONE);
    
    
    State _state;
    NormalRoutineState _normalRoutineState;
    NormalRoutineTransition _transition;
    char* _name;
    double _delay;
    uint8_t _pinRed;
    uint8_t _pinYellow;
    uint8_t _pinGreen;

    
};

void SimpleTrafficLight::BlinkingYellowRoutine(struct pt *pt){
  digitalWrite(_pinYellow, HIGH);
    this->Delay(300);
    digitalWrite(_pinYellow, LOW);
    this->Delay(300);
}

void SimpleTrafficLight::EmergencyVehicleRoutine(struct pt *pt)
{
    digitalWrite(_pinRed, HIGH);
    this->Delay(300);
    digitalWrite(_pinRed, LOW);
    this->Delay(300);
}


void SimpleTrafficLight::NormalRoutine(struct pt *pt)
{
    switch (_normalRoutineState) {
        case NormalRoutineState::RED:
           digitalWrite(_pinYellow, LOW);
            digitalWrite(_pinGreen, LOW);
            digitalWrite(_pinRed, HIGH);
            this->Delay(1000);
            if (_transition == NormalRoutineTransition::RED_TO_YELLOW) {
                _normalRoutineState = NormalRoutineState::YELLOW;
                 break;
            }
            _normalRoutineState = NormalRoutineState::ERROR; 
            break;
            
        case NormalRoutineState::YELLOW:
            digitalWrite(_pinYellow, HIGH);
            digitalWrite(_pinGreen, LOW);
            digitalWrite(_pinRed, LOW);
            
            if (_transition == NormalRoutineTransition::YELLOW_TO_GREEN) {
                _normalRoutineState =  NormalRoutineState::GREEN;
                digitalWrite(_pinRed, HIGH);
                this->Delay(1000);
                break;
                
            }else if (_transition == NormalRoutineTransition::YELLOW_TO_RED){
                this->Delay(1000);
                _normalRoutineState = NormalRoutineState::RED;
                break;
            }
            _normalRoutineState = NormalRoutineState::ERROR;
            break;
        
        case NormalRoutineState::GREEN:
         digitalWrite(_pinYellow, LOW);
            digitalWrite(_pinRed, LOW);
              digitalWrite(_pinGreen, HIGH);
              this->Delay(1000);
            if (_transition==NormalRoutineTransition::GREEN_TO_YELLOW) {
                _normalRoutineState =  NormalRoutineState::YELLOW;
                break;
            }
            _normalRoutineState = NormalRoutineState::ERROR;
            break;
            
        default:
            _normalRoutineState = NormalRoutineState::ERROR;
            break;
    }
  //this->TurnLEDsOFF();
  this->_transition++;
}


char* SimpleTrafficLight::toChar ( NormalRoutineState p )
{
    switch (p) {
        case NormalRoutineState::RED:
            return  "RED" ;
            break;
        case NormalRoutineState::YELLOW:
            return   "YELLOW" ;
            break;
        case NormalRoutineState::GREEN:
            return   "GREEN" ;
            break;
        default:
            return "ERROR";
            break;
    }
}

char* SimpleTrafficLight::toChar (  State p )
{
    switch (p) {
        case State::Idle:
            return   "Idle" ;
            break;
        case State::NormalRoutine:
            return   "NormalRoutine" ;
            break;
        case State::SafeMode:
            return  "SafeMode" ;
            break;
        case State::BlinkingRed:
            return    "BlinkingRed" ;
            break;
        case State::BlinkingYellow:
            return    "BlinkingYellow" ;
            break;
        
        default:
            return  "ERROR";
            break;
    }
}


SimpleTrafficLight::SimpleTrafficLight(State state,NormalRoutineTransition transition,char* name,double delay,uint8_t pinRed, uint8_t pinYellow, uint8_t pinGreen)
:_state(state),_transition(transition),_name( name),_delay(delay), _normalRoutineState(NormalRoutineState::RED),_pinRed(pinRed),_pinYellow(pinYellow),_pinGreen(pinGreen)
{
    this->InitialFeedback();
    PT_INIT(&this->pt1);
    
    
};
void SimpleTrafficLight::InitialFeedback(){
  	Serial.print("NAME   |   STATE   |   TRANSITION\n");
  	Serial.print("[");
    Serial.print(_name);
    Serial.print("]->[");
    Serial.print(toChar(_state));
  	Serial.print("]->[");
    //Serial.print(toChar(_normalRoutineState));
  	Serial.print("]\n");
  
}
void SimpleTrafficLight::Update()
{
   
    this->HandleTransition();
    this->Feedback();
    //this->Delay(10000000);
    //this->HandleTransition(Transition::EMERGENCY_VEHICLE);
    
    
    
        
}
void SimpleTrafficLight::Delay(unsigned int milliseconds)
{
    delay(milliseconds);
}



void SimpleTrafficLight::Feedback()
{
    Serial.print("[");
    Serial.print(_name);
    Serial.print("]->[");
    Serial.print(toChar(_state));
  	Serial.print("]->[");
    //Serial.print(toChar(_normalRoutineState));
  	Serial.print("]\n");
}




void SimpleTrafficLight::HandleTransition(Transition transition) {
    
    
    
    switch (_state) {
        case State::NormalRoutine:
                if(transition == Transition::EMERGENCY_VEHICLE || sim_IsVehicleComing())
                {
                    _state = State::BlinkingRed;
                    this->TurnLEDsOFF();
                    return;
                }
                 if (this->IsBlinkingYellowTime() || transition == Transition::BLINKING_YELLOW) {
                  _state=State::BlinkingYellow;
                  //this->NormalRoutine(&this->pt1);
                  this->TurnLEDsOFF();
                  
                  return;
                }
                this->NormalRoutine(&this->pt1);

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
            
            this->BlinkingYellowRoutine(&this->pt1);
            if(transition == Transition::EMERGENCY_VEHICLE || sim_IsVehicleComing())
            {
                this->TurnLEDsOFF();
                _state=State::BlinkingRed;
                _normalRoutineState = NormalRoutineState::RED;
                return;
            }
            
            if (this->IsWorkintTime() || transition == Transition::BLINKING_YELLOW_STOP) {
                _state = State::NormalRoutine;
                _normalRoutineState = NormalRoutineState::RED;
                _transition = NormalRoutineTransition::RED_TO_YELLOW;
                return;
            }
            
            
            break;
        case State::BlinkingRed:
            /*
             Blink Red
             */
             EmergencyVehicleRoutine(&this->pt1);
            if (transition == Transition::EMERGENCY_VEHICLE_PASSED || sim_IsVehicleThrough() ) {
              this->TurnLEDsOFF();
                _state = State::NormalRoutine;
                _normalRoutineState = NormalRoutineState::RED;
                _transition = NormalRoutineTransition::RED_TO_YELLOW;
                return;
            }
            
            
            
            break;
        case State::SafeMode:
            //in this case, we are going to just quit;
            //std::cout << "\n\n THE ERROR WAS UNFIXABLE \n\n";
      		Serial.print("\n\n THE ERROR WAS UNFIXABLE \n\n");
            //exit(1);
        default:
            break;
    }
}



SimpleTrafficLight ampel = SimpleTrafficLight();

void setup()
{
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  
}

void loop()
{

  ampel.Update();
}