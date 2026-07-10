
import java.util.*;

public class scan {
    public static void main(String[] args) {
        
        String name ; 
        int y ;

        Scanner scap = new Scanner(System.in);

            System.out.println("what do you be called ");

            name = scap.nextLine();
            
            System.out.println("how old are you ");
            
            y = scap.nextInt();
            scap.nextLine();// clearing the input buffer (newline handling)

            System.out.println("hello, you are " + name+ ". and " + y +" years old.");

// this is a single line comment 

/*  sdjgskjag
 * dfg
 * ff
 */

int fr = 10 ; 
fr = fr/2 ;
fr = fr +56;

fr++;


    }
    
}
