#include <iostream>

class List {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
        Node(int val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* first = nullptr;
    Node* last = nullptr;
    unsigned int num_elems = 0;

public:
    List() : first(nullptr), last(nullptr), num_elems(0) {}

    ~List() {
        while (first != nullptr) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void push_back(const int& value) {
        Node* newNode = new Node(value);
        if (last == nullptr) { // Lista vacía
            first = last = newNode;
        }
        else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
        num_elems++;
    }

    void push_front(const int& value) {
        Node* newNode = new Node(value);
        if (first == nullptr) { // Lista vacía
            first = last = newNode;
        }
        else {
            newNode->next = first;
            first->prev = newNode;
            first = newNode;
        }
        num_elems++;
    }

    void insert(unsigned int position, const int& value) {
        if (position == 0) { // Insertar al inicio
            push_front(value);
        }
        else if (position >= num_elems) { // Rellenar con 'N' y luego insertar
            for (unsigned int i = num_elems; i < position; ++i) {
                push_back(0); // Rellenar con 'NULL'
            }
            push_back(value); // Insertar el valor en la última posición
        }
        else { // Insertar en el medio
            Node* current = first;
            for (unsigned int index = 0; index < position; ++index) {
                current = current->next;
            }
            Node* newNode = new Node(value);
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev != nullptr) {
                current->prev->next = newNode;
            }
            current->prev = newNode;
            num_elems++;
        }
    }

    void erase(unsigned int position) {
        if (position >= num_elems) {
            std::cout << "Invalid position to erase.\n";
            return;
        }

        Node* current = first;

        if (position == 0) { // Eliminar el primer elemento
            first = first->next;
            if (first != nullptr) {
                first->prev = nullptr;
            }
            else { // Lista vacía
                last = nullptr;
            }
            delete current;
        }
        else if (position == num_elems - 1) { // Eliminar el último elemento
            current = last;
            last = last->prev;
            if (last != nullptr) {
                last->next = nullptr;
            }
            else { // Lista vacía
                first = nullptr;
            }
            delete current;
        }
        else { // Eliminar un elemento en el medio
            for (unsigned int index = 0; index < position; ++index) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }

        num_elems--;
    }

    void print() const {
        Node* current = first;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    List myList;
    myList.push_back(1);
    myList.print();
    myList.insert(3, 7);
    myList.print();
    myList.insert(2, 2);
    myList.print();
    myList.insert(1, 3);
    myList.print();
    myList.insert(0, 4);
    myList.print();
    myList.push_front(100);
    myList.print();
    myList.erase(2); // Eliminar el elemento en la posición 2
    myList.print();

    return 0;
}
