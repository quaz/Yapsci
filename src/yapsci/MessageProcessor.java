package yapsci;

public class MessageProcessor {

    public void messageIn(String input, String clientID, Connection connection) {
        System.out.println("" + clientID + ": " + input);
    }
}
