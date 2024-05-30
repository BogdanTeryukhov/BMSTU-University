package com.company;
import java.util.Arrays;

public class Test {
    public static void main(String[] args) {
        WordsInSentences[] a = new WordsInSentences[]{
                new WordsInSentences("aaa abac"),
                new WordsInSentences("ab aba ababa"),
                new WordsInSentences("alhah kakaka"),
                new WordsInSentences("a aa")
        };
        Arrays.sort(a);
        for (WordsInSentences s : a) System.out.println(s);
    }
}

