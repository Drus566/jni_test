package ver1;

public class Bridge {
    public static native User createObject(String name, int age, boolean bool);
    public static native int getObjectValue(User obj);
    public static native void setObjectValue(User obj, int value);
}
