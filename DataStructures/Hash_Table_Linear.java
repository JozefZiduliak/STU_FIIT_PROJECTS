public class Hash_Table_Linear {
    class Data {
        String product_name; // It functions as a key

        int product_price; // It functions as a value
    }

    Data[] data = new Data[1];

    int number_of_elements = 0;

    private static int hash(String input, int size) {

        int hash = 0;
        for (int i = 0; i < input.length(); i++)
            hash = (hash * 31 + input.charAt(i)) % size;

        return hash;
    }

    public void add(String product_name, int product_price) {

        int hash = hash(product_name, data.length); // Get the hash of the key

        if (data[hash] == null || data[hash].product_name.equals("DELETED")) {

            // No collision or deleted key
            // Add the new key-value pair
            data[hash] = new Data();
            data[hash].product_name = product_name;
            data[hash].product_price = product_price;
            number_of_elements++;
        }
        else {

            // Linear probing
            int next_hash = (hash + 1) % data.length;
            while (data[next_hash] != null && !data[next_hash].product_name.equals("DELETED")) {
                next_hash = (next_hash + 1) % data.length;
            }
            // Add the new key-value pair
            data[next_hash] = new Data();
            data[next_hash].product_name = product_name;
            data[next_hash].product_price = product_price;
            number_of_elements++;
        }
        if (number_of_elements > data.length * 0.5) {

            copy_resize(data.length * 2);
        }
    }

    public int get_price(String product_name) {
        int hash = hash(product_name, data.length);

        // Linear probing
        //If the key is found, return the value
        while(data[hash] != null) {
            if (data[hash].product_name.equals(product_name)) {
                return data[hash].product_price;
            }
            else {
                hash = (hash + 1) % data.length;
            }
        }
        return -1;
    }

    public void delete(String product_name) {
        int hash = hash(product_name, data.length);

        // Linear probing
        //If the key is found, set it to "DELETED"
        while(data[hash] != null) {
            if (data[hash].product_name.equals(product_name)) {
                data[hash].product_name = "DELETED";
                number_of_elements--;


                if (number_of_elements < data.length * 0.25) {

                    copy_resize(data.length / 2);
                }
            }
            else {
                hash = (hash + 1) % data.length;
            }
        }
    }


    public void copy_resize(int new_size)
    {
        number_of_elements = 0;

        Data[] old_data = new Data[data.length];

        System.arraycopy(data, 0, old_data, 0, data.length);

        data = new Data[new_size];


        for (int i = 0; i < old_data.length; i++) {
            if (old_data[i] != null && !old_data[i].product_name.equals("DELETED")) {

                add(old_data[i].product_name, old_data[i].product_price);

            }
        }

    }

    public void print() {
        for (int i = 0; i < data.length; i++) {
            if (data[i] != null) {
                System.out.println(i +". Key: " + data[i].product_name + " Value: " + data[i].product_price);
            }
        }
    }

}
