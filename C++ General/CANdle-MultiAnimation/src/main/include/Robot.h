/**
 * Phoenix Software License Agreement
 *
 * Copyright (C) Cross The Road Electronics.  All rights
 * reserved.
 * 
 * Cross The Road Electronics (CTRE) licenses to you the right to 
 * use, publish, and distribute copies of CRF (Cross The Road) firmware files (*.crf) and 
 * Phoenix Software API Libraries ONLY when in use with CTR Electronics hardware products
 * as well as the FRC roboRIO when in use in FRC Competition.
 * 
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * CROSS THE ROAD ELECTRONICS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, 
 * INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
 */
/**
 * Description:
 * The CANdle MultiAnimation example demonstrates using multiple animations with CANdle.
 * This example has the robot using a Command Based template to control the CANdle.
 * 
 * This example uses:
 * - A CANdle wired on the CAN Bus, with a 5m led strip attached for the extra animatinos.
 * 
 * Controls (with Xbox controller):
 * Right Bumper: Increment animation
 * Left Bumper: Decrement animation
 * Start Button: Switch to setting the first 8 LEDs a unique combination of colors
 * POV Right: Configure maximum brightness for the CANdle
 * POV Down: Configure medium brightness for the CANdle
 * POV Left: Configure brightness to 0 for the CANdle
 * POV Up: Change the direction of Rainbow and Fire, must re-select the animation to take affect
 * A: Print the VBat voltage in Volts
 * B: Print the 5V voltage in Volts
 * X: Print the current in amps
 * Y: Print the temperature in degrees C
 * 
 * This example uses a development build based on 5.21.2.
 * 
 * Supported Version:
 * 	- CANdle: 22.1.1.0
 */

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>

#include "RobotContainer.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc2::Command* m_autonomousCommand = nullptr;

  RobotContainer m_container;
};
