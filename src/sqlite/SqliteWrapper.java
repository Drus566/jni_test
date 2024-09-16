package sqlite;

import howdo1.NativeCallsClass;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SqliteWrapper {
    static {
//        System.out.println("Версия Java: " + System.getProperty("java.version"));
//        System.out.println("Vendor Java: " + System.getProperty("java.vendor"));
//        System.out.println("Директория Java: " + System.getProperty("java.home"));
//        System.out.println("Операционная система: " + System.getProperty("os.name"));
//        System.out.println("Архитектура: " + System.getProperty("os.arch"));
//        System.out.println("Версия ОС: " + System.getProperty("os.version"));

//        System.loadLibrary("sqlitewrapper.dll");
    }

//    native public static void getResult(String pattern);
    public native void getResult(String pattern);

    public static void main(String[] args) {
//        System.out.println(System.getProperty("java.library.path"));
//        String sql = "SELECT * FROM people WHERE name LIKE '%т%'";

//        SqliteWrapper.getResult();
    }
}
