package gabr;

public class Square extends Quadrilater {
    // posso non dichiarare `Square()` perche' il constructor e' gia' dichiarato in
    // `Quadrilater`. Se invece avessi un attribute final in `Quadrilater`, allora
    // dovrei dichiarare il constructor

    public void draw() {
        System.out.println("Square");
    }
}
