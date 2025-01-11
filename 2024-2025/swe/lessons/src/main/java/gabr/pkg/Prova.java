package gabr.pkg;

public class Prova {
    // friendly by default: visibile a tutte le classi interne allo stesso package
    int attr;
    // protected: visibile a tutte le classi interno allo stesso pacchetto e alle sottoclassi
    protected int attr2;

    // di default, tutte le classi sono figlie di `Object`
    // la classe speciale `Object` e' la root di questo albero di dipendenze,
    // visibile ovunque
    // implementa le funzioni:
    // - `public String toString()` chiamata automaticamente da `print()`
    // - `public final Boolean equals()` usata nella stdlib di Java. Non usano mai `==`
    // - `public final int hashCode()` da ridefinire, se redifinita `equals()`: devono
    //    essere coerenti

    @Override // see above
    public String toString() {
        return "";
    }

    // final @todo che significa? le sottoclassi non la possono cambiare / overriding
    // ovviamente richiede il paramtro Object
    public final boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Prova prova)) return false;
        // `o` viene castato `prova` alla linea sopra, wow
        return attr == prova.attr;
    }

    // public int hashCode() {
    // }

}
