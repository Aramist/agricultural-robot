package org.usfirst.frc.team5472.robot;

import com.google.protobuf.Any;

public class Control {
	
	private Differential frontDrive;
	private Differential rearDrive;
	private XYTable table;
	
	private IMU rearImu;
	private Joy stick;
	
	public Control() {
		//  0, 1, 4, and 5 were all inverted, but I don't know which motors they referred to
		frontDrive = new Differential(0, 1, 2, 3);
		rearDrive = new Differential(4, 5, 6, 7);
		
		table = new XYTable();
		
		rearImu = new IMU();
		
		stick = new Joy(0);
	}
	
	public void sendMessages(Communication comms) {
		comms.send(Any.pack(
			frontDrive.getEncoders().setName("front").build()
		));
		
		comms.send(Any.pack(
			rearDrive.getEncoders().setName("rear").build()
		));
		
		comms.send(Any.pack(
			rearImu.getMessage().setName("rear").build()
		));
		
		comms.send(Any.pack(
			stick.getMessage().setName("0").build()
		));
		
		comms.send(Any.pack(
			table.getPosition()
		));
	}
	
	public void driveFront(double left, double right) {
		frontDrive.drive(left, right);
	}
	
	public void driveRear(double left, double right) {
		rearDrive.drive(left, right);
	}
	
	public void setTableSetpoint(int x, int y) {
		table.set(x, y);
	}
}
