package com.company;

public class Test {
    public static void main(String[] args) {
        GcdList ans = new GcdList(2,4,4,5,15,7);

        for (Integer s: ans) {
            System.out.println(s);
        }
    }
}