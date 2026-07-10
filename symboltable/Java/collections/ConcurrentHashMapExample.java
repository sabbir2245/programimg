package Java.collections;

import java.util.concurrent.ConcurrentHashMap;
import java.util.Map;


// used for multi threading
public class ConcurrentHashMapExample {
    public static void main(String[] args) {
        ConcurrentHashMap<String, Integer> map = new ConcurrentHashMap<>();

        map.put("Apple", 10);
        map.put("Banana", 20);
        map.put("Orange", 30);

        System.out.println("Value for Apple: " + map.get("Apple"));
        System.out.println("Contains key 'Banana': " + map.containsKey("Banana"));
        System.out.println("Contains value 10: " + map.containsValue(10));
        System.out.println("Size: " + map.size());

        map.remove("Orange");
        System.out.println("Size after removing Orange: " + map.size());

        System.out.println("Is empty: " + map.isEmpty());

        map.replace("Apple", 50);
        System.out.println("Value for Apple after replacing: " + map.get("Apple"));

        for (Map.Entry<String, Integer> ptr : map.entrySet()) {
            System.out.println("Key: " + ptr.getKey() + ", Value: " + ptr.getValue());
        }

        map.clear();
        System.out.println("Size after clearing: " + map.size());
    }
}
