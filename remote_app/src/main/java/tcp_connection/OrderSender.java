package tcp_connection;

import java.io.DataOutputStream;
import java.net.InetAddress;
import java.net.Socket;

public class OrderSender {

    private Socket socket;
    private DataOutputStream out;

    public OrderSender(InetAddress inetAddress, int port) throws Exception{
        this.socket =  new Socket(inetAddress,port);
        this.out = new DataOutputStream(this.socket.getOutputStream());
    }

    public void send(int command) throws Exception{
        out.writeInt(Integer.reverseBytes(command));
    }

    public void close() throws Exception{
        socket.close();
    }
}
