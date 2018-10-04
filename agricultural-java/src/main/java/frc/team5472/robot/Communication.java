package frc.team5472.robot;

import org.json.JSONObject;
import org.zeromq.ZContext;
import org.zeromq.ZMQ;

import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Communication {

    private long lastReceived;

    private ZContext context;
    private ZMQ.Socket socket;

    private Thread recvThread;

    private Callbacks.MessageCallback differentialCallback;
    private Callbacks.MessageCallback tableCallback;

    public Communication(Callbacks.MessageCallback diffDrive, Callbacks.MessageCallback table) {
        lastReceived = System.currentTimeMillis();
        differentialCallback = diffDrive;
        tableCallback = table;
        try {
            context = new ZContext();
            socket = context.createSocket(ZMQ.PAIR);
            socket.bind("tcp://10.54.72.2:5002");

            recvThread = new Thread() {
                public void run() {
                    while (true)
                        recv();
                }
            };
            recvThread.start();
        } catch (Exception e) {
            e.printStackTrace();
            DriverStation.reportError("Failed to open communication with Jetson", false);
            Robot.disable();
        }
    }


    private void recv() {
        if (!socket.hasReceiveMore())
            return;
        // Determine message type
        String incoming = socket.recvStr();
        SmartDashboard.putString("Last Received: ", incoming);
    }

    /**
     * Sends sensor data (XY table position, encoders, ...) to Jetson
     *
     * @param msg The message to send
     */
    public void send(JSONObject json) {
    	socket.send(json.toString());
    }
}
