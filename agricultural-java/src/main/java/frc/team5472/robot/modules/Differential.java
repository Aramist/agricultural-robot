package frc.team5472.robot.modules;

import org.json.JSONObject;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.can.VictorSPX;

import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Differential {

    private VictorSPX frontLeft;
    private VictorSPX frontRight;
//
    private VictorSPX rearLeft;
    private VictorSPX rearRight;

    private String frame;

    /**
     * Initializes the speed controllers
     *
     * @param fl PWM ID of the front left motor
     * @param fr PWM ID of the front right motor
     * @param bl PWM ID of the back left motor
     * @param br PWM ID of the back right motor
     */
    public Differential(int fl, int fr, int bl, int br, String frame) {
        frontLeft = new VictorSPX(fl);
        frontRight = new VictorSPX(fr);
        rearLeft = new VictorSPX(bl);
        rearRight = new VictorSPX(br);
        this.frame = frame;
    }

    public void drive(double left, double right) {
        frontLeft.set(ControlMode.PercentOutput, left);
        rearLeft.set(ControlMode.PercentOutput, left);

        frontRight.set(ControlMode.PercentOutput, right);
        rearRight.set(ControlMode.PercentOutput, right);
    	
        SmartDashboard.putString(frame, "{Left: " + left + ", Right: " + right + "}");
    }
    
    public void invert(boolean left, boolean front) {
    	if(left) {
    		if(front)
    			frontLeft.setInverted(true);
    		else
    			rearLeft.setInverted(true);
    	} else {
    		if(front)
    			frontRight.setInverted(true);
    		else
    			rearRight.setInverted(true);
    	}
    }

    /**
     * @return Current encoder readings for this drive train
     */
    public JSONObject getEncoders() {
        JSONObject json = new JSONObject();
        json.put("name", frame + "_encoders");
        json.put("left", 0);
        json.put("right", 0);
        return json;
    }
}
