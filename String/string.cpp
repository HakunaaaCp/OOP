#include <iostream>
#include <cstring>
using namespace std;

class String {
private: 
    size_t size, capacity;
    char* arr;
    void expand() {
        capacity = max((size_t)1, capacity << 1);
        char* new_arr = new char[capacity];
        for(int i = 0; i < size; i++) new_arr[i] = arr[i];
        delete[] arr;
        arr = new_arr;
    }
public:
    String() : size(0), capacity(1) {
        arr = new char[1];
    }
    String(const size_t& size) : size(size), capacity(size) { // just size_t size ? 
        arr = new char[capacity];
    }
    String(size_t size, const char& c) : String(size) {
        for(int i = 0; i < size; i++) arr[i] = c; 
    }
    String(const char* str) : size(strlen(str)), capacity(strlen(str)) {
        arr = new char[capacity];
        for(int i = 0; i < size; i++) arr[i] = str[i];
    }
    String(const String& other) : size(other.size), capacity(other.capacity) {
        arr = new char[capacity];
        for(int i = 0; i < size; i++) arr[i] = other.arr[i];
    }
    String(String&& other) noexcept : size(other.size), capacity(other.capacity), arr(other.arr) {
        other.arr = nullptr;
        other.size = other.capacity = 0;
    }
    ~String() {
        size = capacity = 0;
        delete[] arr;
    }
    // operators
    String& operator=(String&& other) noexcept {
        if(this != &other) {
            delete[] arr;
            size = other.size;
            capacity = other.capacity;
            arr = other.arr;

            other.arr = nullptr;
            other.size = other.capacity = 0;
        }
        return *this;
    }
    String& operator=(String other) {
        if(this != &other) {
            delete[] arr;
            size = other.size;
            capacity = other.capacity;
            arr = new char[capacity];
            for(int i = 0; i < size; i++) arr[i] = other.arr[i];
        }
        return *this;
    }
    String operator+(const String& other) const {
        String result(size + other.size);
        for(int i = 0; i < size; i++) result.arr[i] = arr[i];
        for(int i = 0; i < other.size; i++) result.arr[size + i] = other.arr[i];
        return result;
    }
    String& operator+=(const String& other) {
        for(int i = 0; i < other.size; i++) push_back(other.arr[i]);
        return *this;
    }
    String& operator+=(const char& c) {
        push_back(c);
        return *this;
    }
    bool operator==(const String& other) const {
        if(size != other.size) return false;
        for(int i = 0; i < size; i++) {
            if(arr[i] != other.arr[i]) return false;
        }
        return true;
    }
    bool operator!=(const String& other) const {
        return !(*this == other);
    }
    bool operator<(const String& other) const {
        int min_len = min(size, other.size);
        for(int i = 0; i < min_len; i++) {
            if(arr[i] < other.arr[i]) return true;
            if(arr[i] > other.arr[i]) return false;
        }
        return size < other.size;
    }
    char& operator[](size_t idx) {
        if(idx >= size) {
            throw out_of_range("Index is out of range");
        }
        return arr[idx];
    }
    const char& operator[](size_t idx) const {
        if(idx >= size) {
            throw out_of_range("Index is out of range");
        }
        return arr[idx];
    }
    friend ostream& operator<<(ostream& os, const String& s) {
        for(int i = 0; i < s.size; i++) os << s.arr[i];
        return os;
    }
    // methods
    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }
    bool empty() const { return size == 0; }
    void push_back(const char& c) {
        if(size == capacity) expand();
        arr[size++] = c; 
    }
    void pop_back() {
        if(!size) throw out_of_range("String is empty");
        size--;
    }
    char& front() {
        if(!size) throw out_of_range("String is empty");
        return arr[0];
    }
    char& back() { 
        if(!size) {
            throw out_of_range("String is empty");
        }
        return arr[size - 1]; 
    }
    void insert(size_t idx, const char& c) {
        if(idx > size) {
            throw out_of_range("Idx is out of range");
        }
        if(size == capacity) expand();
        for(int i = size - 1; i >= (int)idx; i--) arr[i + 1] = arr[i];
        arr[idx] = c; 
        size++;
    }
    void remove(size_t idx) {
        if(idx > size - 1) {
            throw out_of_range("Idx is out of range");
        }
        for(int i = idx; i < size - 1; i++) arr[i] = arr[i + 1];
        size--;
    }
    void clear() {
        size = 0;
    }
    // search for a character, returns index or -1
    int find(const char& c) const {
        for(int i = 0; i < size; i++) {
            if(arr[i] == c) return i;
        }
        return -1;
    }
    // substring from idx with length len
    String substr(size_t idx, size_t len) const {
        if(idx >= size) throw out_of_range("Idx is out of range");
        if(idx + len > size) len = size - idx; // clamp
        String result(len);
        for(int i = 0; i < len; i++) result.arr[i] = arr[idx + i];
        return result;
    }
    // returns null-terminated c string
    char* c_str() const {
        char* str = new char[size + 1];
        for(int i = 0; i < size; i++) str[i] = arr[i];
        str[size] = '\0';
        return str;
    }
    char* begin() { return arr; }
    char* end() { return arr + size; }
    const char* begin() const { return arr; }
    const char* end() const { return arr + size; }
    void print() {
        for(int i = 0; i < size; i++) cout << arr[i];
        cout << "\n--------------------\n";
    }
};

int main() {
    String s = {4, 'a'};
    s.print();
    s.insert(4, 'b');
    s.print();
    s.remove(3);
    String s1 = std::move(s);
    s1.print();

    // c-string constructor
    String s2("hello");
    cout << s2 << "\n--------------------\n";

    // concatenation
    String s3("world");
    String s4 = s2 + String(" ") + s3;
    cout << s4 << "\n--------------------\n";

    // comparison 
    cout << "s2 == s3: " << (s2 == s3) << '\n';
    cout << "s2 != s3: " << (s2 != s3) << '\n';
    cout << "s2 < s3: " << (s2 < s3) << '\n';

    // find and substr
    String s5("abcdef");
    cout << "find 'd' in abcdef: " << s5.find('d') << '\n';
    String sub = s5.substr(2, 3);
    cout << "substr(2,3): " << sub << '\n';

    // += operator
    s5 += '!';
    cout << "after +=: " << s5 << '\n';

    return 0;
}

// size_t size ? in bit 
// private
// header.h