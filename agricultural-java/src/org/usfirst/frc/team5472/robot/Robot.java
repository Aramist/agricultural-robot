/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package org.usfirst.frc.team5472.robot;

import edu.wpi.first.wpilibj.TimedRobot;

public class Robot extends TimedRobot {

	private static boolean disabled; //  Disabled by Jetson
	private Communication comm;
	
	private Control control;
	private Callbacks callbacks;
	
	@Override
	public void robotInit() {
		this.control = new Control();
		this.callbacks = new Callbacks(control);
		
		comm = new Communication(callbacks.driveCallback, callbacks.tableCallback);
	}
	
	@Override
	public boolean isDisabled() {
		return disabled || super.isDisabled();
	}

	
	public static void disable() {
		disabled = true;
	}
	
	
	/**
	 * Tele-op group.
	 */
	
	@Override
	public void teleopInit() {
		disabled = false;
	}
	
	@Override
	public void teleopPeriodic() {
		control.sendMessages(comm);
	}
	
	
	/**
	 * Disabled group
	 */
	
	@Override
	public void disabledInit() {}
	
	@Override
	public void disabledPeriodic() {}

	
	/**
	 * Autonomous group. Probably not going to use this.
	 */
	
	@Override
	public void autonomousInit() {}
	
	@Override
	public void autonomousPeriodic() {}
	
	
	/**
	 * Probably not going to use anything here.
	 */
	
	@Override
	public void testInit() {}
	
	@Override
	public void testPeriodic() {}
}
