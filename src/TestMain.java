package yapsci;

import java.io.IOException;

public class TestMain {
    public static void main (String[] args) throws IOException {
        ConnectionManager connectionManager = new ConnectionManager("42");
        NetworkManager networkManager = new NetworkManager(connectionManager);
        networkManager.startListen(1338);
        System.in.read();
        networkManager.stopListen();
    }
}
