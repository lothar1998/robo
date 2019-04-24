package peripheral_devices;

public class Servo implements Device {

    /**
     * numbers of servo's channels
     */
    public enum Channel{
        CH0 (0),
        CH1 (1),
        CH2 (2),
        CH3 (3),
        CH4 (4),
        CH5 (5),
        CH6 (6),
        CH7 (7),
        CH8 (8),
        CH9 (9),
        CH10 (10),
        CH11 (11),
        CH12 (12),
        CH13 (13),
        CH14 (14),
        CH15 (15);

        private int value;

        Channel(int value){
            this.value=value;
        }

        /**
         * getter to value of channel
         * @return value of channel
         */
        public int getInt(){
            return this.value;
        }
    }

    /**
     * servo's channel
     */
    private Channel ch;

    /**
     * device id
     */
    private static int commandNumber = 0;

    /**
     * construct servo object
     * @param ch number of servo's channel
     */
    public Servo(Channel ch){
        this.ch=ch;
    }

    /**
     *
     * @param angle set servo's angle - max 360 = 180°
     * @see #setServo(int, int)
     * @return command to send
     */
    public int setServoAngle(int angle){

        if(angle>=0&&angle<=360) {

            return setServo(angle,0);
        }
        else
            return 0;
    }

    /**
     * set servo's minimum angle = 0°
     * @see #setServo(int, int)
     * @return command to send
     */
    public int setServoMin(){

        return setServo(0,1);
    }

    /**
     * set servo's medium angle = 90°
     * @see #setServo(int, int)
     * @return command to send
     */
    public int setServoMid(){

        return setServo(0,2);
    }

    /**
     * set servo's maximum angle = 180°
     * @see #setServo(int, int)
     * @return commend to send
     */
    public int setServoMax(){

        return setServo(0,3);
    }

    /**
     * set servo's angle using following function
     * @param angle servo's angle
     * @param functionNumber sets angle using following function
     * @return command to send
     */
    private int setServo(int angle, int functionNumber){

        int command = commandNumber;

        command<<=28;

        int ch = this.ch.getInt();

        ch<<=24;

        functionNumber<<=16;

        command+=ch+functionNumber+angle;

        return command;
    }
}
