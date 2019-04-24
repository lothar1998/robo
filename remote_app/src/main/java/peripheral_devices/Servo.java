package peripheral_devices;

public class Servo implements Device {

    public enum channel{
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

        channel(int value){
            this.value=value;
        }

        public int getInt(){
            return this.value;
        }
    }

    private channel ch;
    private static int commandNumber = 0;

    public Servo(channel ch){
        this.ch=ch;
    }

    public int setServoAngle(int angle){

        if(angle>=0&&angle<=360) {

            return setServo(angle,0);
        }
        else
            return 0;
    }

    public int setServoMin(){

        return setServo(0,1);
    }

    public int setServoMid(){

        return setServo(0,2);
    }

    public int setServoMax(){

        return setServo(0,3);
    }

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
