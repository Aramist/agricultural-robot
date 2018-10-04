package frc.team5472.robot.modules;

import java.util.ArrayList;

import org.json.JSONObject;

import edu.wpi.first.wpilibj.Joystick;

public class Joy {

    private int id;
    private Joystick stick;

    public Joy(int id) {
        this.id = id;
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
    
    public JSONObject getMessage() {
    	JSONObject json = new JSONObject();
    	
    	json.put("name", String.format("joy_%d", id));
    	
    	ArrayList<Float> axes = new ArrayList<Float>();
        for (int i = 0; i < stick.getAxisCount(); i++)
            axes.add((float) stick.getRawAxis(i));
        json.put("axes", axes);
        
        ArrayList<Integer> buttons = new ArrayList<Integer>();
        for (int i = 0; i < stick.getButtonCount(); i++)
            buttons.add(stick.getRawButton(i) ? 1 : 0);
        json.put("buttons", buttons);

        return json;
    }
}
