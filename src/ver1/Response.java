package ver1;

import java.util.List;

public class Response {
    private final List<List<Object>> data;
    private int current_row;

    public Response(List<List<Object>> data) {
        this.data = data;
        this.current_row = -1;
    }

    public boolean next() {
        current_row++;
        return (current_row < data.size());
    }

    public Object getObject(int column_index) { return data.get(current_row).get(column_index - 1); }
    public int getInteger(int column_index) { return (Integer) getObject(column_index); }
    public String getString(int column_index) { return (String) getObject(column_index); }
    public boolean getBoolean(int column_index) { return (Boolean) getObject(column_index); }
    public float getFloat(int column_index) { return ((Float)getObject(column_index)).floatValue(); }
}
