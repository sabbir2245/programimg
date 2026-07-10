package Java.collections;

import java.util.Vector;

public class VectorExample {
    public static void main(String[] args) {
        Vector<String> vector = new Vector<>();

        vector.add("Apple");
        vector.add("Banana");
        vector.add("Orange");
        vector.add("Grapes");

        System.out.println("Element at index 1: " + vector.get(1));
        System.out.println("Size of the vector: " + vector.size());
        System.out.println("Is vector empty: " + vector.isEmpty());

        vector.set(2, "Peach");
        System.out.println("Vector after replacing element at index 2: " + vector);

        vector.remove("Banana");
        System.out.println("Vector after removing Banana: " + vector);

        vector.remove(1);
        System.out.println("Vector after removing element at index 1: " + vector);

        System.out.println("Does vector contain 'Apple': " + vector.contains("Apple"));

        vector.clear();
        System.out.println("Vector after clearing: " + vector);
    }
}
