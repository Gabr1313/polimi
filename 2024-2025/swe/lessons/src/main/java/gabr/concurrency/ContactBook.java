package gabr.concurrency;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ContactBook {
    private final Map<String, Integer> contacts;
    private final ReadWriteLock lock;

    public ContactBook() {
        // sarebbe meglio:
        // this.contacts = new ConcurrentHashMap<>();
        this.contacts = new HashMap<>();
        // gli accessi in lettura non vanno tra loro in conflitto
        // esistono i read-write lock
        // Reentrant: se un thread ha gia' il lock, lo puo' riacquisire senza problemi
        //            e deve anche rilasciare lo stesso numero di lock acquisiti
        this.lock = new ReentrantReadWriteLock();
    }

    public void add(String name, int num) {
        // e quindi i lock li devo gestire cosi'
        lock.writeLock().lock();
        this.contacts.put(name, num);
        // e quindi i lock li devo gestire cosi'
        lock.writeLock().unlock();
    }

    public int get(String name) {
        // e quindi i lock li devo gestire cosi'
        lock.readLock().lock();
        int result = this.contacts.get(name);
        // e quindi i lock li devo gestire cosi'
        lock.readLock().unlock();
        return result;
    }
}
