package com.company;
import java.util.Arrays;

public class Test {
    public static void main(String[] args) {
        Quadrangles[] a = new Quadrangles[]{
                new Quadrangles(15, 20),
                new Quadrangles(23, 45),
                new Quadrangles(56, 34),
                new Quadrangles(23, 24)
        };
        Arrays.sort(a);
        for (Quadrangles s : a) System.out.println(s);
    }
}
