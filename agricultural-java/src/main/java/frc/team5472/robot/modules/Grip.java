package frc.team5472.robot.modules;

import edu.wpi.first.networktables.NetworkTable;
import edu.wpi.first.wpilibj.Servo;
import org.json.JSONObject;

public class Grip {

    private int id;
    private String name;
    private Servo servo;

    public Grip(int id, String name) {
        this.id = id;
        this.name = name;
        servo = new Servo(id);
    }

    public void setAngle(double theta) {
        servo.setAngle(theta);
    }

    public void open(){
        servo.setAngle(0);
    }

    public void close(){
        servo.setAngle(90);
    }

    public void sendMessage(NetworkTable table) {
        table.getEntry(name + "angle").setDouble(servo.getAngle());
    }
}
