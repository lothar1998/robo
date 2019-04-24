package peripheral_devices;

public class Led implements Device {

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

        public int getInt(){
            return this.value;
        }
    }

    private Pin pin;
    private static int commandNumber=2;

    public Led(Pin pin){
        this.pin=pin;
    }

    public int on(){
        return setLed(0);
    }

    public int off(){
        return setLed(1);
    }

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
