package frc.team5472.robot;

import edu.wpi.first.networktables.NetworkTable;
import frc.team5472.robot.modules.*;

public class Control {

    private Differential leadDrive;
    private Differential trailDrive;
    private XYTable table;

    private IMU trailImu;
    private Joy stick;

    private Grip grip;
    private Auger auger;

    public Control() {
        leadDrive = new Differential(3, 2, 4, 1, Consts.LEAD_DRIVE);

        leadDrive.invert(false, true);
        leadDrive.invert(false, false);

        trailDrive = new Differential(8, 7, 9, 6, Consts.TRAIL_DRIVE);

        trailDrive.invert(false, true);
        trailDrive.invert(false, false);

        table = new XYTable(Consts.TABLE);

        trailImu = new IMU(Consts.TRAIL_IMU);

        stick = new Joy(0, Consts.DRIVE_JOYSTICK);

        grip = new Grip(0, Consts.GRIP);
        auger = new Auger(5, Consts.AUGER);
    }

    public void sendMessages(NetworkTable table) {
        trailImu.sendMessage(table);
        stick.sendMessage(table);
        grip.sendMessage(table);
        auger.sendMessage(table);
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

        if(auger.getDirection() > 0 && stick.getButton(Consts.AUGER_FORWARD))
            auger.off();
        else if(auger.getDirection() < 0 && stick.getButton(Consts.AUGER_REVERSE))
            auger.off();
        else if(stick.getButton(Consts.AUGER_FORWARD))
            auger.forward();
        else if(stick.getButton(Consts.AUGER_REVERSE))
            auger.reverse();

        if(stick.getButton(Consts.GRIP_CLOSE))
            grip.close();
        else if(stick.getButton(Consts.GRIP_OPEN))
            grip.open();
    }
}
