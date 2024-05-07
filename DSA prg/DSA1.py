class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class HashTable:
    def __init__(self, size=10):
        self.size = size
        self.hash_table = [None] * size

    def hash_function(self, value):
        return value % self.size

    def display(self):
        for i in range(self.size):
            temp = self.hash_table[i]
            print(f"Slot {i}:", end="")
            while temp:
                print(f" -> {temp.value}", end="")
                temp = temp.next
            print()

    def search_element(self, value):
        hash_val = self.hash_function(value)
        temp = self.hash_table[hash_val]
        while temp:
            if temp.value == value:
                print(f"\nElement found at slot {hash_val}")
                return
            temp = temp.next
        print("\nElement not found")

    def delete_element(self, value):
        hash_val = self.hash_function(value)
        temp = self.hash_table[hash_val]
        prev = None
        while temp:
            if temp.value == value:
                if prev:
                    prev.next = temp.next
                else:
                    self.hash_table[hash_val] = temp.next
                print("\nElement deleted")
                return
            prev = temp
            temp = temp.next
        print("\nElement not found")

    def insert_element(self, value):
        hash_val = self.hash_function(value)
        node = Node(value)
        if not self.hash_table[hash_val]:
            self.hash_table[hash_val] = node
        else:
            temp = self.hash_table[hash_val]
            while temp.next:
                temp = temp.next
            temp.next = node


if __name__ == "__main__":
    h = HashTable()

    while True:
        print("\nTelephone Book Menu:")
        print("1. Insert")
        print("2. Display")
        print("3. Search")
        print("4. Delete")
        print("5. Exit")
        
        try:
            choice = int(input("\nEnter your choice (1-5): "))
            if choice == 1:
                data = int(input("Enter phone number to be inserted: "))
                h.insert_element(data)
            elif choice == 2:
                h.display()
            elif choice == 3:
                search = int(input("Enter the phone number to be searched: "))
                h.search_element(search)
            elif choice == 4:
                del_val = int(input("Enter the phone number to be deleted: "))
                h.delete_element(del_val)
            elif choice == 5:
                print("Exiting...")
                break
            else:
                print("Invalid choice, please try again.")
        except ValueError:
            print("Invalid input, please enter a valid choice or number.")
