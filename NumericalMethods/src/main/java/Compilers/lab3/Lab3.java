package Compilers.lab3;

import Compilers.lab3.utils.SyntaxError;
import Compilers.lab3.utils.Tag;
import Compilers.lab3.utils.Token;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Pattern;

import static Compilers.lab3.utils.Token.printToken;

public class Lab3 {

    private static final String numbers = "1?(0+1?)+";
    private static final String idents = "[b-df-hj-np-tv-z]?([a|e|i|o|u]+[b-df-hj-np-tv-z]?)+";
    private static final String pattern = "(?<numbers>^"+numbers+")|(?<idents>^"+idents+")";

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new FileReader(args[0]));
        String line;
        int counter = 1;
        while((line = bufferedReader.readLine()) != null){
            Pattern p = Pattern.compile(pattern);
            try {
                Token token = new Token(line, counter, p);
                do {
                    printToken(token.getTag().toString(), token.getPosition().toString(), token.getValue());
                    token = token.next();
                } while (token.getTag() != Tag.END_OF_TEXT);
            } catch (SyntaxError syntaxError) {
                syntaxError.printStackTrace();
            }
            counter++;
        }
    }
}
