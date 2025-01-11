package gabr.concurrency;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class Main {
    // processi concorrenti condividono l'heap (non lo stack)
    // => gli oggetti sull'heap hanno un lock associato (esprimibile usando syncronized)
    // => gli oggetti sullo stack non hanno un lock associato
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        Thread t = new MyThread();
        t.start();
        // try-catch or throws
        t.join();

        // e' anche funzionale: runnable = () -> ()
        Thread t1 = new Thread(() -> System.out.println("ciao"));
        t1.start();
        t1.join();

        BankAccount account = new BankAccount(1000);
        // illegal, account would not be effectively final
        // account = new BankAccount(2000);
        Thread tDep = new Thread(() -> {
            for (int i = 0; i < 1000; i++) {
                // effectively final
                account.deposit(1);
            }
        });
        Thread tWith = new Thread(() -> {
            for (int i = 0; i < 1000; i++) {
                // effectively final
                account.withdraw(1);
            }
        });
        tDep.start();
        tWith.start();
        tDep.join();
        tWith.join();
        System.out.println(account.getBalance() + " == 1000: no concurrency problems");

        BankAccount a = new BankAccount(1000);
        Thread tTran = new Thread(() -> {
            // non locka, wow
            for (int i = 0; i < 1000; i++) {
                a.transfer_dead_lock(a, 100);
            }
        });
        tTran.start();
        tTran.join();

        BankAccount a1 = new BankAccount(1000);
        BankAccount a2 = new BankAccount(1000);
        Thread tTran1 = new Thread(() -> {
            for (int i = 0; i < 1000; i++) {
                a1.transfer(a2, 100);
            }
        });
        Thread tTran2 = new Thread(() -> {
            for (int i = 0; i < 1000; i++) {
                a2.transfer(a1, 100);
            }
        });
        tTran1.start();
        tTran2.start();
        tTran1.join();
        tTran2.join();

        System.out.println(account.getBalance());

        // Thread Pool
        // creare thread costa!
        // ExecutorService e' un'interfaccia
        // riutilizzza i thread esistenti o ne istanzia ad hoc se non bastano
        // ExecutorService es = Executors.newCachedThreadPool();
        // ne fa partire n nuovi
        ExecutorService executor = Executors.newFixedThreadPool(4);
        // permette di passare un runnable
        executor.submit(() -> System.out.println("Hello"));
        executor.submit(() -> System.out.println("HelloHello"));
        // se non lo metto l'applicazione non si spegne mai
        // shutdown(): prima completa i task e poii shutdown
        // shutdownNow(): chiude i thread e non completa i task in sospeso
        executor.shutdown();
        // specifica a shutdown quanto aspettare al massimo
        // e la join in altri linguaggi
        // se ritorna true esce dal while (e lo ritorna anche senza aspettare i 10
        // secondi)
        // senza il while continuerei l'esecuzione anche senza aspettare che tutti
        // finiscano
        // ovviamente awaitTermination() sereve solo se dopo devo eseguire codice che
        // richieda
        // che tutti i thread abbaino finito
        // awaitTerminatin senza shutdown non ha senso
        // non posso dire "aspetta che finiscano tutti i task senza spegnere i thread"
        // dovrei usare i feature per fare qualcosa di simile
        while (!executor.awaitTermination(10, TimeUnit.SECONDS))
            ;

        executor = Executors.newFixedThreadPool(4);
        // Overload: da Runnable a Callable<T>: () -> T
        Future<String> s1 = executor.submit(() -> "Hello");
        Future<String> s2 = executor.submit(() -> "Hello");

        // wait finche' non lo ottengo
		String s1content = s1.get();
        System.out.println(s1content + s2.get());

        executor.shutdown();
        while (!executor.awaitTermination(10, TimeUnit.SECONDS))
            ;
        // CompletableFuture<T> serve per dire "appena ho il valore, applica queste trasformazioni"

        List<String> myList = new ArrayList<>();
        // decorator (wrapper), che mette synchronized attorno a tutti i metodi
        // List<String> myListSync = Collections.synchronizedList(myList);
        // modificandono una tra myList e myListSync, si modificano entrambe (penso)
        myList = Collections.synchronizedList(myList);
        // sono pero' meglio strutture dati ottimizzate per essere thread-safe
        Map<String, Integer> map = new ConcurrentHashMap<>();

        // gli stream, essendo immutabili, non hanno problemi di concorrenza
    }
}
