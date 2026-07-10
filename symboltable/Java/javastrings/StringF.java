package Java.javastrings ; 

public class StringF {

    public static void main(String[] args) {

        // Create strings
        String str = "Hello, World!";
        String str2 = new String("Java");

        // Length & Character Access
        int length = str.length();         // Returns the length of the string
        char ch = str.charAt(3);  
        
        
        // Returns character at index 3
        System.out.println("Length: " + length);
        System.out.println("Character at index 3: " + ch);

        // Case Conversion
        String upper = str.toUpperCase();  // Converts to uppercase
        String lower = str.toLowerCase();  // Converts to lowercase
        System.out.println("Uppercase: " + upper);
        System.out.println("Lowercase: " + lower);

        // Substring Extraction
        String sub1 = str.substring(7);// Extracts from index 7 to end
        String sub2 = str.substring(0, 5);  // Extracts from index 0 to 4
        System.out.println("Substring from index 7: " + sub1);
        System.out.println("Substring from index 0 to 4: " + sub2);

        // Concatenation
        String full = str.concat(" Java!");  // Concatenates strings
        String full2 = str + " Java!";       // Another way to concatenate
        System.out.println("Concatenated string (concat): " + full);
        System.out.println("Concatenated string (+): " + full2);

        // Comparison
        boolean isEqual = str.equals("Hello, World!");     // Case-sensitive comparison
        boolean isEqualIgnoreCase = str.equalsIgnoreCase("hello, world!");  // Case-insensitive
        int compare = str.compareTo("Hello, Java!");       // Lexicographical comparison
        int compareIgnore = str.compareToIgnoreCase("hello, world!");


        System.out.println("Equals (case-sensitive): " + isEqual);
        System.out.println("Equals (ignore case): " + isEqualIgnoreCase);
        System.out.println("CompareTo: " + compare);
        System.out.println("CompareToIgnoreCase: " + compareIgnore);

        // Searching & Checking
        boolean contains = str.contains("World");         // Checks if "World" is in the string
        boolean starts = str.startsWith("Hello");         // Checks if starts with "Hello"
        boolean ends = str.endsWith("!");                 // Checks if ends with "!"
        int index1 = str.indexOf("o");                    // First occurrence of "o"
        int index2 = str.lastIndexOf("o");                // Last occurrence of "o"
        System.out.println("Contains 'World': " + contains);
        System.out.println("Starts with 'Hello': " + starts);
        System.out.println("Ends with '!': " + ends);
        System.out.println("Index of first 'o': " + index1);
        System.out.println("Index of last 'o': " + index2);

        // Replace
        String replaced = str.replace("World", "Java");  // Replace "World" with "Java"
        System.out.println("Replaced string: " + replaced);

        // Trim
        String withSpaces = "  Hello, World!  ";
        String trimmed = withSpaces.trim();  // Removes leading and trailing spaces
        System.out.println("Trimmed string: '" + trimmed + "'");

        // Split
        String[] words = str.split(" ");  // Splits by space
        System.out.println("Words after split:");
        for (String word : words) {
            System.out.println(word);
        }

        // Value of
        String valueStr = String.valueOf(123);  // Converts integer to string
        System.out.println("String representation of 123: " + valueStr);
    }
}
