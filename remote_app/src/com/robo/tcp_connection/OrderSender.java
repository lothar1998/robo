package com.robo.tcp_connection;

import java.io.DataOutputStream;
import java.net.InetAddress;
import java.net.Socket;

/**
 * Class implementation of TCP sender
 */
public class OrderSender {

    private Socket socket;
    private DataOutputStream out;

    /**
     * construct OrderSender object
     * @param inetAddress address ip
     * @param port port
     * @throws Exception caused by creating a socket and getting output stream
     */
    public OrderSender(InetAddress inetAddress, int port) throws Exception{
        this.socket =  new Socket(inetAddress,port);
        this.out = new DataOutputStream(this.socket.getOutputStream());
    }

    /**
     * send a message
     * @param command message to send
     * @throws Exception caused by sending message through socket
     */
    public void send(int command) throws Exception{
        out.writeInt(Integer.reverseBytes(command));
    }

    /**
     * closing connection
     * @throws Exception caused by closing socket
     */
    public void close() throws Exception{
        socket.close();
    }
}