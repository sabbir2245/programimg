public class javastring {

    public static void main(String[] args) {
        // Example string
        String str = "Hello, World!";

        // Returns the character at the specified index
        char ch = str.charAt(1); // 'e'

        // Returns the length of the string
        int len = str.length(); // 13

        // Returns a new string that is a substring of this string
        String substr1 = str.substring(2); // "llo, World!"
        String substr2 = str.substring(7, 12); // "World"

        // Returns true if the string contains the specified sequence of char values
        boolean containsHello = str.contains("World"); // true

        // Returns the index within this string of the first occurrence of the specified
        // substring
        int index1 = str.indexOf("l"); // 2
        int index2 = str.indexOf("l", 3); // 3

        // Returns the index within this string of the last occurrence of the specified
        // substring
        int lastIndex1 = str.lastIndexOf("l"); // 10
        int lastIndex2 = str.lastIndexOf("l", 2); // 2

        // Converts all characters in this string to uppercase
        String upperStr = str.toUpperCase(); // "HELLO, WORLD!"

        // Converts all characters in this string to lowercase
        String lowerStr = str.toLowerCase(); // "hello, world!"

        // Compares this string to the specified object
        boolean isEqual = str.equals("Hello, World!"); // true

        // Compares this String to another String, ignoring case considerations
        boolean isEqualIgnoreCase = str.equalsIgnoreCase("hello, world!"); // true

        // Returns a string whose value is this string, with any leading and trailing
        // whitespace removed
        String trimmedStr = "  Hello, World!  ".trim(); // "Hello, World!"

        // Returns a string resulting from replacing all occurrences of oldChar in this
        // string with newChar
        String replacedStr1 = str.replace('l', 'p'); // "Heppo, Worpd!"
        String replacedStr2 = str.replace("World", "Java"); // "Hello, Java!"

        // Splits this string around matches of the given regular expression
        String[] parts = "apple,banana,orange".split(","); // ["apple", "banana", "orange"]

        // Tests if this string starts with the specified prefix
        boolean startsWith = str.startsWith("He"); // true

        // Tests if this string ends with the specified suffix
        boolean endsWith = str.endsWith("ld!"); // true

        // Print out all results
        System.out.println("charAt(1): " + ch);
        System.out.println("length(): " + len);
        System.out.println("substring(2): " + substr1);
        System.out.println("substring(7, 12): " + substr2);
        System.out.println("contains(\"World\"): " + containsHello);
        System.out.println("indexOf(\"l\"): " + index1);
        System.out.println("indexOf(\"l\", 3): " + index2);
        System.out.println("lastIndexOf(\"l\"): " + lastIndex1);
        System.out.println("lastIndexOf(\"l\", 2): " + lastIndex2);
        System.out.println("toUpperCase(): " + upperStr);
        System.out.println("toLowerCase(): " + lowerStr);
        System.out.println("equals(\"Hello, World!\"): " + isEqual);
        System.out.println("equalsIgnoreCase(\"hello, world!\"): " + isEqualIgnoreCase);
        System.out.println("trim(): " + trimmedStr);
        System.out.println("replace('l', 'p'): " + replacedStr1);
        System.out.println("replace(\"World\", \"Java\"): " + replacedStr2);
        System.out.println("split(\",\"): " + String.join(" | ", parts));
        System.out.println("startsWith(\"He\"): " + startsWith);
        System.out.println("endsWith(\"ld!\"): " + endsWith);




















        
    }
}
