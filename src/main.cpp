#include <memory>

#include "Cytron_MotorController.h"
#include "CWheelEncoder.h"
#include "CSpeedController.h"
#include "rigs_config.h"
#include "CCommunication.h"
#include "CSerial.h"

#include <vector>
#include <string>

std::unique_ptr<Cytron> leftMotor;
std::unique_ptr<Cytron> rightMotor;
std::unique_ptr<CWheelEncoder> leftEncoder;
std::unique_ptr<CWheelEncoder> rightEncoder;
std::unique_ptr<CSpeedController> speedController;
std::unique_ptr<CSerial> serial;
std::unique_ptr<CCommunication> communication;
bool com = false;
String message = "";

const int debounceDelay = 50;
bool lastState = LOW;
unsigned long lastDebounceTime = 0;

static void SetMotorSpeed(std::vector<void *> args, std::string message)
{
  CSpeedController *speedController = (CSpeedController *)args[0];
  CCommunication *communication = (CCommunication *)args[1];
  int commaIndex = message.find(',');
  std::string left_str = message.substr(1, commaIndex - 1);
  std::string right_str = message.substr(commaIndex + 1);
  speedController->SetWheelSpeeds(std::strtod(left_str.c_str(), nullptr), std::strtod(right_str.c_str(), nullptr));
  communication->Send(left_str + ',' + right_str);
}

static void GetEncoderCounts(std::vector<void *> args, std::string message)
{
  CWheelEncoder *leftEncoder = (CWheelEncoder *)args[0];
  CWheelEncoder *rightEncoder = (CWheelEncoder *)args[1];
  CCommunication *communication = (CCommunication *)args[2];
  communication->Send(std::to_string(leftEncoder->GetCount()) + ',' + std::to_string(rightEncoder->GetCount()));
}

void setup()
{
  leftMotor = std::unique_ptr<Cytron>(new Cytron(Config::LeftMotor::Pwm, Config::LeftMotor::Dir, Config::LeftMotor::DirInverted, Config::LeftMotor::Channel));
  rightMotor = std::unique_ptr<Cytron>(new Cytron(Config::RightMotor::Pwm, Config::RightMotor::Dir, Config::RightMotor::DirInverted, Config::RightMotor::Channel));
  leftEncoder = std::unique_ptr<CWheelEncoder>(new CWheelEncoder(Config::LeftMotor::Encoder1, Config::LeftMotor::Encoder2));
  rightEncoder = std::unique_ptr<CWheelEncoder>(new CWheelEncoder(Config::RightMotor::Encoder1, Config::RightMotor::Encoder2));
  speedController = std::unique_ptr<CSpeedController>(new CSpeedController(*leftMotor, *rightMotor, *leftEncoder, *rightEncoder, {Config::LeftMotor::Kp, Config::LeftMotor::Ki, Config::LeftMotor::Kd, Config::LeftMotor::CountsPerRev}, {Config::RightMotor::Kp, Config::RightMotor::Ki, Config::RightMotor::Kd, Config::RightMotor::CountsPerRev}));
  serial = std::unique_ptr<CSerial>(new CSerial(115200));
  communication = std::unique_ptr<CCommunication>(new CCommunication(*serial, '#', ';'));

  communication->AddCommand('m', {std::vector<void *>{speedController.get(), communication.get()}, SetMotorSpeed});
  communication->AddCommand('e', {std::vector<void *>{leftEncoder.get(), rightEncoder.get(), communication.get()}, GetEncoderCounts});
}

void loop()
{
  communication->Receive();
}