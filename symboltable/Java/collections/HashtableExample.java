package Java.collections;

import java.util.Hashtable;
import java.util.Enumeration;

public class HashtableExample {
    public static void main(String[] args) {
        Hashtable<String, Integer> table = new Hashtable<>();

        table.put("Apple", 10);
        table.put("Banana", 20);
        table.put("Orange", 30);

        System.out.println("Value for Apple: " + table.get("Apple"));
        System.out.println("Contains key 'Banana': " + table.containsKey("Banana"));
        System.out.println("Contains value 10: " + table.containsValue(10));
        System.out.println("Size: " + table.size());

        table.remove("Orange");
        System.out.println("Size after removing Orange: " + table.size());

        System.out.println("Is empty: " + table.isEmpty());

        Enumeration<String> keys = table.keys();
        while (keys.hasMoreElements()) {
            System.out.println("Key: " + keys.nextElement());
        }

        table.clear();
        System.out.println("Size after clearing: " + table.size());
    }
}
