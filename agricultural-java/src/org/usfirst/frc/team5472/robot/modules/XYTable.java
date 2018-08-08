package org.usfirst.frc.team5472.robot.modules;

import org.usfirst.frc.team5472.robot.proto.RobotMsgs;

public class XYTable {

    private int xPosition;
    private int yPosition;

    private int xSetpoint;
    private int ySetpoint;


    /**
     * Sets the table's setpoint to (x,y). Currently does nothing.
     *
     * @param x
     * @param y
     */
    public void set(int x, int y) {
        xSetpoint = x;
        xPosition = x;
        ySetpoint = y;
        yPosition = y;
    }

    public int getX() {
        return xPosition;
    }

    public int getY() {
        return yPosition;
    }

    public int getXSetpoint() {
        return xSetpoint;
    }

    public int getYSetpoint() {
        return ySetpoint;
    }

    public RobotMsgs.XYTable getPosition() {
        return RobotMsgs.XYTable.newBuilder()
                .setX(xPosition)
                .setY(yPosition)
                .build();
    }
}
