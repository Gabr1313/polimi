package gabr.prove;

import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Queue;
import java.util.Set;
import java.util.TreeMap;
import java.util.concurrent.locks.ReentrantLock;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.LongStream;

public class Main {

	public static void main(String[] args) {
		List<Integer> l = new ArrayList<>();
		System.out.println(l.stream().findFirst().isEmpty());
		System.out.println(IntStream.range(1, 4).reduce((x, y) -> x * y).orElse(-1));
		System.out.println(IntStream.range(1, 1).reduce((x, y) -> x * y).orElse(1));
		System.out.println(IntStream.range(1, 4).reduce(1, (acc, x) -> acc * x));
		System.out.println(IntStream.range(1, 1).reduce(1, (acc, x) -> acc * x));
		System.out.println(IntStream.range(1, 1).distinct().count());
		l = Arrays.asList(1, 2, 1);
		System.out.println(l.stream().distinct().count());
		// error !!
		// System.out.println(IntStream.range(1, 1).reduce(1.0, (x, y) -> x *
		// (Double)y));
		// System.out.println(l.stream().findFirst().get());

		List<String> ll = new ArrayList<>();
		ll.add("a");
		ll.add("b");
		ll.add("c");
		Optional<String> prova = ll
				.stream()
				.filter(x -> x == "d")
				.findFirst()
				.map(x -> "e");
		System.out.println(prova);

		class iii {
			public void foo(int x) {
				System.out.println("iii " + x);
			}
		}

		class fff extends iii {
			public void foo(double x) {
				System.out.println("fff " + x);
			}

			public void bar(double x) {
				System.out.println("www " + x);
			}
		}

		iii i = new iii();
		fff f = new fff();

		i.foo(2);
		// i.foo(2.1);
		f.foo(2);
		f.foo(2.1);
		f.bar(2);

		Foo foo = new Foo();
		Bar1 b1 = new Bar1();
		Bar1 b2 = new Bar2();
		b2.getClass();
		foo.print(b1);
		foo.print(b2);

		Map<Integer, String> m = new HashMap<>();
		m.entrySet().stream().map(x -> x.getKey());
		System.out.println(m.get(1));

		String s;

		List<Integer> ld = Arrays.asList(1, 2, 1);
		System.out.println(ld.stream().max(Comparator.naturalOrder()).get());
		System.out.println(ld.stream().max(Comparator.naturalOrder()));
		System.out.println(Double.MAX_VALUE);
		List<Integer> lx = ld.stream().collect(ArrayList<Integer>::new, (x, y) -> x.add(y), (x, y) -> x.addAll(y));
		Optional<Integer> opt;

		List<String> vowels = List.of("a", "e", "i", "o", "u");

		ArrayList<String> al = new ArrayList<>();
		al.add(0, "2");
		al.add(0, "3");
		System.out.println(al);

		// sequential stream - nothing to combine
		String result = vowels.stream().collect(StringBuilder::new, (x, y) -> x.append(y),
				(a, b) -> a.append(",").append(b)).toString();
		System.out.println(result);
		StringBuilder result1 = vowels.parallelStream().collect(StringBuilder::new,
				(x, y) -> x.append(y),
				(a, b) -> a.append(",").append(b));
		System.out.println(result1.toString());

		Bar2 bbb = new Bar2();
		bbb.n();

		int[] arrg;

		Set<Integer> si = new HashSet<>();

		System.out.println(IntStream.iterate(0, x -> x + 1).filter(x -> x > 10).findAny());
		Boh b = new Boh();
		b.boh();
		b.update();
		b.boh();

		PrintStream x = new PrintStream(System.out);
	}

	/*
	 * class Veicolo {
	 * protected void accensione(int tempoMax) {
	 * System.out.println("accensione-Veicolo in " + tempoMax);
	 * }
	 * 
	 * public void spegnimento() {
	 * System.out.println("spengo-Veicolo");
	 * }
	 * }
	 * 
	 * class VeicoloAMotore extends Veicolo {
	 * public void accensione(int tempoMax) {
	 * System.out.println("accensione-VeicoloAMotore in " + tempoMax);
	 * }
	 * 
	 * public void spegnimento(int tempo) {
	 * System.out.println("spengo-VeicoloAMotore");
	 * }
	 * }
	 * 
	 * public class Motociclo extends VeicoloAMotore {
	 * public void accensione(double tempoMax) {
	 * System.out.println("accensione-Motociclo in " + tempoMax);
	 * }
	 * 
	 * public void spegnimento() {
	 * System.out.println("spengo-MotoCiclo");
	 * }
	 * }
	 * 
	 * public static void main(String[] args) {
	 * Veicolo v = new Main().new Veicolo();
	 * Veicolo v1 = new Main().new VeicoloAMotore();
	 * VeicoloAMotore vm2 = new Main().new Motociclo();
	 * v.accensione(3);
	 * v1.accensione(3);
	 * vm2.accensione(3);
	 * v.spegnimento();
	 * v1.spegnimento();
	 * vm2.spegnimento();
	 * vm2.spegnimento(2);
	 * Motociclo m = new Main().new Motociclo();
	 * m.accensione(2.0);
	 * }
	 */
}
