package com.robo.peripheral_devices;

/**
 * Class implementation of engines
 */
public class Engine implements Device{

    /**
     * numbers of engines channels
     */
    public enum Channel{
        CHR(0),
        CHL(1);

        private int value;

        Channel(int value){
            this.value = value;
        }

        /**
         * getter to enum value
         * @return value of enum
         */
        public int getInt(){
            return this.value;
        }
    }

    /**
     * expected engine's directions
     */
    public enum Direction{
        FORWARD(1),
        BACKWARD(0);

        private int value;

        Direction(int value){
            this.value=value;
        }

        /**
         * getter to enum value
         * @return value of enum
         */
        public int getInt(){
            return this.value;
        }
    }

    /**
     * engine's channel
     */
    private Channel ch;

    /**
     * device id
     */
    private static int commandNumber = 1;

    /**
     * construct engine object
     * @param ch channel of engine
     */
    public Engine(Channel ch){
        this.ch=ch;
    }

    /**
     * start engine in given direction with given speed
     * @param direction movement direction
     * @param speed speed of movement
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int startEngine(Direction direction,int speed){

        return setEngine(0,direction,speed,0);
    }

    /**
     * start engine in given direction with given speed for given milliseconds
     * @param direction movement direction
     * @param speed movement speed
     * @param runtime movement time
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int startEngine(Direction direction, int speed, int runtime){

        return setEngine(1,direction,speed,runtime);
    }

    /**
     * start engine in given direction with minimum speed
     * @param direction movement direction
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int startEngineMin(Direction direction){

        return setEngine(2,direction,0,0);
    }

    /**
     * start engine in given direction with minimum speed for given milliseconds
     * @param direction movement direction
     * @param runtime movement time
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int startEngineMin(Direction direction, int runtime){

        return setEngine(3,direction,0,runtime);
    }

    /**
     * start engine in given direction with medium speed
     * @param direction movement direction
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int startEngineMid(Direction direction){

        return setEngine(4,direction,0,0);
    }

    /**
     * start engine in given direction with medium speed for given milliseconds
     * @param direction movement direction
     * @param runtime movement time
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int startEngineMid(Direction direction, int runtime){

        return setEngine(5,direction,0,runtime);
    }

    /**
     * start engine in given direction with maximum speed
     * @param direction movement direction
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int startEngineMax(Direction direction){

        return setEngine(6,direction,0,0);
    }

    /**
     * start engine in given direction with maximum speed for given miliseconds
     * @param direction movement direction
     * @param runtime movement time
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int startEngineMax(Direction direction, int runtime){

        return setEngine(7,direction,0,runtime);
    }

    /**
     * stop engine immediately
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int stopEngineImmediately(){

        return setEngine(8,Direction.FORWARD,0,0);
    }

    /**
     * stop engine slowly
     * @see #setEngine(int, Direction, int, int)
     * @return command to send
     */
    public int stopEngine(){

        return setEngine(9,Direction.FORWARD,0,0);
    }

    /**
     * generate command to send
     * @param functionNumber number of called function
     * @param direction movement direction
     * @param speed movement speed
     * @param runtime movement time
     * @return command to send
     */
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