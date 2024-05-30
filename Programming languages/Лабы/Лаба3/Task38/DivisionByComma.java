package com.company;

public class DivisionByComma implements Comparable<DivisionByComma> {
    private String words;

    public DivisionByComma(String words){
        setWords(words);
    }

    public String getWords() {
        return words;
    }

    public void setWords(String words) {
        this.words = words;
    }

    public int HowManyLetters(){
        int count = 1;
        int maxx = 0;
        char[] charArray = words.toCharArray();
        for( char x : charArray ) {
            if(x == ',') {
                if (count > maxx) {
                    maxx = count;
                }
                count = 1;
            }else if (x ==' ')
                count++;
        }
        if (count>maxx){
            maxx=count;
        }
        return maxx;
    }

    @Override
    public String toString() {
        return "DivisionByComma{" +
                "words='" + words + '\'' +
                '}';
    }

    @Override
    public int compareTo(DivisionByComma o) {
        return Integer.compare(HowManyLetters(),o.HowManyLetters());
    }
}
