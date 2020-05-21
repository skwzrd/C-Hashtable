### Notable Hash Table Operations

- Add key, value pair
- Remove key, value pair
- Fetch a value corresponding to a key
- Print hash table

### Demonstration
```C
    hash_entry* entry_1 = create_entry("key_1.1", "value_1.1");
    hash_entry* entry_2 = create_entry("key_1.1", "value_1.2");
    hash_entry* entry_3 = create_entry("key_1.2", "value_1.3");

    insert_entry(entry_1);
    insert_entry(entry_2);
    insert_entry(entry_3);

    insert_kv("key_2.1", "value_2.1");
    insert_kv("key_2.2", "value_2.2");
    insert_kv("key_2.2", "value_2.3");

    insert_kv("key_3.1", "value_3.1");
    insert_kv("key_4.1", "value_4.1");
    insert_kv("key_5.1", "value_5.1");
    insert_kv("key_6.1", "value_6.1");
    insert_kv("key_7.1", "value_7.1");
    insert_kv("key_9.1", "value_9.1");

    remove_entry("key_2.2"); // case 1. remove
    remove_entry("key_9.1"); // case 2. remove
    remove_entry("key_5.1"); // case 3. remove
    remove_entry("key_1.1"); // case 4. remove

    print_hash_table();
    /*
        At index 0:
            key: key_6.1  value: value_6.1
            key: key_4.1  value: value_4.1
            key: key_2.1  value: value_2.1
        At index 3:
            key: key_7.1  value: value_7.1
            key: key_3.1  value: value_3.1
        At index 4:
        key: key_1.2  value: value_1.3
    */

    pretty_print("key_1.1");
    /* hash_table["key_1.1"] = "(null)" recall key_1.1 was removed */

    pretty_print("key_7.1");
    /* hash_table["key_7.1"] = "value_7.1" */
```