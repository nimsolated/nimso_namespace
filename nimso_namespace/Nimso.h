#pragma once
#include <iostream>

namespace Nimso {
    enum s_InsertionRules { INSERT_BEFORE = 0, INSERT_AFTER };

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
    
    template <typename T>
    class DoublyLinkedList {
    private:
        size_t m_size;
        DoublyNode<T>* m_head;
        DoublyNode<T>* m_tail;
    public:
        DoublyLinkedList() : m_size(0), m_head(nullptr), m_tail(nullptr) {};
        ~DoublyLinkedList() {
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
                m_head->m_prev = newNode;
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
                m_head->m_prev = newNode;
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
        bool find(const T& targetData) {
            if (m_size == 0) {
                return false;
            }

            if (m_head->m_data == targetData) {
                return true;
            }
            else if (m_tail->m_data == targetData) {
                return true;
            }

            DoublyNode<T>* curr = m_head;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                if (curr->m_data == targetData) {
                    return true;
                }
            }

            return false;
        }
        long long int findPos(const T& targetData) {
            if (m_size == 0) {
                return -1;
            }

            if (m_head->m_data == targetData) {
                return 0;
            }
            else if (m_tail->m_data == targetData) {
                return m_size - 1;
            }

            DoublyNode<T>* curr = m_head;
            size_t pos = 0;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                pos++;
                if (curr->m_data == targetData) {
                    return pos;
                }
            }

            return -1;
        }
        bool findInsert(const T& targetData, const T& dataToInsert, s_InsertionRules rule = INSERT_AFTER) {
            if (m_size == 0) {
                return false;
            }

            DoublyNode<T>* newNode = new DoublyNode<T>(dataToInsert);

            if (m_head->m_data == targetData) {
                if (rule == INSERT_AFTER) {
                    newNode->m_next = m_head->m_next;
                    m_head->m_next->m_prev = newNode;
                    m_head->m_next = newNode;
                    newNode->m_prev = m_head;
                }
                else if (rule == INSERT_BEFORE) {
                    newNode->m_next = m_head;
                    m_head->m_prev = newNode;
                    m_head = newNode;
                }
                m_size++;
                return true;
            }
            else if (m_tail->m_data == targetData) {
                if (rule == INSERT_AFTER) {
                    newNode->m_prev = m_tail;
                    m_tail->m_next = newNode;
                    m_tail = newNode;
                }
                else if (rule == INSERT_BEFORE) {
                    newNode->m_next = m_tail;
                    newNode->m_prev = m_tail->m_prev;
                    m_tail->m_prev->m_next = newNode;
                    m_tail->m_prev = newNode;
                }
                m_size++;
                return true;
            }

            DoublyNode<T>* curr = m_head;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                if (curr->m_data == targetData) {
                    if (rule == INSERT_AFTER) {
                        newNode->m_prev = curr;
                        newNode->m_next = curr->m_next;
                        curr->m_next->m_prev = newNode;
                        curr->m_next = newNode;
                    }
                    else if (rule == INSERT_BEFORE) {
                        newNode->m_next = curr;
                        newNode->m_prev = curr->m_prev;
                        curr->m_prev->m_next = newNode;
                        curr->m_prev = newNode;
                    }
                    m_size++;
                    return true;
                }
            }

            if (!newNode->m_prev && !newNode->m_next) {
                delete newNode;
            }

            return false;
        }
        bool findDelete(const T& targetData) {
            if (m_size == 0) {
                return false;
            }

            if (m_head->m_data == targetData) {
                if (m_head == m_tail) {
                    delete m_head;
                }
                else {
                    DoublyNode<T>* tempnode = m_head;
                    m_head->m_next->m_prev = nullptr;
                    m_head = m_head->m_next;
                    tempnode->m_next = nullptr;
                    delete tempnode;
                }
                m_size--;
                return true;
            }
            else if (m_tail->m_data == targetData) {
                if (m_tail == m_head) {
                    delete m_tail;
                }
                else {
                    DoublyNode<T>* tempnode = m_tail;
                    m_tail->m_prev->m_next = nullptr;
                    m_tail = m_tail->m_prev;
                    tempnode->m_prev = nullptr;
                    delete tempnode;
                }
                m_size--;
                return true;
            }

            DoublyNode<T>* curr = m_head;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                if (curr->m_data == targetData) {
                    curr->m_prev->m_next;
                    curr->m_next;
                    curr->m_prev->m_next = curr->m_next;
                    curr->m_next->m_prev = curr->m_prev;
                    curr->m_next = nullptr;
                    curr->m_prev = nullptr;
                    delete curr;
                    m_size--;
                    return true;
                }
            }

            return false;
        }
        bool findReplace(const T& targetData, const T& replacementData) {
            if (m_size == 0) {
                return false;
            }

            if (m_head->m_data == targetData) {
                m_head->m_data = replacementData;
                return true;
            }
            else if (m_tail->m_data == targetData) {
                m_tail->m_data = replacementData;
                return true;
            }

            DoublyNode<T>* curr = m_head;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                if (curr->m_data == targetData) {
                    curr->m_data = replacementData;
                    return true;
                }
            }

            return false;
        }
        void swap(DoublyLinkedList<T>& other) {
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
        friend std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T>& LL) {
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