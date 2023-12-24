#include <memory>

#include "BLDC_MotorDriver.h"
#include "AS5600_Encoder.h"
#include "CSpeedController.h"
#include "rigs_config.h"
#include "CCommunication.h"
#include "CSerial.h"

#include <vector>
#include <string>

#include <Arduino.h>

std::unique_ptr<CBLDC_MotorDriver> leftMotor;
std::unique_ptr<CBLDC_MotorDriver> rightMotor;
std::unique_ptr<CAS5600> leftEncoder;
std::unique_ptr<CAS5600> rightEncoder;
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
  CAS5600 *leftEncoder = (CAS5600 *)args[0];
  CAS5600 *rightEncoder = (CAS5600 *)args[1];
  CCommunication *communication = (CCommunication *)args[2];
  communication->Send(std::to_string(leftEncoder->GetCount()) + ',' + std::to_string(rightEncoder->GetCount()));
}

void setup()
{
  Serial2.begin(115200);
  leftMotor = std::unique_ptr<CBLDC_MotorDriver>(new CBLDC_MotorDriver(Config::LeftMotor::Enable,Config::LeftMotor::Dir,Config::LeftMotor::Pwm, Config::LeftMotor::DirInverted, Config::LeftMotor::PwmChannel));
  rightMotor = std::unique_ptr<CBLDC_MotorDriver>(new CBLDC_MotorDriver(Config::RightMotor::Enable,Config::RightMotor::Dir,Config::RightMotor::Pwm, Config::RightMotor::DirInverted, Config::RightMotor::PwmChannel));
  leftEncoder = std::unique_ptr<CAS5600>(new CAS5600(Config::LeftMotor::BusNum, Config::LeftMotor::SDAPin, Config::LeftMotor::SCLPin, Config::LeftMotor::DirPin));
  rightEncoder = std::unique_ptr<CAS5600>(new CAS5600(Config::RightMotor::BusNum, Config::RightMotor::SDAPin, Config::RightMotor::SCLPin, Config::RightMotor::DirPin));
  speedController = std::unique_ptr<CSpeedController>(new CSpeedController(*leftMotor, *rightMotor, *leftEncoder, *rightEncoder, {Config::LeftMotor::Kp, Config::LeftMotor::Ki, Config::LeftMotor::Kd, Config::LeftMotor::CountsPerRev}, {Config::RightMotor::Kp, Config::RightMotor::Ki, Config::RightMotor::Kd, Config::RightMotor::CountsPerRev}));
  serial = std::unique_ptr<CSerial>(new CSerial(115200));
  communication = std::unique_ptr<CCommunication>(new CCommunication(*serial, '#', ';'));

  communication->AddCommand('m', {std::vector<void *>{speedController.get(), communication.get()}, SetMotorSpeed});
  communication->AddCommand('e', {std::vector<void *>{leftEncoder.get(), rightEncoder.get(), communication.get()}, GetEncoderCounts});
  leftMotor->SetDirection(EDirection::Forward);
  rightMotor->SetDirection(EDirection::Forward);
  leftMotor->SetSpeed(255);
  rightMotor->SetSpeed(255);
}

unsigned long lastTime = 0;
EDirection direction = EDirection::Forward;

void loop()
{
  if (millis() - lastTime > 10000)
  {
    if (direction == EDirection::Forward)
    {
      direction = EDirection::Backward;
    }
    else
    {
      direction = EDirection::Forward;
    }

    leftMotor->SetDirection(direction);
    rightMotor->SetDirection(direction);
    lastTime = millis();
  }

  Serial2.print(leftEncoder->GetCount());
  Serial2.print(',');
  Serial2.println(rightEncoder->GetCount());
}