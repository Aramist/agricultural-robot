package frc.team5472.robot.modules;

import edu.wpi.first.networktables.NetworkTable;
import org.json.JSONObject;

import com.kauailabs.navx.frc.AHRS;

import edu.wpi.first.wpilibj.SPI;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class IMU {
    private AHRS navx;
    private String name;

    public IMU(String name) {
        navx = new AHRS(SPI.Port.kMXP);
        this.name = name;
    }

    public void sendMessage(NetworkTable table) {
        table.getEntry(name + "/gyro_x").setDouble(navx.getRawGyroX());
        table.getEntry(name + "/gyro_y").setDouble(navx.getRawGyroY());
        table.getEntry(name + "/gyro_z").setDouble(navx.getRawGyroZ());

        table.getEntry(name + "/accel_x").setDouble(navx.getRawAccelX());
        table.getEntry(name + "/accel_y").setDouble(navx.getRawAccelY());
        table.getEntry(name + "/accel_x").setDouble(navx.getRawAccelZ());
    }
}
