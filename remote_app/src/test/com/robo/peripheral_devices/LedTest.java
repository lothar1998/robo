package test.com.robo.peripheral_devices;

import com.robo.peripheral_devices.Led;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class LedTest {

    private static Led led;

    @BeforeAll
    static void createObjectTest(){
        led = new Led(Led.Pin.PIN21);
        assertNotNull(led);
    }

    @Test
    void on() {
        assertEquals(0x21500000,led.on());
    }

    @Test
    void off() {
        assertEquals(0x21510000,led.off());
    }
}