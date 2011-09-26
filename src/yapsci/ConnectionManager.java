package yapsci;

import java.net.Socket;
import java.util.HashMap;

public class ConnectionManager {

    HashMap<String, Connection> connections;
    MessageProcessor messageProcessor;
    String clientId;

    ConnectionManager(String clientId, MessageProcessor messageProcessor) {
        this.clientId = clientId;
        this.messageProcessor = messageProcessor;
        connections = new HashMap<String, Connection>();
    }

    synchronized void addConnection(Socket socket) {
        Connection connection = new Connection(socket, clientId);
        connections.put(clientId, connection);
    }

    void halt() {
        for (Connection c : connections.values()) {
            c.halt();
        }
        connections.clear();
    }

    void stopConnection(String clientID) {
        Connection c = connections.get(clientID);
        if (c != null) {
            c.halt();
        }
    }
}
