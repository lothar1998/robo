package com.robo.peripheral_devices;

/**
 * Class implementation of led
 */
public class Led implements Device {

    /**
     * led pin
     */
    public enum Pin{

        PIN0(0),
        PIN1(1),
        PIN2(2),
        PIN3(3),
        PIN4(4),
        PIN5(5),
        PIN6(6),
        PIN7(7),
        PIN8(8),
        PIN9(9),
        PIN10(10),
        PIN11(11),
        PIN12(12),
        PIN13(13),
        PIN14(14),
        PIN15(15),
        PIN16(16),
        PIN17(17),
        PIN18(18),
        PIN19(19),
        PIN20(20),
        PIN21(21),
        PIN22(22),
        PIN23(23),
        PIN24(24),
        PIN25(25),
        PIN26(26),
        PIN27(27),
        PIN28(28),
        PIN29(29);


        private int value;

        Pin(int value){
            this.value=value;
        }

        /**
         * getter to enum value
         * @return enum value
         */
        public int getInt(){
            return this.value;
        }
    }

    /**
     * number of led pin
     */
    private Pin pin;

    /**
     * device id
     */
    private static int commandNumber=2;

    /**
     * construct Led object
     * @param pin number of led pin
     */
    public Led(Pin pin){
        this.pin=pin;
    }

    /**
     * turn on led
     * @see #setLed(int)
     * @return command to send
     */
    public int on(){
        return setLed(0);
    }

    /**
     * turn off led
     * @see #setLed(int)
     * @return command to send
     */
    public int off(){
        return setLed(1);
    }

    /**
     * generate command to send
     * @param val id of function
     * @return command
     */
    private int setLed(int val){

        int command = commandNumber;
        command<<=28;

        int pin=this.pin.getInt();
        pin<<=20;

        val<<=16;

        command+=pin+val;

        return command;
    }


}