package yapsci;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class Connection {
    
    private Socket socket;
    private String serverID;
    private String clientID;
    private MessageProcessor messageProcessor;
    private BufferedWriter writer;
    private ConnectionReader reader;

    public Connection(Socket socket, String serverID) {
        this.socket = socket;
        this.serverID = serverID;
        this.messageProcessor = new MessageProcessor();
    }
    
    private synchronized Socket getSocket () {
        return socket;
    }
    
    private synchronized String getServerID () {
        return serverID;
    }
    
    private synchronized String getClientID () {
        return clientID;
    }
    
    private class ConnectionReader extends Thread {
        
        BufferedReader reader;
        
        public ConnectionReader(Socket socket) {
            try {
                reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            } catch (IOException ex) {
                System.err.println(ex);
            }
        }

        @Override
        public void run() {
            System.out.println("ConnectionReader "+getClientID()+" started");
            
            while (!isInterrupted()) {
                try {
                    String input = reader.readLine();
                    if (input == null) interrupt();
                    else messageIn(input, getClientID());
                } catch (IOException ex) {
                    interrupt();
                }
            }
            
            System.out.println("ConnectionReader "+getClientID()+" stopped");
        }
        
        public void halt () {
            if (getSocket() != null)
                try {
                    getSocket().close();
                } catch (IOException ex) {
                    //unhandled exception
                }
            interrupt();
        }
        
    }
    
    void messageIn (String input, String clientID) {
        messageProcessor.messageIn(input, clientID, this);
    }
    
    void messageOut (String output) {
        if (writer == null) return;
        try {
            writer.write(output);
        } catch (IOException ex) {
            halt();
        }
    }
    
    boolean start () {
        reader = new ConnectionReader(socket);
        reader.start();
        try {
            writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        } catch (IOException ex) {
            return true;
        }
        return false;
    }
    
    void halt () {
        if (reader != null) {
            reader.halt();
            reader = null;
        }
        if (writer != null) writer = null;
    }
}
