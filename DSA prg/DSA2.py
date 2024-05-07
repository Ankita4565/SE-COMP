class HashTable:
    def __init__(self, size):
        self.size = size
        # Initialize a list of lists (buckets) for separate chaining
        self.table = [[] for _ in range(size)]

    def hash_function(self, key):
        # Calculate the index using the hash of the key modulo the size of the hash table
        return hash(key) % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        # Check if the key already exists in the bucket at the calculated index
        for pair in self.table[index]:
            if pair[0] == key:
                # Update the value if the key is already present
                pair[1] = value
                return
        # If the key is not found, append a new key-value pair to the bucket
        self.table[index].append([key, value])

    def find(self, key):
        index = self.hash_function(key)
        # Search the bucket at the calculated index for the key
        for pair in self.table[index]:
            if pair[0] == key:
                # Return the value if the key is found
                return pair[1]
        # Return None if the key is not found
        return None

    def delete(self, key):
        index = self.hash_function(key)
        # Search the bucket at the calculated index for the key
        for i, pair in enumerate(self.table[index]):
            if pair[0] == key:
                # Delete the key-value pair if the key is found
                del self.table[index][i]
                return
        # Raise a KeyError if the key is not found
        raise KeyError("Key not found")

# Demonstration of using the HashTable class
if __name__ == "__main__":
    hash_table = HashTable(10)  # Create a hash table with 10 buckets
    hash_table.insert("apple", 10)  # Insert a key-value pair
    hash_table.insert("banana", 20)  # Insert another key-value pair

    # Find and print the value associated with the key "apple"
    print(hash_table.find("apple"))  # Output: 10

    # Find and print the value associated with the key "banana"
    print(hash_table.find("banana"))  # Output: 20

    # Delete the key-value pair associated with the key "apple"
    hash_table.delete("apple")

    # Try to find the value associated with the key "apple" after deletion
    print(hash_table.find("apple"))  # Output: None (since the key was deleted)
