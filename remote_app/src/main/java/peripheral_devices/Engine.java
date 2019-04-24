package peripheral_devices;

public class Engine implements Device{

    public enum Channel{
        CHL(0),
        CHR(1);

        private int value;

        Channel(int value){
            this.value = value;
        }

        public int getInt(){
            return this.value;
        }
    }

    public enum Direction{
        FORWARD(1),
        BACKWARD(0);

        private int value;

        Direction(int value){
            this.value=value;
        }

        public int getInt(){
            return this.value;
        }
    }

    private Channel ch;
    private static int commandNumber = 1;

    public Engine(Channel ch){
        this.ch=ch;
    }

    public int startEngine(Direction direction,int speed){

        return setEngine(0,direction,speed,0);
    }
    public int startEngine(Direction direction, int speed, int runtime){

        return setEngine(1,direction,speed,runtime);
    }

    public int startEngineMin(Direction direction){

        return setEngine(2,direction,0,0);
    }

    public int startEngineMin(Direction direction, int runtime){

        return setEngine(3,direction,0,runtime);
    }

    public int startEngineMid(Direction direction){

        return setEngine(4,direction,0,0);
    }

    public int startEngineMid(Direction direction, int runtime){

        return setEngine(5,direction,0,runtime);
    }

    public int startEngineMax(Direction direction){

        return setEngine(6,direction,0,0);
    }

    public int startEngineMax(Direction direction, int runtime){

        return setEngine(7,direction,0,runtime);
    }

    public int stopEngineImmediately(){

        return setEngine(8,Direction.FORWARD,0,0);
    }

    public int stopEngine(){

        return setEngine(9,Direction.FORWARD,0,0);
    }

    private int setEngine(int functionNumber, Direction direction, int speed, int runtime){
        int command = commandNumber;
        command<<=28;


        int ch = this.ch.getInt();
        ch<<=24;


        functionNumber<<=16;


        int dir_temp = direction.getInt();
        dir_temp<<=15;


        if(!(speed>=0&&speed<=100))
            speed=0;

        speed<<=8;

        if(!(runtime>=0&&runtime<=255))
            runtime = 0;

        command+=ch+functionNumber+dir_temp+speed+runtime;

        return command;
    }


}
