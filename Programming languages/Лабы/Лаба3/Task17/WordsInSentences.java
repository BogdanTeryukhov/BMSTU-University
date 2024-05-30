package com.company;

public class WordsInSentences implements Comparable<WordsInSentences> {
    private String words;

    public WordsInSentences(String words){
        setWords(words);
    }

    public String getWords() {
        return words;
    }

    public void setWords(String words) {
        this.words = words;
    }

    public int HowManyLetters(){
        int kol = 0;
        int max = 0;
        char[] charArray = words.toCharArray();
        for( char x : charArray ) {
            if(x == ' ') {
                if (kol > max) {
                    max = kol;
                }
                kol = 0;
            }else
                kol++;
        }
        return max;
    }

    @Override
    public String toString() {
        return "WordsInSentences{" +
                "words='" + words + '\'' +
                '}';
    }

    @Override
    public int compareTo(WordsInSentences o) {
        return Integer.compare(HowManyLetters(),o.HowManyLetters());
    }

}
