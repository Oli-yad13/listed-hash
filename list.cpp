#include <iostream>
#include <cassert> // For using assert
using namespace std;

// Node structure for Singly Linked List
struct Node {
    int data; // Holds the value of the node
    Node* next; // Pointer to the next node in the list
    Node(int val) : data(val), next(nullptr) {} // Constructor to create a new node
};

// Singly Linked List Structure with Head and Tail Pointers
struct SinglyLinkedList {
    Node* head; // Points to the first node in the list
    Node* tail; // Points to the last node in the list

    SinglyLinkedList() : head(nullptr), tail(nullptr) {} // Constructor to initialize empty list

    // Unsorted List Operations
    void insertAtHead(int val); // Insert a new node at the beginning
    void insertAtEnd(int val); // Insert a new node at the end
    void deleteFromHead(); // Delete the node from the beginning
    void deleteFromEnd(); // Delete the node from the end
    void deleteByKey(int key); // Delete the node with a specific value
    void printList(); // Print the whole list
    bool search(int key); // Search for a node with a specific value

    // Sorted List Operations
    void insertSorted(int val); // Insert a node in a sorted position
};

// Insert a new node at the beginning of the list
void SinglyLinkedList::insertAtHead(int val) {
    Node* newNode = new Node(val); // Create a new node
    if (!head) { // If the list is empty
        head = tail = newNode; // Both head and tail point to the new node
    } else {
        newNode->next = head; // Make the new node point to the current head
        head = newNode; // Update head to the new node
    }
}

// Insert a new node at the end of the list
void SinglyLinkedList::insertAtEnd(int val) {
    Node* newNode = new Node(val); // Create a new node
    if (!tail) { // If the list is empty
        head = tail = newNode; // Both head and tail point to the new node
    } else {
        tail->next = newNode; // Make the current tail point to the new node
        tail = newNode; // Update tail to the new node
    }
}

// Delete the node from the beginning of the list
void SinglyLinkedList::deleteFromHead() {
    if (!head) return; // If the list is empty, do nothing
    Node* temp = head; // Store the current head in a temp variable
    head = head->next; // Move head to the next node
    if (!head) tail = nullptr; // If the list becomes empty, update tail to nullptr
    delete temp; // Delete the old head node
}

// Delete the node from the end of the list
void SinglyLinkedList::deleteFromEnd() {
    if (!head) return; // If the list is empty, do nothing
    if (head == tail) { // If the list has only one node
        delete head; // Delete the only node
        head = tail = nullptr; // Set both head and tail to nullptr
        return;
    }
    Node* temp = head;
    while (temp->next != tail) { // Traverse to the second-to-last node
        temp = temp->next;
    }
    delete tail; // Delete the last node
    tail = temp; // Update tail to the second-to-last node
    tail->next = nullptr; // Set the new tail's next pointer to nullptr
}

// Delete a node by its value (key)
void SinglyLinkedList::deleteByKey(int key) {
    if (!head) return; // If the list is empty, do nothing

    if (head->data == key) { // If the node to delete is the head
        deleteFromHead(); // Call deleteFromHead to handle deletion
        return;
    }

    Node* prev = head;
    Node* curr = head->next;
    while (curr && curr->data != key) { // Traverse the list to find the node with the key
        prev = curr;
        curr = curr->next;
    }

    if (curr) { // If the node is found
        prev->next = curr->next; // Skip over the node to delete it
        if (curr == tail) { // If the node is the tail
            tail = prev; // Update tail to the previous node
        }
        delete curr; // Delete the node
    } else {
        cout << "Key not found in the list." << endl; // If the node isn't found
    }
}

