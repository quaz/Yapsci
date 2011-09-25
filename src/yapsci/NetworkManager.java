package yapsci;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

public class NetworkManager {
    
    private class ListenWorker extends Thread {

        private ServerSocket serverSocket;
        private int port;
        
        public ListenWorker(int port) {
            this.port = port;
        }

        @Override
        public void run() {
            System.out.println("ListenWorker" + port + " started");
            try {
                serverSocket = new ServerSocket(port);
            } catch (IOException ex) {
                interrupt();
            }
            
            while (!isInterrupted()) {
                try {
                    Socket socket = serverSocket.accept();
                    registerConnection(socket);
                } catch (IOException ex) {
                    interrupt();
                }
            }
            System.out.println("ListenWorker " + port + " stopped");
        }
        
        public void halt () {
            if (serverSocket != null)
                try {
                    serverSocket.close();
                } catch (IOException ex) {
                    //unhandled exception
                }
            interrupt();
        }
    }
    
    private ConnectionManager connectionManager;

    public NetworkManager(ConnectionManager connectionManager) {
        this.connectionManager = connectionManager;
        listenWorkers = new HashMap<Integer, ListenWorker>();
    }
    
    private synchronized void registerConnection (Socket socket) {
        System.out.println("New Connection:" + socket.getInetAddress().toString());
        connectionManager.addConnection(socket);
    }
    
    private HashMap<Integer, ListenWorker> listenWorkers;
    
    void startListen (int port) {
        if (!listenWorkers.containsKey(port))
            listenWorkers.put(port, new ListenWorker(port));
        
        ListenWorker listenWorker = listenWorkers.get(port);
        if (!listenWorker.isAlive())
            listenWorker.start();
    }
    
    void stopListen (int port) {
        if (!listenWorkers.containsKey(port)) return;
        listenWorkers.get(port).halt();
    }
    
    void stopListen () {
        for (ListenWorker listenWorker : listenWorkers.values()) {
            listenWorker.halt();
        }
    }
}
