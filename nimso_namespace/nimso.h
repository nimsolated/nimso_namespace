#pragma once
#include <iostream>
#include <Windows.h>
#include <unordered_map>

namespace nimso {
    enum e_InsertionRules { INSERT_BEFORE = 0, INSERT_AFTER = 1 };

    enum e_ErrorState { ERROR_FAIL = -1, ERROR_PASS = 0 };
    
    bool isKeyPressed(int key) {
        return (GetAsyncKeyState(key) & 0x8000) != 0;
    }

    struct Vector2 {
        int x;
        int y;

        Vector2() : x(0), y(0) {}
        Vector2(const int& _x, const int& _y) : x(_x), y(_y) {}

        bool operator==(const Vector2& other) {
            return (this->x == other.x && this->y == other.y);
        }
        bool operator>(const Vector2& other) {
            return (this->x > other.x || this->y > other.y);
        }
        bool operator<(const Vector2& other) {
            return (this->x < other.x || this->y < other.y);
        }
        friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
            os << '(' << vec.x << ", " << vec.y << ')';
            return os;
        }
    };

    class FreeRoam {
    private:
        Vector2 position;
        Vector2 border;
        char playerChar;
        bool done;

        void drawCurrState() const {
            system("cls");

            for (int i = 0; i < position.y; i++) {
                std::cout << std::endl;
            }
            for (int i = 0; i < position.x; i++) {
                std::cout << ' ';
            }

            std::cout << playerChar << std::endl;
        }
        void checkForKey() {
            if ((isKeyPressed(VK_UP) || isKeyPressed(87)) && position.y > 0) {
                position.y--;
                drawCurrState();
            }
            else if ((isKeyPressed(VK_DOWN) || isKeyPressed(83)) && position.y < border.y) {
                position.y++;
                drawCurrState();
            }
            if ((isKeyPressed(VK_LEFT) || isKeyPressed(65)) && position.x > 0) {
                position.x--;
                drawCurrState();
            }
            else if ((isKeyPressed(VK_RIGHT) || isKeyPressed(68)) && position.x < border.x) {
                position.x++;
                drawCurrState();
            }
            else if (isKeyPressed(113)) {
                done = true;
            }
            else if (isKeyPressed(81)) {
                done = true;
            }
        }
    public:
        FreeRoam(const char& _playerCharacter = static_cast<char>(254), const Vector2& _startPos = Vector2(), const Vector2& _initialBorder = Vector2(50, 25))
            : position(_startPos), border(_initialBorder), playerChar(_playerCharacter), done(false) {}

        void setPos(const Vector2& newPos) {
            position = newPos;
        }
        void setBorder(const Vector2& newBorder) {
            border = newBorder;
        }
        void setPlayerChar(const char& newPlayerChar) {
            playerChar = newPlayerChar;
        }
        Vector2 getPos() const {
            return position;
        }
        Vector2 getBorder() const {
            return border;
        }
        char getPlayerChar() const {
            return playerChar;
        }

        int run() {
            if (position > border) {
                std::cout << "Starting position must *not* be outside of the border." << std::endl;
                return -1;
            }

            system("cls");
            drawCurrState();
            while (!done) {
                checkForKey();
                Sleep(50);
            }
            system("cls");
            std::cout << "FreeRoam session ended!\n";
            return 0;
        }
    };

    template <typename Variant>
    void display(const Variant& item) {
        try {
            std::cout << item << std::endl;
        }
        catch (...) {
            std::cout << "Unknown error in display(item) function. Does the item parameter have an operator<< overload?" << std::endl;
            return;
        }
    }

    template <typename Variant>
    void display(Variant&& item) {
        try {
            std::cout << item << std::endl;
        }
        catch (...) {
            std::cout << "Unknown error in display(item) function. Does the item parameter have an operator<< overload?" << std::endl;
            return;
        }
    }

    template <typename T>
    long long seqSearch(const T arr[], const T& target, const size_t& arr_size) {
        for (size_t i = 0; i < arr_size; i++) {
            if (arr[i] == target) {
                return i;
            }
        }

        return -1;
    }

    template <typename T>
    long long binarySearch(const T arr[], size_t low, size_t high, const T& target) {
        while (high >= low) {
            size_t mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid;
            }
            else if (arr[mid] < target) {
                low = mid + 1;
            }
            else if (arr[mid] > target) {
                high = mid - 1;
            }
        }

        return -1;
    }

    template <typename T>
    long long binarySearchRecursive(const T arr[], size_t low, size_t high, const T& target) {
        if (low > high) {
            return -1;
        }

        size_t mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            return nimso::binarySearchRecursive(arr, mid + 1, high, target);
        }
        else {
            return nimso::binarySearchRecursive(arr, low, mid - 1, target);
        }
    }

    class TowerOfHanoi {
    private:
        size_t m_numMoves;
    public:
        TowerOfHanoi() : m_numMoves(0) {};
        TowerOfHanoi(const TowerOfHanoi& other) : TowerOfHanoi() {
            try {
                if (this == &other) {
                    throw std::runtime_error("Self Referense in TowerOfHanoi's copy constructor!");
                }
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                return;
            }

            this->m_numMoves = other.m_numMoves;
        }
        ~TowerOfHanoi() = default;
        
        void resetNumMoves() {
            m_numMoves = 0;
        }
        size_t getNumMoves() const {
            return m_numMoves;
        }
        void start(size_t n, char src, char dest, char aux) {
            m_numMoves++;

            if (n == 1) {
                std::cout << "Move disk 1 from " << src
                    << " to " << dest << std::endl;
                return;
            }

            start(n - 1, src, aux, dest);
            std::cout << "Move disk " << n << " from " << src
                << " to " << dest << std::endl;
            start(n - 1, aux, dest, src);
        }
    };

    template <typename Variant>
    struct Node {
        Node<Variant>* m_next = nullptr;
        Variant m_data;

        Node() = default;
        Node(const Variant& data, Node<Variant>* next = nullptr) : m_data(data), m_next(next) {}
        Node(Variant&& data, Node<Variant>* next = nullptr) : m_data(data), m_next(next) {}
        template <typename... Args>
        Node(Args&&... args) : m_data(std::forward<Args>(args)...) {}
    };

    template <typename Variant>
    struct DoublyNode {
        DoublyNode<Variant>* m_next = nullptr;
        DoublyNode<Variant>* m_prev = nullptr;
        Variant m_data;

        DoublyNode() = default;
        DoublyNode(const Variant& data, DoublyNode<Variant>* prev = nullptr, DoublyNode<Variant>* next = nullptr)
            : m_data(data), m_prev(prev), m_next(next) {}
        DoublyNode(Variant&& data, DoublyNode<Variant>* prev = nullptr, DoublyNode<Variant>* next = nullptr)
            : m_data(data), m_prev(prev), m_next(next) {}
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
        Queue(const Queue<T>& other) : Queue() {
            try {
                if (this == &other) {
                    throw std::runtime_error("Self Referense in Queue's copy constructor!");
                }
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                return;
            }

            if (other.m_size == 0) {
                return;
            }

            Node<T>* curr = other.m_front;
            this->push(curr->m_data);
            while (curr->m_next) {
                curr = curr->m_next;
                this->push(curr->m_data);
            }
        }
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
        T& front() const {
            return m_front->m_data;
        }
        T& back() const {
            return m_back->m_data;
        }
        void push(const T& val) {
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
        e_ErrorState swap(Queue<T>& other) noexcept {
            try {
                if (this == &other) {
                    throw std::runtime_error("A Queue can't self-swap!");
                }
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                return ERROR_FAIL;
            }

            if (this->m_size > 0 || other.m_size > 0) {
                Node<T>* tempnode = this->m_front;
                this->m_front = other.m_front;
                other.m_front = tempnode;
                tempnode = this->m_back;
                this->m_back = other.m_back;
                other.m_back = tempnode;
                size_t tempsizet = this->m_size;
                this->m_size = other.m_size;
                other.m_size = tempsizet;
                return ERROR_PASS;
            }

            return ERROR_FAIL;
        }
        friend std::ostream& operator<<(std::ostream& os, Queue<T>& q) {
            os << "F [";
            if (q.m_size != 0) {
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
    class Stack {
    private:
        size_t m_size;
        Node<T>* m_top;
    public:
        Stack() : m_size(0), m_top(nullptr) {};
        ~Stack() {
            if (m_size == 0) {
                return;
            }

            Node<T>* curr = m_top;
            while (curr->m_next) {
                curr = curr->m_next;
                m_top->m_next = nullptr;
                delete m_top;
                m_top = curr;
            }
            delete curr;
        }
        bool isEmpty() const {
            return m_size == 0;
        }
        size_t size() const {
            return m_size;
        }
        T& top() const {
            return m_top->m_data;
        }
        void push(const T& value) {
            Node<T>* newNode = new Node<T>(value);

            if (m_size == 0) {
                m_top = newNode;
            }
            else {
                newNode->m_next = m_top;
                m_top = newNode;
            }

            m_size++;
        }
        template <typename... Args>
        void emplace(Args&&... args) {
            Node<T>* newNode = new Node<T>(std::forward<Args>(args)...);

            if (m_size == 0) {
                m_top = newNode;
            }
            else {
                newNode->m_next = m_top;
                m_top = newNode;
            }

            m_size++;
        }
        T pop() {
            if (m_size == 0) {
                throw std::runtime_error("Nothing to pop from the Stack!");
            }

            T r = m_top->m_data;

            if (!(m_top->m_next)) {
                delete m_top;
            }
            else {
                Node<T>* temp = m_top;
                m_top = m_top->m_next;
                temp->m_next = nullptr;
                delete temp;
            }
            m_size--;

            return r;
        }
        e_ErrorState swap(Stack<T>& other) {
            try {
                if (this == &other) {
                    throw std::runtime_error("A Stack can't self-swap!");
                }
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                return ERROR_FAIL;
            }

            if (this->m_size > 0 || other.m_size > 0) {
                Node<T>* tempnode = this->m_top;
                this->m_top = other.m_top;
                other.m_top = tempnode;
                size_t tempsizet = this->m_size;
                this->m_size = other.m_size;
                other.m_size = tempsizet;
                return ERROR_PASS;
            }

            return ERROR_FAIL;
        }
        friend std::ostream& operator<<(std::ostream& os, Stack<T>& stk) {
            os << "Top [";
            if (stk.m_size != 0) {
                Node<T>* curr = stk.m_top;
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
            os << "] Bottom";
            return os;
        }
    };
    
    template <typename T>
    class SinglyLinkedList {
    private:
        size_t m_size;
        Node<T>* m_head;
        Node<T>* m_tail;
    public:
        SinglyLinkedList() : m_size(0), m_head(nullptr), m_tail(nullptr) {}
        SinglyLinkedList(Node<T>* head) : m_head(head) {
            m_size = 1;
            Node<T>* curr = m_head;
            while (curr->m_next) {
                curr = curr->m_next;
                m_size++;
            }
            m_tail = curr;
        }
        ~SinglyLinkedList() {
            if (m_size == 0) {
                return;
            }

            Node<T>* curr = m_head;
            while (curr->m_next) {
                curr = curr->m_next;
                m_head->m_next = nullptr;
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
        T& head() const {
            return m_head->m_data;
        }
        T& tail() const {
            return m_tail->m_data;
        }
        void push(const T& value) {
            Node<T>* newNode = new Node<T>(value);

            if (m_size == 0) {
                m_head = newNode;
                m_tail = newNode;
            }
            else {
                newNode->m_next = m_head;
                m_head = newNode;
            }

            m_size++;
        }
        void pushBack(const T& value) {
            Node<T>* newNode = new Node<T>(value);

            if (m_size == 0) {
                m_head = newNode;
                m_tail = newNode;
            }
            else {
                m_tail->m_next = newNode;
                m_tail = newNode;
            }

            m_size++;
        }
        template <typename... Args>
        void emplace(Args&&... args) {
            Node<T>* newNode = new Node<T>(std::forward<Args>(args)...);

            if (m_size == 0) {
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
            Node<T>* newNode = new Node<T>(std::forward<Args>(args)...);

            if (m_size == 0) {
                m_head = newNode;
                m_tail = newNode;
            }
            else {
                m_tail->m_next = newNode;
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
                m_head = nullptr;
                m_tail = nullptr;
            }
            else {
                Node<T>* temp = m_head;
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

            if (m_head == m_tail) {
                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
            }
            else {
                Node<T>* curr = m_head;
                while (curr->m_next != m_tail) {
                    curr = curr->m_next;
                }
                curr->m_next = nullptr;
                delete m_tail;
                m_tail = curr;
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

            Node<T>* curr = m_head;
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

            Node<T>* curr = m_head;
            long long int pos = 0;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                pos++;
                if (curr->m_data == targetData) {
                    return pos;
                }
            }

            return -1;
        }
        e_ErrorState findInsert(const T& targetData, const T& dataToInsert, e_InsertionRules rule = INSERT_AFTER) {
            if (m_size == 0) {
                return ERROR_FAIL;
            }

            if (m_head == m_tail) {
                if (m_head->m_data != targetData) {
                    return ERROR_FAIL;
                }

                Node<T>* newNode = new Node<T>(dataToInsert);
                if (rule == INSERT_AFTER) {
                    m_tail = newNode;
                    m_head->m_next = m_tail;
                    m_size++;
                    return ERROR_PASS;
                }
                else if (rule == INSERT_BEFORE) {
                    newNode->m_next = m_head;
                    m_head = newNode;
                    m_size++;
                    return ERROR_PASS;
                }
                else {
                    delete newNode;
                }
            }
            else {
                Node<T>* curr = m_head;

                Node<T>* newNode = new Node<T>(dataToInsert);
                if (curr->m_data == targetData) {
                    if (rule == INSERT_AFTER) {
                        newNode->m_next = m_head->m_next;
                        m_head->m_next = newNode;
                        m_size++;
                        return ERROR_PASS;
                    }
                    else if (rule == INSERT_BEFORE) {
                        newNode->m_next = m_head;
                        m_head = newNode;
                        m_size++;
                        return ERROR_PASS;
                    }
                }

                while (curr->m_next) {
                    Node<T>* temp = curr;
                    curr = curr->m_next;
                    if (curr->m_data != targetData) {
                        continue;
                    }

                    if (rule == INSERT_AFTER) {
                        newNode->m_next = temp->m_next->m_next;
                        curr->m_next = newNode;
                        if (curr == m_tail) {
                            m_tail = newNode;
                        }
                        m_size++;
                        return ERROR_PASS;
                    }
                    else if (rule == INSERT_BEFORE) {
                        newNode->m_next = curr;
                        temp->m_next = newNode;
                        m_size++;
                        return ERROR_PASS;
                    }
                }

                delete newNode;
            }

            return ERROR_FAIL;
        }
        e_ErrorState findDelete(const T& targetData) {
            if (m_size == 0) {
                return ERROR_FAIL;
            }

            if (m_head == m_tail) {
                if (m_head->m_data != targetData) {
                    return ERROR_FAIL;
                }

                delete m_head;
                m_head = nullptr;
                m_tail = nullptr;
                m_size--;
                return ERROR_PASS;
            }
            else {
                Node<T>* curr = m_head;

                if (curr->m_data == targetData) {
                    m_head = m_head->m_next;
                    curr->m_next = nullptr;
                    delete curr;
                    m_size--;
                    return ERROR_PASS;
                }

                while (curr->m_next) {
                    Node<T>* temp = curr;
                    curr = curr->m_next;
                    if (curr->m_data != targetData) {
                        continue;
                    }

                    temp->m_next = temp->m_next->m_next;
                    curr->m_next = nullptr;
                    if (curr == m_tail) {
                        m_tail = temp;
                    }
                    delete curr;
                    m_size--;
                    return ERROR_PASS;
                }
            }

            return ERROR_FAIL;
        }
        e_ErrorState findReplace(const T& targetData, const T& replacementData) {
            if (m_size == 0) {
                return ERROR_FAIL;
            }

            if (m_head->m_data == targetData) {
                m_head->m_data = replacementData;
                return ERROR_PASS;
            }
            else if (m_tail->m_data == targetData) {
                m_tail->m_data = replacementData;
                return ERROR_PASS;
            }

            Node<T>* curr = m_head;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                if (curr->m_data == targetData) {
                    curr->m_data = replacementData;
                    return ERROR_PASS;
                }
            }

            return ERROR_FAIL;
        }
        e_ErrorState swap(SinglyLinkedList<T>& other) {
            try {
                if (this == &other) {
                    throw std::runtime_error("A DoublyLinkedList can't self-swap!");
                }
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                return ERROR_FAIL;
            }

            if (this->m_size > 0 || other.m_size > 0) {
                Node<T>* tempnode = this->m_head;
                this->m_head = other.m_head;
                other.m_head = tempnode;
                size_t tempsizet = this->m_size;
                this->m_size = other.m_size;
                other.m_size = tempsizet;
                return ERROR_PASS;
            }

            return ERROR_FAIL;
        }
        e_ErrorState swapEnds() {
            if (m_size == 0 || m_head == m_tail) {
                return ERROR_FAIL;
            }

            Node<T>* tempnode = m_head;

            if (m_head->m_next == m_tail) {
                m_head = m_tail;
                m_tail = tempnode;
                m_head->m_next = m_tail;
                m_tail->m_next = nullptr;
            }
            else {
                Node<T>* curr = m_head;
                while (curr->m_next != m_tail) {
                    curr = curr->m_next;
                }

                m_head = m_tail;
                m_tail = tempnode;

                m_head->m_next = m_tail->m_next;
                curr->m_next = m_tail;
                m_tail->m_next = nullptr;
            }

            return ERROR_PASS;
        }
        friend std::ostream& operator<<(std::ostream& os, SinglyLinkedList<T>& LL) {
            os << '[';
            if (LL.m_size != 0) {
                Node<T>* curr = LL.m_head;
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
    
    template <typename T>
    class DoublyLinkedList {
    private:
        size_t m_size;
        DoublyNode<T>* m_head;
        DoublyNode<T>* m_tail;
    public:
        DoublyLinkedList() : m_size(0), m_head(nullptr), m_tail(nullptr) {};
        DoublyLinkedList(DoublyNode<T>* head) : m_head(head) {
            m_size = 1;
            DoublyNode<T>* curr = m_head;
            while (curr->m_next) {
                curr = curr->m_next;
                m_size++;
            }
            m_tail = curr;
        }
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
        T& head() const {
            return m_head->m_data;
        }
        T& tail() const {
            return m_tail->m_data;
        }
        void push(const T& value) {
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
        void pushBack(const T& value) {
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
            long long int pos = 0;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                pos++;
                if (curr->m_data == targetData) {
                    return pos;
                }
            }

            return -1;
        }
        e_ErrorState findInsert(const T& targetData, const T& dataToInsert, e_InsertionRules rule = INSERT_AFTER) {
            if (m_size == 0) {
                return ERROR_FAIL;
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
                return ERROR_PASS;
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
                return ERROR_PASS;
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
                    return ERROR_PASS;
                }
            }

            if (!newNode->m_prev && !newNode->m_next) {
                delete newNode;
            }

            return ERROR_FAIL;
        }
        e_ErrorState findDelete(const T& targetData) {
            if (m_size == 0) {
                return ERROR_FAIL;
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
                return ERROR_PASS;
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
                return ERROR_PASS;
            }

            DoublyNode<T>* curr = m_head;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                if (curr->m_data == targetData) {
                    curr->m_prev->m_next = curr->m_next;
                    curr->m_next->m_prev = curr->m_prev;
                    curr->m_next = nullptr;
                    curr->m_prev = nullptr;
                    delete curr;
                    m_size--;
                    return ERROR_PASS;
                }
            }

            return ERROR_FAIL;
        }
        e_ErrorState findReplace(const T& targetData, const T& replacementData) {
            if (m_size == 0) {
                return ERROR_FAIL;
            }

            if (m_head->m_data == targetData) {
                m_head->m_data = replacementData;
                return ERROR_PASS;
            }
            else if (m_tail->m_data == targetData) {
                m_tail->m_data = replacementData;
                return ERROR_PASS;
            }

            DoublyNode<T>* curr = m_head;
            while (curr->m_next && curr->m_next != m_tail) {
                curr = curr->m_next;
                if (curr->m_data == targetData) {
                    curr->m_data = replacementData;
                    return ERROR_PASS;
                }
            }

            return ERROR_FAIL;
        }
        e_ErrorState swap(DoublyLinkedList<T>& other) {
            try {
                if (this == &other) {
                    throw std::runtime_error("A DoublyLinkedList can't self-swap!");
                }
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                return ERROR_FAIL;
            }

            if (this->m_size > 0 || other.m_size > 0) {
                DoublyNode<T>* tempnode = this->m_head;
                this->m_head = other.m_head;
                other.m_head = tempnode;
                tempnode = this->m_tail;
                this->m_tail = other.m_tail;
                other.m_tail = tempnode;
                size_t tempsizet = this->m_size;
                this->m_size = other.m_size;
                other.m_size = tempsizet;
                return ERROR_PASS;
            }

            return ERROR_FAIL;
        }
        e_ErrorState swapEnds() {
            if (m_size == 0 || m_head == m_tail) {
                return ERROR_FAIL;
            }

            DoublyNode<T>* tempnode = m_head;

            if (m_head->m_next == m_tail) {
                m_head = m_tail;
                m_tail = tempnode;
                m_head->m_next = m_tail;
                m_head->m_prev = nullptr;
                m_tail->m_prev = m_head;
                m_tail->m_next = nullptr;
            }
            else {
                m_head->m_prev = m_tail->m_prev;
                m_tail->m_next = m_head->m_next;
                m_head->m_next = nullptr;
                m_tail->m_prev = nullptr;
                m_head->m_prev->m_next = m_head;
                m_tail->m_next->m_prev = m_tail;
                m_head = m_tail;
                m_tail = tempnode;
            }

            return ERROR_PASS;
        }
        friend std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T>& LL) {
            os << '[';
            if (LL.m_size != 0) {
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

    class PostfixExpression {
    private:
        Queue<char> m_expression;
        bool isOperator(char c) {
            return c == '(' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
        }
        short precedence(char op) {
            std::unordered_map<char, short> precedence_map = {
                {'+', 1}, {'-', 1},
                {'*', 2}, {'/', 2},
                {'^', 3}
            };
            return precedence_map[op];
        }
    public:
        PostfixExpression(const char*& fromInfix) : m_expression(Queue<char>()) {
            try {
                Stack<char> stack;
                for (size_t i = 0; i < strlen(fromInfix); i++) {
                    if (isOperator(fromInfix[i])) {
                        if (stack.isEmpty() || fromInfix[i] == '(') {
                            stack.push(fromInfix[i]);
                        }
                        else if (precedence(fromInfix[i]) > precedence(stack.top())) {
                            stack.push(fromInfix[i]);
                        }
                        else {
                            m_expression.push(stack.pop());
                            i--;
                        }
                    }
                    else if (fromInfix[i] == ')') {
                        while (!stack.isEmpty()) {
                            m_expression.push(stack.pop());
                            if (stack.top() == '(') {
                                stack.pop();
                                break;
                            }
                        }
                    }
                    else {
                        m_expression.push(fromInfix[i]);
                    }
                }
                while (!stack.isEmpty()) {
                    m_expression.push(stack.pop());
                }
            }
            catch (...) {
                std::cout << "PostfixExpression: Unknown error with converting infix to postfix. Did you pass in the correct charraySize?" << std::endl;
                return;
            }
        }
        Queue<char> getExpression() const {
            return m_expression;
        }
        friend std::ostream& operator<<(std::ostream& os, PostfixExpression& pe) {
            if (pe.m_expression.size() == 0) {
                return os;
            }

            Queue<char> temp(pe.m_expression);

            os << "Postfix Expression: ";
            while (!temp.isEmpty()) {
                os << temp.pop();
            }
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