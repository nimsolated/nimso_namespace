#pragma once
#include <iostream>

namespace Nimso {
    template <typename Variant>
    struct Node {
        Node<Variant>* m_next = nullptr;
        Variant m_data;

        Node() = default;
        Node(Variant data) : m_data(data) {}
        template <typename... Args>
        Node(Args&&... args) : m_data(std::forward<Args>(args)...) {}
    };

    template <typename Variant>
    struct DoublyNode {
        DoublyNode<Variant>* m_next = nullptr;
        DoublyNode<Variant>* m_prev = nullptr;
        Variant m_data;

        DoublyNode() = default;
        DoublyNode(Variant data) : m_data(data) {}
        template <typename... Args>
        DoublyNode(Args&&... args) : m_data(std::forward<Args>(args)...) {}
    };

    template <typename T>
    class Queue {
    private:
        size_t m_size;
        Node<T>* m_front;
        Node<T>* m_back;
    public:
        Queue() : m_size(0), m_front(nullptr), m_back(nullptr) {};
        ~Queue() {
            if (m_size == 0) {
                return;
            }

            Node<T>* curr = m_front;
            while (curr->m_next) {
                curr = curr->m_next;
                m_front->m_next = nullptr;
                delete m_front;
                m_front = curr;
            }
            delete curr;
        }
        bool isEmpty() const {
            return m_size == 0;
        }
        size_t size() const {
            return m_size;
        }
        T front() const {
            return m_front->m_data;
        }
        T back() const {
            return m_back->m_data;
        }
        void push(T& val) {
            Node<T>* newNode = new Node<T>(val);

            if (m_size == 0) {
                m_front = newNode;
                m_back = newNode;
            }
            else {
                m_back->m_next = newNode;
                m_back = newNode;
            }

            m_size++;
        }
        template <typename... Args>
        void emplace(Args&&... args) {
            Node<T>* newNode = new Node<T>(std::forward<Args>(args)...);

            if (m_size == 0) {
                m_front = newNode;
                m_back = newNode;
            }
            else {
                m_back->m_next = newNode;
                m_back = newNode;
            }

            m_size++;
        }
        T pop() {
            if (m_size == 0) {
                throw std::runtime_error("Nothing to pop from the Queue!");
            }

            T r = m_front->m_data;

            if (m_front == m_back) {
                delete m_front;
            }
            else {
                Node<T>* temp = m_front;
                m_front = m_front->m_next;
                temp->m_next = nullptr;
                delete temp;
            }
            m_size--;

            return r;
        }
        void swap(Queue<T>& other) noexcept {
            if (this != &other && (this->m_size > 0 || other.m_size > 0)) {
                Node<T>* tempnode = this->m_front;
                this->m_front = other.m_front;
                other.m_front = tempnode;
                tempnode = this->m_back;
                this->m_back = other.m_back;
                other.m_back = tempnode;
                size_t tempsizet = this->m_size;
                this->m_size = other.m_size;
                other.m_size = tempsizet;
            }
        }
        friend std::ostream& operator<<(std::ostream& os, Queue<T>& q) {
            os << "F [";
            if (q.m_front) {
                Node<T>* curr = q.m_front;
                do {
                    os << curr->m_data;
                    if (curr->m_next) {
                        os << ", ";
                        curr = curr->m_next;
                    }
                    else {
                        curr = nullptr;
                    }
                } while (curr);
            }
            os << "] B";
            return os;
        }
    };
    
