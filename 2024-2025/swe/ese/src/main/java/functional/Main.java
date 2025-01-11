package functional;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.function.BiFunction;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        List<Couple> data = new ArrayList<>();
        data.add(new Couple(1, 2));
        data.add(new Couple(-1, 0));
        data.add(new Couple(0, 10));
        data.add(new Couple(-4, 1));

        int result = data
                .stream()
                // .parallel()
                .filter(x -> x.val1 >= 0)
                // .mapToInt(x -> x.val2)
                .map(x -> x.val2)
                // .reduce(0, (sum, value) -> sum + value);
                .reduce(0, Integer::sum);

        // wow! under the hood this is what happens
        int result2 = data.stream()
                .filter(
                        new Predicate<Couple>() {
                            @Override
                            public boolean test(Couple couple) {
                                return couple.val1 >= 0;
                            }
                        })
                .map(
                        new Function<Couple, Integer>() {
                            @Override
                            public Integer apply(Couple couple) {
                                return couple.val2;
                            }
                        })
                .reduce(
                        0, new BinaryOperator<Integer>() {
                            @Override
                            public Integer apply(Integer acc, Integer i) {
                                return acc + i;
                            }
                        });

        System.out.println(result + " == " + result2);

        // NON RIESCO! (come viene implementata da stream a list?)
        // float result3 = data
        // .stream()
        // .filter(x -> x.val1 >= 0)
        // .map(x -> x.val2)
        // .reduce((float)0, (sum, value) -> sum + ((float)value)/2);
        // SEE THIS
        // Set<Integer> result3 = data
        // .stream()
        // .filter(x -> x.val1 >= 0)
        // .map(x -> x.val2)
        // .collect(Collectors.toSet());

        List<Integer> numeri = new ArrayList<>();
        numeri.add(0);
        numeri.add(1);
        numeri.add(2);
        numeri.add(3);
        numeri.add(4);
        numeri
                .stream()
                .filter(x -> x % 2 == 0)
                .findFirst()
                // .ifPresentOrElse(
                // x -> System.out.println("il primo numero pari e' " + x),
                // () -> System.out.println("nessun numero pari trovato"));
                .map(
                        x -> "il primo numero pari e' " + x)
                .orElse("nessun numero pair");

        BiFunction<List<Integer>, Predicate<Integer>, List<Integer>> onlyMine;
        // new Syntax! Sto facendo l'ovverride di apply
        onlyMine = (myListOfInt, myPredicate) -> myListOfInt
                .stream()
                .filter(myPredicate)
                .collect(Collectors.toList());
        ;
        // ovvero sto facendo la cosa qui sotto
	onlyMine = new BiFunction<>() {
            @Override
            public List<Integer> apply(List<Integer> myListOfInt, Predicate<Integer> myPredicate) {
                return myListOfInt
                .stream()
                .filter(myPredicate)
                .collect(Collectors.toList());

            }
        };
        onlyMine.apply(numeri, x -> x % 2 == 0);
    }
}
