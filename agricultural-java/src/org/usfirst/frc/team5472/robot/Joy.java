package org.usfirst.frc.team5472.robot;

import org.usfirst.frc.team5472.robot.proto.RobotMsgs;
import org.usfirst.frc.team5472.robot.proto.RobotMsgs.Joy.Builder;

import edu.wpi.first.wpilibj.Joystick;

public class Joy {
	
	private Joystick stick;
	
	public Joy(int id) {
		stick = new Joystick(id);
	}
	
	public Builder getMessage() {
		Builder b = RobotMsgs.Joy.newBuilder();
		for(int i = 0; i < stick.getAxisCount(); i++)
			b.setAxes(i, (float) stick.getRawAxis(i));
		for(int i = 0; i < stick.getButtonCount(); i++)
			b.setButtons(i, stick.getRawButton(i) ? 1 : 0);
		return b;
	}
}
