package zzjavapractice;

import java.io.*;
import java.net.*;

public class Socketwrap {

    private Socket so ;
    private ObjectInputStream in ; 
    private ObjectOutputStream out  ; 


    Socketwrap(Socket s) throws IOException{
        so = s; 
        out = new ObjectOutputStream(s.getOutputStream());
        in = new ObjectInputStream(s.getInputStream()) ; 

    }

    public void send(Object obj ) throws IOException{

        out.writeObject(obj); 
        out.flush() ; 


    }

    public Object receive() throws IOException , ClassNotFoundException{
        return in.readObject() ; 
    }
    
    public void close() throws IOException {
        in.close();
        out.close();
        so.close();
    }
    
    
}
