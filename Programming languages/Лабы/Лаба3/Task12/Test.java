package com.company;
import java.util.Arrays;

public class Test {

    public static void main(String[] args){
        AriphmeticProgression[] a = new AriphmeticProgression[]{
                new AriphmeticProgression(11,3),
                new AriphmeticProgression(1,30),
                new AriphmeticProgression(5,21),
                new AriphmeticProgression(55,110)
        };

        Arrays.sort(a);

        for (AriphmeticProgression s:a) {
            System.out.println(s);
        }
    }
}
