package ver1;

public class User {
    void info() {
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
        System.out.println("Is man: " + is_man);
    }

    User(String name, int age, boolean is_man) {
        this.name = name;
        this.age = age;
        this.is_man = is_man;
    }

    String name;
    int age;
    boolean is_man;
}
