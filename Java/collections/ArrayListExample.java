package Java.collections;

import java.util.ArrayList;


public class ArrayListExample {
    public static void main(String[] args) {
        ArrayList<String> list = new ArrayList<>();

        list.add("Apple");
        list.add("Banana");
        list.add("Orange");
        list.add("Grapes");

        System.out.println("Element at index 1: " + list.get(1));
        System.out.println("Size of the list: " + list.size());
        System.out.println("Is list empty: " + list.isEmpty());

        list.set(2, "Peach");
        System.out.println("List after replacing element at index 2: " + list);

        list.remove("Banana");
        System.out.println("List after removing Banana: " + list);

        list.remove(1);
        System.out.println("List after removing element at index 1: " + list);

        System.out.println("Does list contain 'Apple': " + list.contains("Apple"));

        list.clear();
        System.out.println("List after clearing: " + list);
    }
}
