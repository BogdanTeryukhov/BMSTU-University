package com.company;

public class Test {
    public static void main(String[] args) {
        StringBuilder b = new StringBuilder("qwerty");
        SuffixList suffix = new SuffixList(b);

        for (String s: suffix) System.out.println(s);

    }
}