package org.usfirst.frc.team5472.robot.modules;

import com.google.protobuf.Message;
import org.usfirst.frc.team5472.robot.proto.RobotMsgs;
import org.usfirst.frc.team5472.robot.proto.RobotMsgs.IMU.Builder;

import com.kauailabs.navx.frc.AHRS;

import edu.wpi.first.wpilibj.SPI;

public class IMU {
    private AHRS navx;
    private String frame;

    public IMU(String frame) {
        navx = new AHRS(SPI.Port.kMXP);
        this.frame = frame;
    }

    public Message getMessage() {
        return RobotMsgs.IMU.newBuilder()
                .setRawAccelX(navx.getRawAccelX())
                .setRawAccelY(navx.getRawAccelY())
                .setRawAccelZ(navx.getRawAccelZ())
                .setRawGyroX(navx.getRawGyroX())
                .setRawGyroY(navx.getRawGyroY())
                .setRawGyroZ(navx.getRawGyroZ())
                .setName(frame)
                .build();
    }
}
