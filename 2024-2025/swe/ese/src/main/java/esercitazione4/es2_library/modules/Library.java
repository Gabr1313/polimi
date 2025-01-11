package esercitazione4.es2_library.modules;

import java.util.Collection;
import java.util.HashSet;

public class Library {
    final private Collection<Document> catalogue;

    public Library() {
        catalogue = new HashSet<>();
    }
    // Utilizziamo il polimorfismo: tipo statico Collection, tipo dinamico HashSet
    // In questo modo se volessimo cambiare l'implementazione del catalogo, basta cambiare l'istanziazione
    //      utilizzano un'altra classe che implementa Collection.
    //
    // HashSet evita che ci siano elementi uguali
    // Organizza gli elementi in bucket utilizzando il metodo hashCode
    // hashCode è una funzione di hash: restituisce il numero del bucket dati i valori degli attributi selezionati
    // Prima di inserire un elemento controlla che in quel bucket non ci siano altri elementi uguali
    // Per la scelta del bucket utilizza hashCode
    // Per il check sull'uguaglianza utilizza il metodo equals

    public void addDocument(Document d) {
        catalogue.add(d);
    }

    public boolean loanDocument(Document d) {
        if (d.isLoanable()){
            LoanableDocument dl = (LoanableDocument) d;
            dl.loanDocument();
            return dl.isOnLoan();
        }
        return false;
    }

    public boolean returnDocument(Document d) {
        if (d.isLoanable()) {
            LoanableDocument dl = (LoanableDocument) d;
            return dl.returnDocument();
        }
        return false;
    }

    public Document getDocumentByCode(int code) {
        for (Document d : catalogue) {
            if (d.getCode() == code) return d;
        }
        return null;
    }

    public int generateCode() {
        return catalogue.size()+1;
    }

    public String toString() {
        String s = "";
        for (Document d : catalogue) {
            s += d.toString() + "\n\n";
        }
        return s.substring(0, s.length()-2);
    }
}
