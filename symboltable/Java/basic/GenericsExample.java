package Java.basic;

// Generic Class
class Box<T> {
    private T value;

    // Constructor
    public Box(T value) {
        this.value = value;
    }

    // Getter
    public T getValue() {
        return value;

    }

    // Setter
    public void setValue(T value) {
        this.value = value;
    }
}

// Generic Method with Upper Bound
public class GenericsExample {

    // Generic method
    public static <T> void printArray(T[] array) {
        for (T element : array) {
            System.out.print(element + " ");
        }
        System.out.println();
    }

    // Upper bounded wildcard example
    public static <T extends Number> void printNumber(T number) {
        System.out.println(number);
    }


// Generic Interface

 interface Pair<K, V> {
        K getKey();

        V getValue();
    }

    // Implementing Pair interface
    static class KeyValuePair<K, V> implements Pair<K, V> {
        private K key;
        private V value;

        public KeyValuePair(K key, V value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public K getKey() {
            return key;
        }

        @Override
        public V getValue() {
            return value;
        }
    }

    // Unbounded wildcard method
    public static void printList(java.util.List<?> list) {
        for (Object obj : list) {
            System.out.println(obj);
        }
    }

    // Upper Bounded Wildcard
    public static void printNumbers(java.util.List<? extends Number> list) {
        for (Number number : list) {
            System.out.println(number);
        }
    }

    // Lower Bounded Wildcard
    public static void addIntegers(java.util.List<? super Integer> list) {
        list.add(10); // OK: Integer is a subclass of itself
    }

    public static void main(String[] args) {
        // 1. Generic Class Example
        Box<Integer> intBox = new Box<>(10);
        System.out.println("Box contains: " + intBox.getValue());

        // 2. Generic Method Example
        Integer[] intArray = { 1, 2, 3, 4, 5 };
        String[] strArray = { "Hello", "World" };
        printArray(intArray);
        printArray(strArray);

        // 3. Upper Bounded Wildcard Example
        printNumber(10); // Integer
        printNumber(10.5); // Double

        // 4. Generic Interface Example
        Pair<Integer, String> pair = new KeyValuePair<>(1, "One");
        System.out.println("Key: " + pair.getKey() + ", Value: " + pair.getValue());

        // 5. Unbounded Wildcard Example
        java.util.List<Object> list = new java.util.ArrayList<>();
        list.add("Hello");
        list.add(10);
        printList(list);

        // 6. Upper Bounded Wildcard Example
        java.util.List<Number> numList = new java.util.ArrayList<>();
        numList.add(10);
        numList.add(10.5);
        printNumbers(numList);

        // 7. Lower Bounded Wildcard Example
        java.util.List<Number> numbersList = new java.util.ArrayList<>();
        addIntegers(numbersList); // Valid
    }
}
