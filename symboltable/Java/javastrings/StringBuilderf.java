
package Java.javastrings ; 

public class StringBuilderf{

    public static void main(String[] args) {

        // Create StringBuilder
        StringBuilder sb = new StringBuilder("Hello");
        StringBuilder sb2 = new StringBuilder("Java");
        StringBuilder sb3 = new StringBuilder(sb2);
        //StringBuilder sb4 = "loppp" ; errro


        // Length & Character Access
        int length = sb.length();           // Returns the length of the StringBuilder
        char ch = sb.charAt(3);             // Returns character at index 3
        System.out.println("Length: " + length);
        System.out.println("Character at index 3: " + ch);

        // Append
        sb.append(" World!");               // Appends string to the end
        sb.append(" Java");                 // Append another string
        System.out.println("After append: " + sb);

        // Insert
        sb.insert(5, ",");                  // Inserts at specified index
        System.out.println("After insert: " + sb);

        // Delete
        sb.delete(5, 6);                    // Deletes the characters between indices 5 and 6
        System.out.println("After delete: " + sb);

        // Replace
        sb.replace(6, 11, "Everyone");      // Replaces part of the string with another string
        System.out.println("After replace: " + sb);

        // Reverse
        sb.reverse();                       // Reverses the string
        System.out.println("Reversed string: " + sb);

        // Capacity & Ensure Capacity
        int capacity = sb.capacity();       // Returns the current capacity of StringBuilder
        sb.ensureCapacity(50);              // Ensures capacity is at least 50
        System.out.println("Current capacity: " + capacity);

        // Convert StringBuilder to String
        String strFromSB = sb.toString();   // Converts StringBuilder to String
        System.out.println("String from StringBuilder: " + strFromSB);

        // Set & Get at specific index
        sb.setCharAt(5, 'A');               // Set a character at a specific index
        char charAtIndex = sb.charAt(5);    // Get the character at specific index
        System.out.println("After setCharAt: " + sb);
        System.out.println("Character at index 5: " + charAtIndex);

        // Check if StringBuilder is empty
        boolean isEmpty = sb.isEmpty();     // Checks if the StringBuilder is empty
        System.out.println("Is StringBuilder empty: " + isEmpty);

        // Index of
        int index = sb.indexOf("Java");     // Finds the first occurrence of "Java"
        System.out.println("Index of 'Java': " + index);
    }
}
 
