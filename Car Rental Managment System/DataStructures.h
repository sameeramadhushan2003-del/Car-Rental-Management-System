#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "Models.h"
#include <iostream>
using namespace std;


// linked list for cars

class LinkedListCar {
public:
    struct Node {
        Car data;
        Node* next;

        Node(Car d) {
            data = d;
            next = nullptr;
        }
    };

    Node* head;
    int size;

    LinkedListCar() {
        head = nullptr;
        size = 0;
    }

    void insert(Car data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            size++;
            return;
        }

        Node* temp = head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
        size++;
    }

    void add(Car data) { insert(data); }

    Car& get(int index) {
        Node* cur = head;
        for (int i = 0; i < index; i++) cur = cur->next;
        return cur->data;
    }

    void removeAt(int index) {
        if (index == 0) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            size--;
            return;
        }
        Node* cur = head;
        for (int i = 0; i < index - 1; i++) cur = cur->next;
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        size--;
    }

    ~LinkedListCar() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};


// linked list for customers

class LinkedListCustomer {
public:
    struct Node {
        Customer data;
        Node* next;

        Node(Customer d) {
            data = d;
            next = nullptr;
        }
    };

    Node* head;
    int size;

    LinkedListCustomer() {
        head = nullptr;
        size = 0;
    }

    void insert(Customer data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            size++;
            return;
        }

        Node* temp = head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
        size++;
    }

    void add(Customer data) { insert(data); }

    Customer& get(int index) {
        Node* cur = head;
        for (int i = 0; i < index; i++) cur = cur->next;
        return cur->data;
    }

    void removeAt(int index) {
        if (index == 0) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            size--;
            return;
        }
        Node* cur = head;
        for (int i = 0; i < index - 1; i++) cur = cur->next;
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        size--;
    }

    ~LinkedListCustomer() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};


// linked list for rentals

class LinkedListRental {
public:
    struct Node {
        Rental data;
        Node* next;

        Node(Rental d) {
            data = d;
            next = nullptr;
        }
    };

    Node* head;
    int size;

    LinkedListRental() {
        head = nullptr;
        size = 0;
    }

    void insert(Rental data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            size++;
            return;
        }

        Node* temp = head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
        size++;
    }

    void add(Rental data) { insert(data); }

    Rental& get(int index) {
        Node* cur = head;
        for (int i = 0; i < index; i++) cur = cur->next;
        return cur->data;
    }

    void removeAt(int index) {
        if (index == 0) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            size--;
            return;
        }
        Node* cur = head;
        for (int i = 0; i < index - 1; i++) cur = cur->next;
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        size--;
    }

    ~LinkedListRental() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};


// Queue for waiting list

class Queue {
    struct Node {
        WaitEntry data;
        Node* next;
        Node(WaitEntry val) : data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;

public:
    int size;
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(WaitEntry val) {
        Node* n = new Node(val);
        if (!rear) { front = rear = n; }
        else { rear->next = n; rear = n; }
        size++;
    }

    WaitEntry dequeue() {
        Node* tmp = front;
        WaitEntry val = tmp->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete tmp;
        size--;
        return val;
    }

    void display() {
        Node* cur = front;
        int i = 1;
        while (cur) {
            cout << "  " << i++ << ". " << cur->data.customerName
                 << " (waiting for: " << cur->data.Brand << " " << cur->data.model << ")\n";
            cur = cur->next;
        }
        if (size == 0) cout << "  Waiting list is empty.\n";
    }

    bool isEmpty() { return size == 0; }

    ~Queue() {
        while (front) {
            Node* tmp = front;
            front = front->next;
            delete tmp;
        }
    }
};

// Stack for history log

class Stack {
    struct Node {
        string data;
        Node* next;
        Node(string val) : data(val), next(nullptr) {}
    };
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(string val) {
        Node* n = new Node(val);
        n->next = top;
        top = n;
    }

    void displayTop5() {
        Node* cur = top;
        int i = 0;
        while (cur && i < 5) {
            cout << "  - " << cur->data << "\n";
            cur = cur->next;
            i++;
        }
        if (!top) cout << "  No history yet.\n";
    }

    ~Stack() {
        while (top) {
            Node* tmp = top;
            top = top->next;
            delete tmp;
        }
    }
};

#endif
