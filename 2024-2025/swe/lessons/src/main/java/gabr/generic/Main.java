package gabr.generic;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import gabr.exception.EmptyListException;

public class Main {
    public static void main(String[] args) {
        Pair<String> pair1 = new Pair<String>("Ciao", "Pino");
        // uguale a sopra
        Pair<String> pair2 = new Pair<>("Ciao", "Pino");

        // non worka perche' `int` e' tipo primitivo, e i generics funzionano solo
        // rispetto ai tipi classe -> esiste `Integer`
        // Java fa in automatico i cast
        // E quindi posso anche fare le ordinarie operazioni, senza boilerplate
        Pair<Integer> pair3 = new Pair<>(1, 2);

        List<Integer> l1 = new LinkedList<>();
        l1.add(1);
        // wow, posso trasformare il tipo di l1
        // l1 va nel gc e ne viene allocata una nuova
        l1 = new ArrayList<>();
        l1.add(0);
        System.out.println("List: " + l1);
        System.out.println("List size: " + l1.get(0)); // niente `[` `]` !

        Set<String> set1 = new HashSet<>();
        set1.add("Ciao");
        set1.add("Ciao");
        set1.add("Pino");
        System.out.println("Elementi: " + set1.size()); // 2
        
        // clone
		Set<String> set2 = new HashSet<>(set1);

        // HashMap
        Map<String, Integer> map1 = new HashMap<>();
		// map1.entrySet();
        map1.put("Ale", 231);
        System.out.println(map1.get("Ale"));
        System.out.println(map1.get("Ale"));

        ArrayList<String> a1 = new ArrayList<>();
        // ArrayList<Object> o1 = a1; // non posso perche' altrimenti potrei buttarci
        // dentro qualsiasi cosa, anche non String:
        // i generici NON sono CO-VARIANTI con l'ereditarieta': sono INVARIANTI
        // ovviamente nemmeno vicenversa

        // e' valida sintassi!
        ArrayList<? extends String> a2 = new ArrayList<>();

        for (Integer s : l1) {
            System.out.println(s);
        }
        // `Iterable` e' un'interfaccia con 2 metodo: `hasNext()` e `next()`
        // quello sopra e' sintactic sugar per
        // `Iterator` e' un generic che implenta `Iterable`
        Iterator<Integer> it = l1.iterator();
        while (it.hasNext()) {
            Integer s = it.next();
            System.out.println(s);
        }

        for (String s : pair1) {
            System.out.println(s);
        }

        List<Integer> myList = new ArrayList<>();
        try {
            GenericsUtils.getFirst(myList);
        } catch (EmptyListException e) {
            System.out.println(e.getMessage());
        }
        // esistono anche eccezioni a run-time, che non sono obbligatorie da checkare in
        // quanto non sono conosciute a comp-time. Sarebbero da mettere attorno a ogni
        // pezzo di codice
        // queste quindi sono opzionali da controllare. quelle a comp-time sono 
        // obbligatorie invece
        // `finally` si mette quando voglio che il codice venga eseguito prima del return
        // della funzione, indifferentemente da cosa succede nel try-catch
    }
}
