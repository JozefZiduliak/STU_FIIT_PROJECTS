public class Hast_Table_Quadratic {
    class Data {
        String product_name; // It functions as a key

        int product_price; // It functions as a value
    }

    //Hash table
    Data[] data = new Data[1];

    //Number of elements in the hash table
    int number_of_elements = 0;

    //return size of table
    public void get_size_of_table()
    {
        System.out.println("Size of table: " + data.length);
    }

    private static int hash(String input, int size) {

        int hash = 0;
        for (int i = 0; i < input.length(); i++)
            hash = (hash * 37 + input.charAt(i)) % size;

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
            // Quadratic probing
            int next_hash = (hash + 1) % data.length;

            for(int i = 1; data[next_hash] != null && !data[next_hash].product_name.equals("DELETED"); i++) {
                next_hash = (hash + i * i) % data.length;
            }
            // Add the new key-value pair

            data[next_hash] = new Data();
            data[next_hash].product_name = product_name;
            data[next_hash].product_price = product_price;

            number_of_elements++;
        }

        // Resize the hash table if the number of elements is more than 50% of the size of the hash table
        if (number_of_elements > data.length * 0.5) {
            copy_resize(data.length * 3);
        }
    }

    public void copy_resize(int new_size)
    {
        number_of_elements = 0; //Resets the number of elements , because add functions will increment it

        Data[] old_data = new Data[data.length]; //TMP array to store data

        System.arraycopy(data, 0, old_data, 0, data.length);

        data = new Data[new_size]; //Resize the hash table


        //Add all elements from old_data to new hash table
        for (int i = 0; i < old_data.length; i++) {
            if (old_data[i] != null && !old_data[i].product_name.equals("DELETED")) {
                add(old_data[i].product_name, old_data[i].product_price);
            }
        }
    }

    //Method that returns the price of a product
    public int get_price(String product_name)
    {
        int hash = hash(product_name, data.length); // Get the hash of the key
        int tmp = hash; // TMP variable to store the hash

        // Quadratic probing
        for(int i = 1;data[hash] != null; i++) {
            if (data[hash].product_name.equals(product_name)) {
                return data[hash].product_price;
            }
            else {
                hash = (tmp + i * i) % data.length;
            }
        }
        return -1; //Return -1 if the product is not found
    }

    public void delete(String product_name) {
        int hash = hash(product_name, data.length); // Get the hash of the key
        int tmp = hash;  // TMP variable to store the hash

        //System.out.println("Deleting: " + product_name);

        // Quadratic probing
        for(int i = 1;data[hash] != null; i++) {

           // System.out.println("Hash: " + hash);

            if (data[hash].product_name.equals(product_name)) {
                data[hash].product_name = "DELETED";
                data[hash].product_price = -1;
                return;
            }
            else {
                hash = (tmp + i * i) % data.length;
            }
        }
    }

    //Print the whole hash table
    public void print() {
        for (int i = 0; i < data.length; i++) {
            if (data[i] != null) {
                System.out.println(i +". Key: " + data[i].product_name + " Value: " + data[i].product_price);
            }
        }
    }
}
