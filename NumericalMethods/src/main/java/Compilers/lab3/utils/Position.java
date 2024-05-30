package Compilers.lab3.utils;

import java.util.function.IntPredicate;

public class Position {
    private String text;
    private int index, line, col;

    public Position(String text,int line) {
        this(text, 0, line, 1);
    }

    private Position(String text, int index, int line, int col) {
        this.text = text;
        this.index = index;
        this.line = line;
        this.col = col;
    }

    public boolean isEmpty() {
        return text.isEmpty();
    }

    public int getChar() {
        return index < text.length() ? text.codePointAt(index) : -1;
    }

    public boolean satisfies(IntPredicate p) {
        return p.test(getChar());
    }

    public Position skip() {
        int c = getChar();
        //System.out.println("Index: " + index);
        switch (c) {
            case -1:
                return this;
            case '\n':
                return new Position(text.substring(1), index, line + 1, 1);
            default:
                return new Position(text.substring(1), index, line, col + 1);
        }
    }

    public Position skipToken(int range) {
        Position pos = this;
        for (int i = 0; i < range; i++) {
            pos = pos.skip();
        }
        pos.text = text.substring(range);

        return pos;
    }

    public Position skipWhile(IntPredicate p) {
        Position pos = this;
        while (pos.satisfies(p)) pos = pos.skip();
        return pos;
    }

    public String getText() {
        return text;
    }

    public String toString() {
        return String.format("(%d, %d)", line, col);
    }
}
