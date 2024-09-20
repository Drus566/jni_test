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
        String sql_query = "SELECT * FROM PERSON WHERE name LIKE '%и%';";
        Response resp = bridge.search(sql_query);
//        Response resp = bridge.test();

//        while (resp.next()) {
//            Integer i = resp.getInteger(2);
//            String str = resp.getString(1);
//            System.out.println(i + ": " + str);
//        }

        while (resp.next()) {
            Integer i = resp.getInteger(1);
            String str = resp.getString(2);
            System.out.println(i + ": " + str);
        }
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
