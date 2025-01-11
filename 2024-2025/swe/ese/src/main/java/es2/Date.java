package es2;

abstract class Date {
    public abstract String dateDistance(Date d);
}

class DayDate extends Date{
    int day;

    public String dateDistance(Date p) {
        System.out.println("* CLASS DayDate, PARAMETER Date");
        System.out.println("p dynamic class: "+p.getClass().getName());
        return "Distance of the two dates is" + dateDistance((DayDate) p);
    } // override del metodo di Date

    public String dateDistance(DayDate p) {
        DayMonthDate d = (DayMonthDate) p;
        System.out.println("* CLASS DayDate, PARAMETER DayDate");
        System.out.println("p dynamic class: "+p.getClass().getName());
        return ": " + (day-p.day) + " days";
    } // aggiunta di un nuovo metodo
    // attenzione al cast

    public DayDate(int d) { day=d; }
}

class DayMonthDate extends DayDate {
    int month;
    DayMonthDate(int d, int m) { super(d); month = m; }

    public String dateDistance(Date p) {
        System.out.println("* CLASS DayMonthDate, PARAMETER Date");
        System.out.println("p dynamic class: "+p.getClass().getName());
        return "Distance in days and months is" + dateDistance((DayMonthDate) p);
    } // override del metodo di DayDate

    public String dateDistance(DayMonthDate p) {
        System.out.println("* CLASS DayMonthDate, PARAMETER DayMonthDate");
        System.out.println("p dynamic class: "+p.getClass().getName());
        return super.dateDistance(p) + ": " + (month - p.month) + " months";
    }
    // chiamo il metodo della superclasse
}

class DayMonthYearDate extends DayMonthDate {
    int year;

    DayMonthYearDate(int d, int m, int y) { super(d, m); year = y; }

    public String dateDistance(Date p) {
        System.out.println("* CLASS DayMonthYearDate, PARAMETER Date");
        System.out.println("p dynamic class: "+p.getClass().getName());
        return "Distance in d-m-y is" + dateDistance((DayMonthYearDate) p);
        // potrebbe esserci un problema nel cast da Date a DayMonthYearDate
    }

    public String dateDistance(DayMonthYearDate p) {
        System.out.println("* CLASS DayMonthYearDate, PARAMETER DayMonthYearDate");
        System.out.println("p dynamic class: "+p.getClass().getName());
        return super.dateDistance(p) + ": " + (year - p.year) + " years";
    }
}
