package gabr.concurrency;

public class BankAccount {
    private int balance;

    // i costruttori non si sincronizzano ovviamente
    public BankAccount(int balance) {
        this.balance = balance;
    }

    // synchronized e' garantito sulla stessa istanza:
    // non permette di chiamare piu' funzioni synchronized insieme
    // (come avere un mutex unico intorno alle chiamate synchronized)
    public synchronized void deposit(int amount) {
        // o alternativamente posso
        // synchronized prende in ingresso anche un attributo, purche' sia un oggetto
        synchronized (this) {
            this.balance += amount;
            // serve per avvertire withdraw() che il denaro e' cambiato
            // e' lecito chiamare notify notify() solo all'interno di un blocck synchronized
            // e viene chiamata quando rilascia il lock
            // this.notify();
            this.notifyAll();
        }
    }

    public synchronized void withdraw(int amount) {
        // metti sempre il while attorno a una wait()
        // anche perche' ogni tanto Java puo' risvegliare a caso un lock()
        while (balance < amount) {
            // va in stato di attesa, durante il quale rilascia il lock
            // (controlla che il lock rilasciato sia lo stesso che serve altrove, e vv)
            // e' lecito chiamare wait solo internamente a un blocco synchronize
            try {
                this.wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        this.balance -= amount;
    }

    public synchronized int getBalance() {
        return balance;
    }

    public void transfer_dead_lock(BankAccount other, int amount) {
        // this.transfer(this) non va in deadlock
        synchronized (this) {
            this.balance -= amount;
            synchronized (other) {
                other.balance += amount;
            }
        }
    }

    public void transfer(BankAccount other, int amount) {
        this.withdraw(amount);
        other.deposit(amount);
    }
}
