package com.company;
import java.util.Arrays;

public class Test {
    public static void main(String[] args) {
        Char_kol_A[] a = new Char_kol_A[]{
                new Char_kol_A('a','b'),
                new Char_kol_A('a','a','a'),
                new Char_kol_A('b','b'),
                new Char_kol_A('a','a','a','b','a')
        };
        Arrays.sort(a);
        for (Char_kol_A s : a) System.out.println(s);
    }
}
