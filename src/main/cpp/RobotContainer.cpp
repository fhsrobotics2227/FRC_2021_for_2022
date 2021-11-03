/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/XboxController.h>
#include <frc2/command/button/JoystickButton.h>

#include <RobotContainer.h>

#include "frc2/command/button/Button.h"


RobotContainer::RobotContainer() :
  m_driveSubsystem{
    [this] { return m_gyro.GetAngle(); }
  }, 
  m_defaultDriveCommand{
    &m_driveSubsystem,
    [this] { return -m_driverController.GetLeftY( );  },
    [this] { return -m_driverController.GetRightX( ); }
  },
  m_prepareToShootCommand{
    &m_driveSubsystem,
    &m_shooterSubsystem,
    &m_intakeSubsystem,
    false,
    [this] { return -m_driverController.GetRightX( ); }
  },
  m_intakePowerCellsCommand{
    &m_intakeSubsystem,
    &m_indexerSubsystem
  },
  m_defaultIntakeControlCommand{
    &m_intakeSubsystem
  },
  m_raiseIntakeCommand{
    &m_intakeSubsystem
  },
  m_lowerIntakeCommand{
    &m_intakeSubsystem
  },
  m_changeShooterAngleComand{
    &m_shooterSubsystem,
    &m_intakeSubsystem,
    [this] { return m_driverController.GetRightBumper( ); },
    [this] { return m_driverController.GetLeftBumper( ); }
  },
  m_stopShooterCommand{
    &m_shooterSubsystem
  },
  m_indexerInCommand{
     &m_indexerSubsystem
  },
  m_indexerOutCommand{
     &m_indexerSubsystem
  },
  m_indexerStopCommand{
     &m_indexerSubsystem
  },
  m_intakeInCommand{
     &m_intakeSubsystem
  },
  m_intakeOutCommand{
     &m_intakeSubsystem
  },
  m_intakeStopCommand{
     &m_intakeSubsystem
  },
  m_angleShooterUp{
     &m_shooterSubsystem
  },
  m_angleShooterDown{
     &m_shooterSubsystem
  },
  m_shooterHoldAngle{
     &m_shooterSubsystem
  },
  m_fullyLowerShooter{
    &m_shooterSubsystem
  },
  m_autoThreeBallShoot{
    &m_driveSubsystem,
    &m_shooterSubsystem,
    &m_intakeSubsystem,
    &m_indexerSubsystem
  }
{
  // Initialize all of your commands and subsystems here
  InTestMode = false;

  m_gyro.InitGyro();
  m_gyro.Calibrate();

  // Set up default subsystem commands
  m_driveSubsystem.SetDefaultCommand( m_defaultDriveCommand );
  //m_intakeSubsystem.SetDefaultCommand( m_defaultIntakeControlCommand );
  m_shooterSubsystem.SetDefaultCommand( m_stopShooterCommand );
  m_indexerSubsystem.SetDefaultCommand( m_indexerStopCommand );

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  frc2::InstantCommand loadShooter{ [this] { m_indexerSubsystem.LoadShooter(); },  {&m_indexerSubsystem}};
  // Configure your button bindings here
  frc::XboxController* driverController = &m_driverController;

  /*frc2::Button LeftTrigger = frc2::Button([driverController] {
          return ( driverController->GetTriggerAxis( frc::XboxController::kLeftStick ) > 0.1 );
        });*/

  frc2::Button RightTrigger = frc2::Button([driverController] {
          return ( driverController->GetRightTriggerAxis( ) > 0.8 );
        }); 


  frc2::Button LeftTrigger = frc2::Button([driverController] {
          return ( driverController->GetLeftTriggerAxis( ) > 0.8 );
        }); 

  frc2::JoystickButton( &m_driverController, (int)frc::XboxController::Button::kA )
      .WhenPressed( m_lowerIntakeCommand );

  frc2::JoystickButton( &m_driverController, (int)frc::XboxController::Button::kB )
      .WhenPressed( m_raiseIntakeCommand );

  frc2::JoystickButton( &m_driverController, (int)frc::XboxController::Button::kY )
      .WhileHeld( m_intakePowerCellsCommand );

  //frc2::JoystickButton( &m_driverController, (int)frc::XboxController::Button::kX )
  //    .WhileHeld( m_prepareToShootCommand );

  LeftTrigger.WhileHeld( m_prepareToShootCommand );

  frc2::JoystickButton( &m_driverController, (int)frc::XboxController::Button::kLeftBumper )
      .WhileHeld( m_angleShooterDown );

  frc2::JoystickButton( &m_driverController, (int)frc::XboxController::Button::kRightBumper )
      .WhileHeld( m_angleShooterUp );

  RightTrigger.WhileHeld( loadShooter );
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  //return &m_autonomousCommand;
  return &m_autoThreeBallShoot;
}
