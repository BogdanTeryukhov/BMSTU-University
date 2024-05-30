package Compilers.lab3.utils;

import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public final class Token {
    private Tag tag;
    private String value;
    private Position start, follow;
    private Pattern pattern;

    public Token(String text, int line, Pattern pattern) throws SyntaxError {
        this(new Position(text,line), pattern);
    }

    private Token(Position cur, Pattern pattern) throws SyntaxError {
        this.pattern = pattern;
        start = cur.skipWhile(Character::isWhitespace);
        follow = start.skip();

        Matcher matcher = pattern.matcher(start.getText());

        if (start.isEmpty()) {
            tag = Tag.END_OF_TEXT;
            value = "EOF";
        }
        else if (!matcher.find()) {
            throwError("invalid character");
        }
        else if (matcher.group("idents") != null) {
            tag = Tag.IDENT;
            value = matcher.group("idents");
            follow = follow.skipToken(matcher.end() - 1);
        }
        else if (matcher.group("numbers") != null) {
            tag = Tag.NUMBERS;
            value = matcher.group("numbers");
            follow = follow.skipToken(matcher.end() - 1);
        }
        else {
            throwError("invalid character");
        }
    }

    public static void printToken(String tag, String position, String value) {
        System.out.printf("%s %s: %s\n", tag, position, value);
    }

    public void throwError(String msg) throws SyntaxError {
        throw new SyntaxError(start, msg);
    }

    public Token next() throws SyntaxError {
        return new Token(follow, pattern);
    }

    public Tag getTag() {
        return tag;
    }

    public Position getPosition() {
        return start;
    }

    public String getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "Token{" +
                "tag=" + tag +
                ", value='" + value + '\'' +
                ", start=" + start +
                ", follow=" + follow +
                ", pattern=" + pattern +
                '}';
    }
}
