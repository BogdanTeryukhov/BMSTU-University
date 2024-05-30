package com.company;
import java.util.Arrays;

public class Test {
    public static void main(String[] args) {
        Circles[] a = new Circles[]{
                new Circles(2, 5, 7, 3, 4, 8),
                new Circles(4, 6, 5, 3, 3, 8),
                new Circles(5, 7, 9, 8, 4, 6)
        };
        Arrays.sort(a);
        for (Circles s : a) System.out.println(s);
    }
}

