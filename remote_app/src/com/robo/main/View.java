package com.robo.main;


import com.robo.peripheral_devices.Engine;
import com.robo.peripheral_devices.Led;
import com.robo.tcp_connection.OrderSender;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleButton;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import java.net.InetAddress;


public class View{

    @FXML
    private Slider sliderEngineLeft, sliderEngineRight;
    @FXML
    private Button connectButton;
    @FXML
    private TextField IPAddress;
    @FXML
    private Button stopButton;
    @FXML
    private ToggleButton lightFront, lightBack;


    private String IP;
    private static int port = 10000;

    private Engine engineLeft, engineRight;
    private Led ledFL, ledFR, ledBL, ledBR;

    public void engineLeftAction(MouseEvent event) throws Exception {
        if(sliderEngineLeft.getValue()>0)
            sendMessage(engineLeft.startEngine(Engine.Direction.FORWARD,(int)sliderEngineLeft.getValue()),IP,port);
        else
            sendMessage(engineLeft.startEngine(Engine.Direction.BACKWARD,(int)sliderEngineLeft.getValue()*(-1)),IP,port);
    }

    public void engineRightAction(MouseEvent event) throws Exception{
        if(sliderEngineRight.getValue()>0)
            sendMessage(engineRight.startEngine(Engine.Direction.FORWARD,(int)sliderEngineRight.getValue()),IP,port);
        else
            sendMessage(engineRight.startEngine(Engine.Direction.BACKWARD,(int)sliderEngineRight.getValue()*(-1)),IP,port);
    }

    public void pressedKeyAction(KeyEvent event) throws Exception{
        switch (event.getCode()){
            case W: sliderEngineLeft.increment();
                    if(sliderEngineLeft.getValue()>0)
                        sendMessage(engineLeft.startEngine(Engine.Direction.FORWARD,(int)sliderEngineLeft.getValue()),IP,port);
                    else
                        sendMessage(engineLeft.startEngine(Engine.Direction.BACKWARD,(int)sliderEngineLeft.getValue()*(-1)),IP,port);
                break;
            case S: sliderEngineLeft.decrement();
                    if(sliderEngineLeft.getValue()>0)
                        sendMessage(engineLeft.startEngine(Engine.Direction.FORWARD,(int)sliderEngineLeft.getValue()),IP,port);
                    else
                        sendMessage(engineLeft.startEngine(Engine.Direction.BACKWARD,(int)sliderEngineLeft.getValue()*(-1)),IP,port);
                break;
            case O: sliderEngineRight.increment();
                    if(sliderEngineRight.getValue()>0)
                        sendMessage(engineRight.startEngine(Engine.Direction.FORWARD,(int)sliderEngineRight.getValue()),IP,port);
                    else
                        sendMessage(engineRight.startEngine(Engine.Direction.BACKWARD,(int)sliderEngineRight.getValue()*(-1)),IP,port);
                break;
            case K: sliderEngineRight.decrement();
                    if(sliderEngineRight.getValue()>0)
                        sendMessage(engineRight.startEngine(Engine.Direction.FORWARD,(int)sliderEngineRight.getValue()),IP,port);
                    else
                        sendMessage(engineRight.startEngine(Engine.Direction.BACKWARD,(int)sliderEngineRight.getValue()*(-1)),IP,port);
                break;
            case B: sliderEngineLeft.setValue(0);
                    sliderEngineRight.setValue(0);
                    sendMessage(engineLeft.stopEngineImmediately(),IP,port);
                    sendMessage(engineRight.stopEngineImmediately(),IP,port);
                break;

                default:
        }
    }

    public void stopEngineAction(ActionEvent event) throws Exception{
        sliderEngineLeft.setValue(0);
        sliderEngineRight.setValue(0);
        sendMessage(engineLeft.stopEngineImmediately(),IP,port);
        sendMessage(engineRight.stopEngineImmediately(),IP,port);
    }

    public void frontLightAction(ActionEvent event) throws Exception{
        if(lightFront.isSelected()){
            sendMessage(ledFL.on(),IP,port);
            sendMessage(ledFR.on(),IP,port);
        }
        else {
            sendMessage(ledFL.off(),IP,port);
            sendMessage(ledFR.off(),IP,port);
        }
    }

    public void backLightAction(ActionEvent event) throws Exception{
        if(lightBack.isSelected()){
            sendMessage(ledBL.on(),IP,port);
            sendMessage(ledBR.on(),IP,port);
        }
        else {
            sendMessage(ledBL.off(),IP,port);
            sendMessage(ledBR.off(),IP,port);
        }
    }

    public void getIPAddressAction(ActionEvent event){
        IP=IPAddress.getText();
        connectButton.setDisable(true);
        IPAddress.setDisable(true);
        engineLeft = new Engine(Engine.Channel.CHL);
        engineRight = new Engine(Engine.Channel.CHR);
        ledFL = new Led(Led.Pin.PIN27);
        ledFR = new Led(Led.Pin.PIN25);
        ledBL = new Led(Led.Pin.PIN4);
        ledBR = new Led(Led.Pin.PIN5);
        sliderEngineLeft.setDisable(false);
        sliderEngineRight.setDisable(false);
        lightFront.setDisable(false);
        lightBack.setDisable(false);
        stopButton.setDisable(false);
    }

    private void sendMessage(int command,String IP, int port) throws Exception{
        Thread sendThread = new Thread(() -> {

            try {
                OrderSender sender = new OrderSender(InetAddress.getByName(IP), port);
                sender.send(command);
                sender.close();
            }catch (Exception e){
                System.out.println(e.getMessage());
            }

        });

        sendThread.start();

        sendThread.join();
    }
}
