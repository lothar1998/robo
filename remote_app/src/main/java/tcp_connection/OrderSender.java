package tcp_connection;

import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class OrderSender {

    private Socket socket;
    private PrintWriter out;

    public OrderSender(InetAddress inetAddress, int port) throws Exception{
        this.socket =  new Socket(inetAddress,port);
        this.out = new PrintWriter(this.socket.getOutputStream(),true);
    }

    public void send(int command){
        out.print(command);
    }

}
