package Java.collections;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class HashMapExample {
    public static void main(String[] args) {
        HashMap<String, Integer> map = new HashMap<>();

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

        Set<Map.Entry<String, Integer>> entries = map.entrySet();
        for (Map.Entry<String, Integer> entry : entries) {
            System.out.println("Key: " + entry.getKey() + ", Value: " + entry.getValue());
        }

        map.clear();
        System.out.println("Size after clearing: " + map.size());
    }
}
