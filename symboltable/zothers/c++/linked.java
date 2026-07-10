import java.util.LinkedList;

public class linked{ 
public static void main(String[] args) {
    
LinkedList<String> linkedList =new LinkedList<String>();



linkedList.offer("A");
linkedList.offer("B");
linkedList.offer("C");
linkedList.offer("D");
linkedList.offer("E");

linkedList.add(4,"e");


System.out.println(linkedList.peekFirst());
System.out.println(linkedList.peekLast());

System.out.println(linkedList);





 
}
}