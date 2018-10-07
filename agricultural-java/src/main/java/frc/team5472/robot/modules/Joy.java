package frc.team5472.robot.modules;

import java.util.ArrayList;

import edu.wpi.first.networktables.NetworkTable;
import edu.wpi.first.networktables.NetworkTableEntry;
import edu.wpi.first.networktables.NetworkTableInstance;
import org.json.JSONObject;

import edu.wpi.first.wpilibj.Joystick;

public class Joy {

    private int id;
    private String name;
    private Joystick stick;

    public Joy(int id, String name) {
        this.id = id;
        this.name = name;
        stick = new Joystick(id);
    }

    public double getY() {
    	return stick.getY();
    }
    
    public double getTwist() {
    	return stick.getTwist();
    }
    
    public boolean getButton(int id) {
    	return stick.getRawButton(id);
    }
    
    public void sendMessage(NetworkTable table) {

        double axes[] = new double[stick.getAxisCount()];
        for(int i = 0; i < stick.getAxisCount(); i++)
            axes[i] = stick.getRawAxis(i);

        Integer buttons[] = new Integer[stick.getButtonCount()];
        for(int i = 1; i < stick.getButtonCount() + 1; i++)
            buttons[i-1] = stick.getRawButton(i) ? 1 : 0;

        NetworkTableEntry axesEntry = table.getEntry(name + "/axes");
        axesEntry.setDoubleArray(axes);
        NetworkTableEntry buttonsEntry = table.getEntry(name + "/buttons");
        buttonsEntry.setNumberArray(buttons);
    }
}