    // TODO: a delete function to delete a node that has matching data with the target data
    // TODO: a find function to check if the target data exists in the list
    template <typename T>
    class LinkedList {
    private:
        size_t m_size;
        DoublyNode<T>* m_head;
        DoublyNode<T>* m_tail;
    public:
        LinkedList() : m_size(0), m_head(nullptr), m_tail(nullptr) {};
        ~LinkedList() {
            if (m_size == 0) {
                return;
            }

            DoublyNode<T>* curr = m_head;
            while (curr->m_next) {
                curr = curr->m_next;
                m_head->m_next = nullptr;
                curr->m_prev = nullptr;
                delete m_head;
                m_head = curr;
            }
            delete curr;
        }
        bool isEmpty() const {
            return m_size == 0;
        }
        size_t size() const {
            return m_size;
        }
        T head() const {
            return m_head->m_data;
        }
        T tail() const {
            return m_tail->m_data;
        }
        void push(T& value) {
            DoublyNode<T>* newNode = new DoublyNode<T>(value);

            if (!m_head) {
                m_head = newNode;
                m_tail = newNode;
            }
            else {
                newNode->m_next = m_head;
                m_head = newNode;
            }

            m_size++;
        }
        void pushBack(T& value) {
            DoublyNode<T>* newNode = new DoublyNode<T>(value);

            if (!m_head) {
                m_head = newNode;
                m_tail = newNode;
            }
            else {
                m_tail->m_next = newNode;
                newNode->m_prev = m_tail;
                m_tail = newNode;
            }

            m_size++;
        }
        template <typename... Args>
        void emplace(Args&&... args) {
            DoublyNode<T>* newNode = new DoublyNode<T>(std::forward<Args>(args)...);

            if (!m_head) {
                m_head = newNode;
                m_tail = newNode;
            }
            else {
                newNode->m_next = m_head;
                m_head = newNode;
            }

            m_size++;
        }
        template <typename... Args>
        void emplaceBack(Args&&... args) {
            DoublyNode<T>* newNode = new DoublyNode<T>(std::forward<Args>(args)...);

            if (!m_head) {
                m_head = newNode;
                m_tail = newNode;
            }
            else {
                m_tail->m_next = newNode;
                newNode->m_prev = m_tail;
                m_tail = newNode;
            }

            m_size++;
        }
        T pop() {
            if (m_size == 0) {
                throw std::runtime_error("Nothing to pop from the Linked List!");
            }

            T r = m_head->m_data;

            if (m_head == m_tail) {
                delete m_head;
            }
            else {
                DoublyNode<T>* temp = m_head;
                m_head = m_head->m_next;
                temp->m_next = nullptr;
                delete temp;
            }

            m_size--;
            return r;
        }
        T popBack() {
            if (m_size == 0) {
                throw std::runtime_error("Nothing to pop from the Linked List!");
            }

            T r = m_tail->m_data;

            if (m_tail == m_head) {
                delete m_tail;
            }
            else {
                DoublyNode<T>* temp = m_tail;
                m_tail = m_tail->m_prev;
                m_tail->m_next = nullptr;
                temp->m_prev = nullptr;
                delete temp;
            }

            m_size--;
            return r;
        }
        void swap(LinkedList<T>& other) {
            if (this != &other && (this->m_size > 0 || other.m_size > 0)) {
                DoublyNode<T>* tempnode = this->m_head;
                this->m_head = other.m_head;
                other.m_head = tempnode;
                tempnode = this->m_tail;
                this->m_tail = other.m_tail;
                other.m_tail = tempnode;
                size_t tempsizet = this->m_size;
                this->m_size = other.m_size;
                other.m_size = tempsizet;
            }
        }
        friend std::ostream& operator<<(std::ostream& os, LinkedList<T>& LL) {
            os << '[';
            if (LL.m_head) {
                DoublyNode<T>* curr = LL.m_head;
                do {
                    os << curr->m_data;
                    if (curr->m_next) {
                        os << ", ";
                        curr = curr->m_next;
                    }
                    else {
                        curr = nullptr;
                    }
                } while (curr);
            }
            os << ']';
            return os;
        }
    };

    // TODO: implement Plate class
	template <typename T>
	class Plate {
        // TODO: implement Plate class
	};

    // TODO: implement Bowl class (inherits from Plate class)
	template <typename T>
	class Bowl : public Plate<T> {
        // TODO: implement Bowl class (inherits from Plate class)
	};
}