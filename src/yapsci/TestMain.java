package yapsci;

import java.io.IOException;

public class TestMain {
    public static void main (String[] args) throws IOException {
        MessageProcessor messageProcessor =  new MessageProcessor();
        ConnectionManager connectionManager = new ConnectionManager("42",messageProcessor);
        NetworkManager networkManager = new NetworkManager(connectionManager);
        networkManager.startListen(1338);
        System.in.read();
        networkManager.stopListen();
    }
}
