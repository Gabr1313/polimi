package coin_flip;

import coin_flip.modules.Coin;
import coin_flip.modules.CoinFairnessTest;
import coin_flip.modules.Side;

public class Main {
    /* public static void main(String[] args) { 
        Coin c = new Coin(.7);
        int nHeads = 0;
        for (int i = 0; i < 50; i++) {
            Side s = c.toss();
            if (s==Side.HEAD) {
                nHeads++;
            }
        }
        System.out.println("Tossed heads: " + nHeads);
    } */
    public static void main(String[] args) { 
        Coin c = new Coin(.7);
        boolean fair = CoinFairnessTest.isFair(c, 0.05);
        System.out.println("Is fair? " + fair);
    }
}