// Print all the elements in the list
void SinglyLinkedList::printList() {
    Node* temp = head;
    while (temp) { // Traverse the list and print each node
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n"; // End of the list
}

// Search for a node by its value (key)
bool SinglyLinkedList::search(int key) {
    Node* temp = head;
    while (temp) { // Traverse the list
        if (temp->data == key) return true; // If the key is found
        temp = temp->next;
    }
    return false; // If the key isn't found
}

// Insert a node in a sorted list
void SinglyLinkedList::insertSorted(int val) {
    Node* newNode = new Node(val); // Create a new node
    if (!head || val < head->data) { // If the list is empty or the new value is smaller than the head's value
        newNode->next = head; // Insert the new node at the beginning
        head = newNode;
        if (!tail) tail = newNode; // If the list was empty, the new node is also the tail
        return;
    }
    Node* temp = head;
    while (temp->next && temp->next->data < val) { // Traverse to find the right position
        temp = temp->next;
    }
    newNode->next = temp->next; // Insert the new node in the correct position
    temp->next = newNode;
    if (!newNode->next) tail = newNode; // If it's inserted at the end, update the tail
}

// Doubly Linked List Implementation
struct DNode {
    int data;
    DNode* next;
    DNode* prev;
    DNode(int val) : data(val), next(nullptr), prev(nullptr) {} // Constructor for a doubly linked node
};

struct DoublyLinkedList {
    DNode* head; // Points to the first node
    DNode* tail; // Points to the last node

    DoublyLinkedList() : head(nullptr), tail(nullptr) {} // Constructor to initialize an empty list

    void insertAtPosition(int pos, int val); // Insert at a specific position
    void deleteByKey(int key); // Delete a node by key
    void deleteAtPosition(int pos); // Delete at a specific position
    void printList(); // Print the list
};

// Insert a node at a specific position in the doubly linked list
void DoublyLinkedList::insertAtPosition(int pos, int val) {
    DNode* newNode = new DNode(val);
    if (pos == 0) { // If inserting at the head
        if (!head) {
            head = tail = newNode; // If the list is empty
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode; // Update head to the new node
        }
        return;
    }

    DNode* temp = head;
    for (int i = 0; temp && i < pos - 1; i++) {
        temp = temp->next; // Traverse to the position before where the new node should be
    }

    if (!temp) return; // If position is invalid

    if (!temp->next) { // If inserting at the end
        temp->next = newNode;
        newNode->prev = temp;
        tail = newNode; // Update tail
    } else {
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
}

// Delete a node by key in a doubly linked list
void DoublyLinkedList::deleteByKey(int key) {
    if (!head) return; // If the list is empty, do nothing

    if (head->data == key) { // If the node to delete is the head
        DNode* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr; // If the list is empty after deletion, update tail
        delete temp;
        return;
    }

    DNode* temp = head;
    while (temp && temp->data != key) { // Traverse the list to find the node
        temp = temp->next;
    }

    if (temp) {
        if (temp == tail) {
            tail = temp->prev; // If deleting the tail, update tail
            tail->next = nullptr;
        } else {
            temp->prev->next = temp->next; // Update the previous node's next pointer
            if (temp->next) temp->next->prev = temp->prev; // Update the next node's prev pointer
        }
        delete temp;
    } else {
        cout << "Key not found in the list." << endl;
    }
}

// Delete a node at a specific position in the doubly linked list
void DoublyLinkedList::deleteAtPosition(int pos) {
    if (!head) return; // If the list is empty, do nothing

    DNode* temp = head;
    if (pos == 0) { // If deleting the head
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr; // If the list becomes empty, update tail
        delete temp;
        return;
    }

    for (int i = 0; temp && i < pos; i++) {
        temp = temp->next; // Traverse to the node at the given position
    }

    if (!temp) return; // If the position is invalid

    if (temp == tail) {
        tail = temp->prev;
        tail->next = nullptr; // Update tail
    } else {
        temp->prev->next = temp->next; // Update previous node's next pointer
        if (temp->next) temp->next->prev = temp->prev; // Update next node's prev pointer
    }
    delete temp;
}

// Print the doubly linked list
void DoublyLinkedList::printList() {
    DNode* temp = head;
    while (temp) {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    SinglyLinkedList sl;
    DoublyLinkedList dl;

    int choice, val, pos;

    while (true) {
        // Singly Linked List Menu
        cout << "Singly Linked List Operations:\n";
        cout << "1. Insert at Head\n";
        cout << "2. Insert at End\n";
        cout << "3. Delete from Head\n";
        cout << "4. Delete from End\n";
        cout << "5. Delete by Key\n";
        cout << "6. Print List\n";
        cout << "7. Search by Key\n";
        cout << "8. Insert in Sorted List\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at head: ";
                cin >> val;
                sl.insertAtHead(val);
                break;
            case 2:
                cout << "Enter value to insert at end: ";
                cin >> val;
                sl.insertAtEnd(val);
                break;
            case 3:
                sl.deleteFromHead();
                break;
            case 4:
                sl.deleteFromEnd();
                break;
            case 5:
                cout << "Enter value to delete by key: ";
                cin >> val;
                sl.deleteByKey(val);
                break;
            case 6:
                sl.printList();
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> val;
                if (sl.search(val)) cout << "Found\n";
                else cout << "Not Found\n";
                break;
            case 8:
                cout << "Enter value to insert in sorted list: ";
                cin >> val;
                sl.insertSorted(val);
                break;
            default:
                cout << "Invalid choice\n";
                break;
        }

        // Doubly Linked List Menu
        cout << "\nDoubly Linked List Operations:\n";
        cout << "1. Insert at Position\n";
        cout << "2. Delete by Key\n";
        cout << "3. Delete at Position\n";
        cout << "4. Print List\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter position and value to insert: ";
                cin >> pos >> val;
                dl.insertAtPosition(pos, val);
                break;
            case 2:
                cout << "Enter value to delete by key: ";
                cin >> val;
                dl.deleteByKey(val);
                break;
            case 3:
                cout << "Enter position to delete: ";
                cin >> pos;
                dl.deleteAtPosition(pos);
                break;
            case 4:
                dl.printList();
                break;
            default:
                cout << "Invalid choice\n";
                break;
        }
    }

    return 0;
}