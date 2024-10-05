package coin_flip.modules;

import java.util.Random;

// protected: metodo/attributo visto solo dalle sottoclassi e nel package stesso
//          : (friendly in C++) metodo/attributo visto solo nel package stesso

public class Coin {
    private Side showingSide;
    private final Random generator;
    private final double pHead;

    public Coin() {
        // gia' inizializzato cosi' di default
        this.showingSide = null;
        this.generator = new Random();
        this.pHead = 0.5;
    }

    public Coin(Side showingSide) {
        this.showingSide = showingSide;
        this.generator = new Random();
        this.pHead = 0.5;
    }

    public Coin(int seed) {
        this.showingSide = null;
        this.generator = new Random(seed);
        this.pHead = 0.5;
    }

    public Coin(double pHead) {
        this.showingSide = null;
        this.generator = new Random();
        this.pHead = pHead;
    }

    public Side toss() {
        if (generator.nextDouble() <= pHead) {
            showingSide = Side.HEAD;
        } else {
            showingSide = Side.TAIL;
        }
        return showingSide;
    }

    public Side getShowingSide() {
        return showingSide;
    }
}
