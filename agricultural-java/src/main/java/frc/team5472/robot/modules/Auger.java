package frc.team5472.robot.modules;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.can.VictorSPX;
import edu.wpi.first.networktables.NetworkTable;
import frc.team5472.robot.Consts;
import org.json.JSONObject;

public class Auger {

    private String name;
    private VictorSPX motor;

    private boolean enabled;
    private double speed;

    public Auger(int id, String name) {
        motor = new VictorSPX(id);
        this.name = name;
    }

    public void off() {
        enabled = false;
        motor.set(ControlMode.PercentOutput, 0);
    }

    public void forward() {
        enabled = true;
        speed = Consts.AUGER_SPEED;
        motor.set(ControlMode.PercentOutput, Consts.AUGER_SPEED);
    }

    public void reverse() {
        enabled = true;
        speed = -Consts.AUGER_SPEED;
        motor.set(ControlMode.PercentOutput, -Consts.AUGER_SPEED);
    }

    public int getDirection() {
        return (int) Math.signum(speed);
    }

    public void sendMessage(NetworkTable table) {
        table.getEntry(name + "enabled").setBoolean(enabled);
        table.getEntry(name + "direction").setNumber((int)Math.signum(speed));
    }

}
