/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/PWMVictorSPX.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/controller/PIDController.h>
#include "Constants.h"

class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem( std::function<double()> currentAngle );

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
   void Periodic() override;

  // Subsystem methods go here.

  /**
   * Drives the robot using arcade controls.
   *
   * @param fwd the commanded forward movement
   * @param rot the commanded rotation
   */
  void ArcadeDrive(double fwd, double rot);

  /**
   * Sets the max output of the drive.  Useful for scaling the drive to drive
   * more slowly.
   *
   * @param maxOutput the maximum output to which the drive will be constrained
   */
  void SetMaxOutput(double maxOutput);

  bool RotateToTarget();

  double GetAngle();

  int m_pidCounter;
  frc2::PIDController m_pid;
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  // The motor controllers
  frc::PWMVictorSPX m_left1;
  frc::PWMVictorSPX m_left2;
  frc::PWMVictorSPX m_right1;
  frc::PWMVictorSPX m_right2;

  // The motors on the left side of the drive
  frc::MotorControllerGroup m_leftMotors{m_left1, m_left2};

  // The motors on the right side of the drive
  frc::MotorControllerGroup m_rightMotors{m_right1, m_right2};

  // The robot's drive
  frc::DifferentialDrive m_drive{m_leftMotors, m_rightMotors};

  std::function<double()> m_currentAngle;

  int m_goodAngleCount;


};
