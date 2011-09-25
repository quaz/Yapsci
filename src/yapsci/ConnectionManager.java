package yapsci;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.HashMap;

public class ConnectionManager {

    HashMap<String, Socket> sockets;
    String serverId;

    ConnectionManager(String serverId) {
        this.serverId = serverId;
        sockets = new HashMap<String, Socket>();
    }

    void addConnection(Socket socket) {
        BufferedWriter bw = null;
        BufferedReader br = null;
        try {
            // Init Id Exchange
            bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            bw.write(serverId);
            bw.newLine();
            bw.flush();
            br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String clientId = br.readLine();
            
            sockets.put(clientId, socket);
            initConnection(clientId);
        } catch (IOException ex) {
        } finally {
            try {
                bw.close();
            } catch (IOException ex) {
            }
            try {
                br.close();
            } catch (IOException ex) {
            }
        }
    }

    private void initConnection(String clientId) {
        // Init Data Exchange
    }
}
