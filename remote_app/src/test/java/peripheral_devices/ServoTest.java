package peripheral_devices;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ServoTest {

    private static Servo s2;
    private static Servo s13;

    @BeforeAll
    static void createServo(){
        s2 = new Servo(Servo.Channel.CH2);
        s13 = new Servo(Servo.Channel.CH13);
        assertNotNull(s2);
        assertNotNull(s13);
    }

    @Test
    void setServoAngleTest(){
        assertEquals(0x02000168,s2.setServoAngle(360));
        assertEquals(0x0D000016,s13.setServoAngle(22));
    }

    @Test
    void setServoMinTest(){
        assertEquals(0x02010000,s2.setServoMin());
        assertEquals(0x0D010000,s13.setServoMin());
    }

    @Test
    void setServoMidTest(){
        assertEquals(0x02020000,s2.setServoMid());
        assertEquals(0x0D020000,s13.setServoMid());
    }

    @Test
    void setServoMaxTest(){
        assertEquals(0x02030000,s2.setServoMax());
        assertEquals(0x0D030000,s13.setServoMax());
    }
}