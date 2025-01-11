package gabr.prove;

import java.util.Optional;
import java.util.function.Function;

public class Boh {
	int val;
	Function<Integer, Integer> fff;

	public Boh() {
		this.fff = new Function<Integer, Integer>() {
			@Override
			public Integer apply(Integer x) {
				return x + Boh.this.val;
			}
		};
	}

	public void boh() {
		System.out.println(Optional.of(1).map(x -> x + this.val).get());
		Function<Integer, Integer> ggg = new Function<Integer, Integer>() {
			@Override
			public Integer apply(Integer x) {
				return x + val;
			}
		};
		this.val++;
		System.out.println(Optional.of(1).map(ggg).get());
	}

	public void update() {
		val++;
	}
}
