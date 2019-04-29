package test.com.robo.tcp_connection;

import com.robo.tcp_connection.OrderSender;
import org.junit.jupiter.api.Test;
import java.net.Inet4Address;
import java.net.InetAddress;
import static org.junit.jupiter.api.Assertions.*;

class OrderSenderTest {

    @Test
    void connectionTest() throws Exception{
        OrderSender sender = new OrderSender(InetAddress.getByName("192.168.1.18"),10000);
        assertNotNull(sender);
        sender.send(0xFFFFFFFF);
        sender.close();

    }

}