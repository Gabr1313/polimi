package esercitazione4.es1_courses.modules;

public class Mail {
    private final String sender;
    private final String subject;
    private final String object;

    public Mail(String sender, String subject, String object) {
        this.sender = sender;
        this.subject = subject;
        this.object = object;
    }

    @Override
    public String toString() {
        return "Mail{" +
                "sender='" + sender + '\'' +
                ", subject='" + subject + '\'' +
                ", object='" + object + '\'' +
                '}';
    }
}
