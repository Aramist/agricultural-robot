package frc.team5472.robot.modules;

import edu.wpi.first.networktables.NetworkTable;
import edu.wpi.first.wpilibj.Relay;

public class Grip {

    private int id;
    private String name;
    private Relay servo;

    public Grip(int id, String name) {
        this.id = id;
        this.name = name;
        servo = new Relay(id);
    }

    public boolean isOpen(){
        return servo.get() == Relay.Value.kForward;
    }

    public void open() {
        servo.set(Relay.Value.kForward);
        System.out.println("opening");
    }

    public void close() {
        servo.set(Relay.Value.kReverse);
        System.out.println("closing");
    }

    public void sendMessage(NetworkTable table) {
        table.getEntry(name + "angle").setBoolean(isOpen());
    }
}
