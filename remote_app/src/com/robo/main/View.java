package com.robo.main;


import com.robo.peripheral_devices.Engine;
import com.robo.tcp_connection.OrderSender;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;

import java.net.InetAddress;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.ResourceBundle;

public class View{

    @FXML
    private Slider sliderEngineLeft;
    @FXML
    private Slider sliderEngineRight;
    @FXML
    private Button connectButton;
    @FXML
    private TextField IPAddress;


    private OrderSender sender;
    private String IP;
    private static int port = 10000;

    private Engine engineLeft, engineRight;

    public void engineLeftAction(MouseEvent event) {

        System.out.println("left: " + sliderEngineLeft.getValue());
    }

    public void engineRightAction(MouseEvent event){

        System.out.println("right: " + sliderEngineRight.getValue());
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

    public void getIPAddressAction(ActionEvent event){
        IP=IPAddress.getText();
        engineLeft = new Engine(Engine.Channel.CHL);
        engineRight = new Engine(Engine.Channel.CHR);
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
