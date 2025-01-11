package gabr.generic;

import java.util.List;

import gabr.exception.EmptyListException;

/// 
public class GenericsUtils {
    // metto prima <T> per dire che e' il valore generico
    // `throws` keyword, chiamabile solo su `implements Throwable`...
    // nel nostro caso solo su `extends Exception`
    public static <T> T getFirst(List<T> list) throws EmptyListException {
        if (list.isEmpty()) {
            // return null; // orrore
            throw new EmptyListException("List is empty");
        }
        return list.get(0);
    }

    // per dire che 2 istanze sono confrontabili, allora devono implementare
    // `Comparable()`
    // la lista e di <T> e <T extends Comparable<T>>
    public static <T extends Comparable<T>> T getMax(List<T> list) throws EmptyListException {
        if (list.isEmpty()) {
            // return null; // orrore
            throw new EmptyListException("List is empty");
        }
        T max = list.get(0);
        for (T x : list) { // come in C++
            // .compareTo() ritorna 1, 0, -1 (1 se chiamante > argument etc.)
            max = x.compareTo(max) > 0 ? x : max;
        }
        return max;
    }
}
