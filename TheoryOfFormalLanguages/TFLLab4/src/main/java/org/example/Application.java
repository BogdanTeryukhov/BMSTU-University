package org.example;

import utils.fileScanning.GrammarAndWordScanner;
import utils.grammar.Grammar;
import utils.grammar.rule.Rule;
import utils.syntaxTree.SyntaxTreeCreation;
import utils.syntaxTree.incrementalParsing.IncrementalParsing;
import utils.syntaxTree.parsingTable.ParsingTableCreator;
import utils.syntaxTree.parsingTable.firstAndFollow.FirstFunForGrammarCreator;
import utils.syntaxTree.parsingTable.firstAndFollow.FollowFunForGrammarCreator;

import java.io.IOException;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

import static utils.fileScanning.GrammarAndWordScanner.grammarFill;
import static utils.fileScanning.GrammarAndWordScanner.word;

public class Application {


    public static void main(String[] args) throws IOException {
        Grammar grammar = GrammarAndWordScanner.grammarFill(args[0]); //args[0] - путь к файлу input.txt
        if (Grammar.isGrammarLeftRecursive(grammar)){
            throw new RuntimeException("Grammar is not LL(1) !");
        }

        /*
        Grammar checkGrammar = new Grammar();
        checkGrammar.setRulesSet(grammar.getRulesSet());

        for (int i = 0; i < grammar.getRulesSet().size(); i++) {
            Rule rule = grammar.getRulesSet().get(i);
            List<String> additionRules = new ArrayList<>();
            for (int j = 0; j < rule.getTo().size(); j++) {
                //System.out.println("to: " + rule.getTo().get(j));
                if (!Grammar.isTerminal(rule.getTo().get(j).substring(0,1).charAt(0))){
                    List<String> proxy = Objects.requireNonNull(Grammar.findRuleByFrom(grammar, rule.getTo().get(j).substring(0, 1).charAt(0))).getTo();
                    additionRules.addAll(proxy);
                }
                else {
                    additionRules.add(rule.getTo().get(j));
                }
                //System.out.println(additionRules);
            }
            for (int j = 0; j < additionRules.size(); j++) {
                String firstTo = additionRules.get(j);
                for (int k = j + 1; k < additionRules.size(); k++) {
                    String secondTo = additionRules.get(k);
                    if (firstTo.contains(secondTo.substring(0,1)) || secondTo.contains(firstTo.substring(0,1))){
                        throw new RuntimeException("Неоднозначность выбора!");
                    }
                }
            }
        }

         */

        try {
            for (int i = grammar.getRulesSet().size() - 1; i >= 0; i--) {
                FirstFunForGrammarCreator.firstCreator(grammar.getRulesSet().get(i));
            }
        }catch (RuntimeException exception){
            throw new RuntimeException("Неоднозначность выбора!");
        }

        //System.out.println("First");
        //FirstFunForGrammarCreator.firstFunctionHashMap.forEach((key,value)->System.out.println(key + " : " + value));
        try{
            FollowFunForGrammarCreator.followCreator(grammar, FirstFunForGrammarCreator.firstFunctionHashMap);
        }catch (RuntimeException exception){
            throw new RuntimeException("Неоднозначность выбора!");
        }


        //System.out.println("Follow");
        //FollowFunForGrammarCreator.followFunctionHashMap.forEach((key,value)->System.out.println(key + " : " + value));
        ParsingTableCreator.tableCreator(FirstFunForGrammarCreator.firstFunctionHashMap, FollowFunForGrammarCreator.followFunctionHashMap, grammar);

        System.out.println("LL(1) Parsing Tree: ");
        SyntaxTreeCreation.createHashMap(ParsingTableCreator.parsingTable, GrammarAndWordScanner.word);
        //SyntaxTreeCreation.tree.forEach((key, value) -> System.out.println(key + " : " + value));

        //System.out.println("Reps");
        //SyntaxTreeCreation.reps.forEach((key, value) -> System.out.println(key + " : " + value));

        System.out.println("\nIncremental LL(1) Parsing Tree");
        IncrementalParsing.incrementalParsingRealisation(SyntaxTreeCreation.resultTree, GrammarAndWordScanner.incWord, ParsingTableCreator.parsingTable);
        //IncrementalParsing.incrementalTree.forEach((key,value) -> System.out.println(key + " : " + value));
    }
}