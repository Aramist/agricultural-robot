package frc.team5472.robot.modules;

import org.json.JSONObject;

import com.kauailabs.navx.frc.AHRS;

import edu.wpi.first.wpilibj.SPI;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class IMU {
    private AHRS navx;
    private String frame;

    public IMU(String frame) {
        navx = new AHRS(SPI.Port.kMXP);
        this.frame = frame;
    }

    public JSONObject getMessage() {
    	JSONObject json = new JSONObject();
    	
    	json.put("name", frame);
    	
    	json.put("gyro_x", navx.getRawGyroX());
    	json.put("gyro_y", navx.getRawGyroX());
    	json.put("gyro_z", navx.getRawGyroX());
    	
    	json.put("accel_x", navx.getRawAccelX());
    	json.put("accel_y", navx.getRawAccelX());
    	json.put("accel_z", navx.getRawAccelX());
    	
    	SmartDashboard.putString("imu", json.toString());
    	return json;
    }
}
