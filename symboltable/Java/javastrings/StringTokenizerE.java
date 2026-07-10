package Java.javastrings ; 

import java.util.StringTokenizer;

public class StringTokenizerE {

    public static void main(String[] args) {

        // Create a StringTokenizer object
        String str = "Hello, Java; StringTo,kenizer Example!";
        StringTokenizer tokenizer = new StringTokenizer(str, " ,;!");

        // Count number of tokens
        int tokenCount = tokenizer.countTokens();
        System.out.println("Total tokens: " + tokenCount);

        // Iterate through the tokens
        while (tokenizer.hasMoreTokens()) {
            String token = tokenizer.nextToken();  // Get next token
            System.out.println("Token: " + token);
        }

        // Reset tokenizer and use nextElement()
        tokenizer = new StringTokenizer(str, " ,;!");
        System.out.println("\nUsing nextElement() method:");
        while (tokenizer.hasMoreElements()) {
            String token = (String) tokenizer.nextElement();  // Get next element
            System.out.println("Token: " + token);
        }

        // Using the delimiter argument
        String str2 = "Apple|Banana|Orange|Grape";
        StringTokenizer tokenizer2 = new StringTokenizer(str2, "|");

        System.out.println("\nTokens from str2 using '|' as delimiter:");
        while (tokenizer2.hasMoreTokens()) {
            System.out.println("Token: " + tokenizer2.nextToken());
        }

        // Check if the string has more tokens
        boolean hasTokens = tokenizer2.hasMoreTokens();
        System.out.println("\nDoes the string have more tokens? " + hasTokens);
    }
}
