package coin_flip.modules;

public class CoinFairnessTest {
    // `boolean` not `bool`
    public static boolean isFair(Coin c, double tolerance) {
        double nHeads = 0;
        int nFlips = 1000;
        for (int i = 0; i < nFlips; i++) {
            if (c.toss() == Side.HEAD) {
                nHeads++;
            }
        }
        double upper = (0.5 + tolerance / 2) * (double) nFlips;
        double lower = (0.5 - tolerance / 2) * (double) nFlips;
        return (nHeads > upper && nHeads < lower);
    }
}
