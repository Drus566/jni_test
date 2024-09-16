package howdo1;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class NativeCallsClass {

    static class MyObject {
        private int value;

        public MyObject(int value) {
            this.value = value;
        }

        public int getValue() {
            return value;
        }

        public void setValue(int value) {
            this.value = value;
        }
    }

    static {
        System.out.println("Версия Java: " + System.getProperty("java.version"));
        System.out.println("Vendor Java: " + System.getProperty("java.vendor"));
        System.out.println("Директория Java: " + System.getProperty("java.home"));
        System.out.println("Операционная система: " + System.getProperty("os.name"));
        System.out.println("Архитектура: " + System.getProperty("os.arch"));
        System.out.println("Версия ОС: " + System.getProperty("os.version"));

        System.loadLibrary("megalib32");
    }
    native public static void printOne();
    native public static void printTwo();

    public static native MyObject createObject(int value);
    public static native int getObjectValue(MyObject obj);
    public static native void setObjectValue(MyObject obj, int value);


    public static void main(String[] args) {
        System.out.println(System.getProperty("java.library.path"));

        NativeCallsClass nc = new NativeCallsClass();
        nc.printOne(); // Invoke native method
        nc.printTwo(); // Invoke native method
        MyObject mobj = nc.createObject(2);
        int i = nc.getObjectValue(mobj);
        System.out.println(i);
        nc.setObjectValue(mobj, 3);
        System.out.println(mobj.getValue());


        // Создание нового окна
        JFrame frame = new JFrame("Пример окна Swing");

        // Установка размера окна
        frame.setSize(400, 300);

        // Завершение работы приложения при закрытии окна
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Создание кнопки
        JButton button = new JButton("Нажми меня!");

        // Добавление обработчика события для кнопки
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(frame, "Кнопка нажата!");
            }
        });

        // Добавление кнопки в окно
        frame.getContentPane().add(button);

        // Установка окна видимым
        frame.setVisible(true);

    }
}
