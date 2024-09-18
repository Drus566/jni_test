package ver1;

import java.util.List;

public class Bridge {
//    public static native User createObject(String name, int age, boolean bool);
//    public static native int getObjectValue(User obj);
//    public static native void setObjectValue(User obj, int value);
//    public static native void test();

    public native User createObject(String name, int age, boolean bool);
    public native int getObjectValue(User obj);
    public native void setObjectValue(User obj, int value);
    public native List<List<Object>> testObj();
    public native Response test();
}
