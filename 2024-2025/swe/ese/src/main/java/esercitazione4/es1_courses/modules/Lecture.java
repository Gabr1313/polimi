package esercitazione4.es1_courses.modules;

public class Lecture {
    private final String topic;
    private final Date date;
    private final Faculty speaker; // polimorfismo

    public Lecture(String topic, Date date, Faculty speaker) {
        this.topic = topic;
        this.date = date;
        this.speaker = speaker;
    }

    public String getTopic() {
        return topic;
    }

    public Date getDate() {
        return date;
    }

    @Override
    public String toString() {
        return "Lecture{" +
                "topic='" + topic + '\'' +
                ", date=" + date +
                ", speaker=" + speaker.getName() + " " + speaker.getSurname() +
                '}';
    }
}
