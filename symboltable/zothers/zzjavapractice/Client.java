package zzjavapractice;

import java.io.*;
import java.net.*;


public class Client {
    public static void main(String[] args) throws UnknownHostException, IOException, ClassNotFoundException {
        String serverAddress = "localhost";//127.0.0.1
        int port = 56666;

        Socket socket = new Socket(serverAddress, port);
        System.out.println("Connected to the server!");

       

        Socketwrap sc = new Socketwrap(socket);
        
        sc.send("oppp from clien speaking ");
        System.out.println("Message sent to server");

        Object resp = (String) sc.receive();
        System.out.println("Received from server: " + resp);


        sc.close();
            


    }
}