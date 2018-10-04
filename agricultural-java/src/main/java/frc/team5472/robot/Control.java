package frc.team5472.robot;

import frc.team5472.robot.modules.Differential;
import frc.team5472.robot.modules.IMU;
import frc.team5472.robot.modules.Joy;
import frc.team5472.robot.modules.XYTable;

public class Control {

    private Differential leadDrive;
    private Differential trailDrive;
    private XYTable table;

    private IMU trailImu;
    private Joy stick;

    public Control() {
        leadDrive = new Differential(3, 2, 4, 1, "lead_drive");
        
        leadDrive.invert(false, true);
        leadDrive.invert(false, false);
        
        trailDrive = new Differential(7, 6, 8, 5, "trail_drive");
        
        trailDrive.invert(false, true);
        trailDrive.invert(false, false);

        table = new XYTable();

        trailImu = new IMU("trail_imu");

        stick = new Joy(0);
    }

    public void sendMessages(Communication comms) {
//        comms.send(Any.pack(frontDrive.getEncoders()));

//        comms.send(Any.pack(rearDrive.getEncoders()));

        comms.send(trailImu.getMessage());

//        comms.send(Any.pack(stick.getMessage()));

//        comms.send(Any.pack(table.getPosition()));
    }

    public void driveLead(double left, double right) {
        leadDrive.drive(left, right);
    }

    public void driveTrail(double left, double right) {
        trailDrive.drive(left, right);
    }

    public void setTableSetpoint(int x, int y) {
        table.set(x, y);
    }
    
    public void joystickDrive() {
    	double y = -stick.getY() / 2.0;
    	double tw = stick.getTwist() / 2.0;
    	double l = y + tw;
    	double r = y - tw;
    	driveLead(l, r);
    	driveTrail(y, y);
    }
}
