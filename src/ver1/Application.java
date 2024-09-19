package ver1;

import com.sun.org.apache.xpath.internal.operations.Bool;
import howdo1.NativeCallsClass;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class Application {
    static {
//        System.loadLibrary("icu32");
//        System.loadLibrary("libnewicudt75");
//        System.loadLibrary("libnewicuuc75");
//        System.loadLibrary("libnewicuio75");
//        System.loadLibrary("libnewicudt75");
//
//        System.loadLibrary("libnewicuin75");

        System.loadLibrary("322");
        System.loadLibrary("ver2_bridge32");
    }

    public static void info() {
        System.out.println("Версия Java: " + System.getProperty("java.version"));
        System.out.println("Vendor Java: " + System.getProperty("java.vendor"));
        System.out.println("Директория Java: " + System.getProperty("java.home"));
        System.out.println("Операционная система: " + System.getProperty("os.name"));
        System.out.println("Архитектура: " + System.getProperty("os.arch"));
        System.out.println("Версия ОС: " + System.getProperty("os.version"));
        System.out.println(System.getProperty("java.library.path"));
    }

    public static void main(String[] args) {
        Bridge bridge = new Bridge();
        info();
        User u = new User("Вася",13,true);
        bridge.setObjectValue(u, 3);
        User new_user = bridge.createObject("Иван", 12, true);
        new_user.info();
        List<List<Object>> lists = bridge.testObj();
        for (List<Object> l : lists) {
            String str = (String)l.get(0);
            Integer i = (Integer)l.get(1);
            Boolean b = (Boolean)l.get(2);

            System.out.println(str + " " + i + " " + b);
        }

        Response resp = bridge.test();
        while (resp.next()) {
            String str = resp.getString(1);
            Integer i = resp.getInteger(2);
            Boolean b = resp.getBoolean(3);
            System.out.println(str + " " + i + " " + b);
//            System.out.println("GG");
        }


//        NativeCallsClass nc = new NativeCallsClass();
//        nc.printOne(); // Invoke native method
//        nc.printTwo(); // Invoke native method
//        NativeCallsClass.MyObject mobj = nc.createObject(2);
//        int i = nc.getObjectValue(mobj);
//        nc.setObjectValue(mobj, 3);
    }

    public static void showFrame() {
        // Создание нового окна
//        JFrame frame = new JFrame("Пример окна Swing");

        // Установка размера окна
//        frame.setSize(400, 300);

        // Завершение работы приложения при закрытии окна
//        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Создание кнопки
//        JButton button = new JButton("Нажми меня!");

        // Добавление обработчика события для кнопки
//        button.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                JOptionPane.showMessageDialog(frame, "Кнопка нажата!");
//            }
//        });
//
//        // Добавление кнопки в окно
//        frame.getContentPane().add(button);
//
//        // Установка окна видимым
//        frame.setVisible(true);
    }
}
