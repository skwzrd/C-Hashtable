### Notable Hash Table Operations

- Add key, value pair
- Remove key, value pair
- Fetch a value corresponding to a key
- Print hash table

### Demonstration
```C
hash_entry* entry_1 = create_entry("A", "1");
hash_entry* entry_2 = create_entry("B", "2");

insert_entry(entry_1);
insert_entry(entry_2);

insert_kv("C", "3");

remove_entry("C");

print_hash_table();

print("A");

print("C");

/*
Outputs:

    At index 2:
        key: A  value: 1
    At index 3:
        key: B  value: 2

    hash_table["A"] = "1"

    hash_table["C"] = "(null)"
*/
```