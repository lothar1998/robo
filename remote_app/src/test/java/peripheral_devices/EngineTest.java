package peripheral_devices;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class EngineTest {

    static Engine engineLeft;
    static Engine engineRight;

    @BeforeAll
    static void createObjectTest(){
        engineLeft = new Engine(Engine.Channel.CHL);
        engineRight = new Engine(Engine.Channel.CHR);
        assertNotNull(engineLeft);
        assertNotNull(engineRight);
    }

    @Test
    void startEngine() {
        assertEquals(0x1000E400,engineLeft.startEngine(Engine.Direction.FORWARD,100));
        assertEquals(0x1100E400,engineRight.startEngine(Engine.Direction.FORWARD,100));
    }

    @Test
    void startEngine1() {
        assertEquals(0x1001A4FF,engineLeft.startEngine(Engine.Direction.FORWARD,36,255));
        assertEquals(0x1101A4FF,engineRight.startEngine(Engine.Direction.FORWARD,36,255));
    }

    @Test
    void startEngineMin() {
        assertEquals(0x10028000,engineLeft.startEngineMin(Engine.Direction.FORWARD));
        assertEquals(0x11028000,engineRight.startEngineMin(Engine.Direction.FORWARD));
    }

    @Test
    void startEngineMin1() {
        assertEquals(0x100300AA,engineLeft.startEngineMin(Engine.Direction.BACKWARD,170));
        assertEquals(0x110300AA,engineRight.startEngineMin(Engine.Direction.BACKWARD,170));
    }

    @Test
    void startEngineMid() {
        assertEquals(0x10040000,engineLeft.startEngineMid(Engine.Direction.BACKWARD));
        assertEquals(0x11040000,engineRight.startEngineMid(Engine.Direction.BACKWARD));
    }

    @Test
    void startEngineMid1() {
        assertEquals(0x100580B5,engineLeft.startEngineMid(Engine.Direction.FORWARD,181));
        assertEquals(0x110580B5,engineRight.startEngineMid(Engine.Direction.FORWARD,181));
    }

    @Test
    void startEngineMax() {
        assertEquals(0x10060000,engineLeft.startEngineMax(Engine.Direction.BACKWARD));
        assertEquals(0x11060000,engineRight.startEngineMax(Engine.Direction.BACKWARD));
    }

    @Test
    void startEngineMax1() {
        assertEquals(0x10078077,engineLeft.startEngineMax(Engine.Direction.FORWARD,119));
        assertEquals(0x11078077,engineRight.startEngineMax(Engine.Direction.FORWARD,119));
    }

    @Test
    void stopEngineImmediately() {
        assertEquals(0x10088000,engineLeft.stopEngineImmediately());
        assertEquals(0x11088000,engineRight.stopEngineImmediately());
    }

    @Test
    void stopEngine() {
        assertEquals(0x10098000,engineLeft.stopEngine());
        assertEquals(0x11098000,engineRight.stopEngine());
    }
}