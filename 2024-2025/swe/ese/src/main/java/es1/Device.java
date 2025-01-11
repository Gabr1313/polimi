package es1;

class Device {
    public String toString() { return "a generic device"; }
}

class Watch extends Device {
    public String toString() { return "a watch"; }
}

class Smartwatch extends Watch {
    public String toString() { return "a smartwatch"; }
}
