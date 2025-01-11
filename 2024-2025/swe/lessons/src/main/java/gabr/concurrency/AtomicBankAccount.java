package gabr.concurrency;

import java.util.concurrent.atomic.AtomicInteger;

// su alcune architetture questi vengono compilate meglio (utilizza hardware apposito)
public class AtomicBankAccount {
    // nice
    private AtomicInteger balance;

    public AtomicBankAccount() {
        balance = new AtomicInteger();
    }

    public void deposit(int amount) {
        balance.addAndGet(amount);
    }

    public void withdraw(int amount) {
        balance.addAndGet(-amount);
    }

    public int getBalance() {
        return balance.get();
    }
}
