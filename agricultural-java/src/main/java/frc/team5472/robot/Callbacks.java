package frc.team5472.robot;

import org.json.JSONObject;

public class Callbacks {

    /**
     * Callback template for when a message is received
     *
     * @author aramist
     */
    public interface MessageCallback {
        void run(JSONObject command);
    }

    private Control control;

    public Callbacks(Control control) {
        this.control = control;
    }


    public Callbacks.MessageCallback driveCallback = new MessageCallback() {
        @Override
        public void run(JSONObject command) {
            if (command.getString("name").equalsIgnoreCase("lead_drive"))
                control.driveLead(command.getDouble("left"), command.getDouble("right"));
            else if (command.getString("name").equalsIgnoreCase("trail_drive"))
                control.driveTrail(command.getDouble("left"), command.getDouble("right"));
        }
    };

    public Callbacks.MessageCallback tableCallback = new MessageCallback() {
        @Override
        public void run(JSONObject command) {
            control.setTableSetpoint(command.getInt("x"), command.getInt("y"));
        }
    };
}
