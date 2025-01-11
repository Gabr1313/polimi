package gabr.generic;

import java.util.Iterator;

// generics: come in Rust
public class Pair<T> implements Iterable<T> {
    private final T first;
    private final T second;

    public Pair(T first, T second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() {
        return first;
    }

    public T getSecond() {
        return second;
    }

    @Override
    public Iterator<T> iterator() {
        return new PairIterator(this);
    }

    ///
    // carino che si possa definire classi in classi
    // l'ho dovuta definire, cosi' che sia mutabile, al contrario di pair che
    // potrebbe non esserlo
    // Avrei potuto ottenere la stessa visibilita' creando un altro file? No
    private class PairIterator implements Iterator<T> {
        private Pair<T> pair;
        private int current;

        public PairIterator(Pair<T> pair) {
            this.pair = pair;
            this.current = 0;
        }

        @Override
        public boolean hasNext() {
            return current < 2;
        }

        @Override
        public T next() {
            if (current == 0) {
                current++;
                return pair.getFirst();
            } else if (current == 1) {
                current++;
                return pair.getSecond();
            } else {
                return null;
            }
        }
    }
}

/// qui fuori posso mettere quante classi voglio purche' non siano public,
// e private (chi le chiama)
