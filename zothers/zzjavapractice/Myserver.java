package zzjavapractice;

import java.io.*;
import java.net.*;
import zzjavapractice.Socketwrap;

public class Myserver {
    
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        int port = 56666; 
      

        ServerSocket serverSocket = new ServerSocket(port) ; 
        System.out.println("Server running on port " + port); 

        Socket simple = serverSocket.accept() ; 
        System.out.println("Client connected!");

        Socketwrap fv = new Socketwrap(simple) ; 
        Object receive = fv.receive() ; 
        System.out.println("Received from client: " + receive);

        System.out.println("msg recwived ");

        fv.send("this is Sevrer prime speaking ");

        fv.close(); 

        serverSocket.close();



        


        
    }
    
}
