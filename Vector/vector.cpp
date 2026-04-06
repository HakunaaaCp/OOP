#include <iostream>
using namespace std;

template <typename T>
class Vector {
private:
    T* arr;
    size_t size;
    size_t capacity;

    void resize() {
        capacity <<= 1; 
        T* new_arr = new T[capacity];
        for(int i = 0; i < size; i++) new_arr[i] = std::move(arr[i]); // is T is complex type, vector itself for example. 
        delete[] arr;
        arr = new_arr;
    }

public:
    // constructors
    Vector() : size(0), capacity(1) {
        arr = new T[1];
    }
    Vector(size_t size) : size(size), capacity(size) {
        arr = new T[size];
        for(int i = 0; i < size; i++) arr[i] = 0;
    }  
    Vector(size_t size, const T& a) : size(size), capacity(size) {
        arr = new T[size];
        for(int i = 0; i < size; i++) arr[i] = a;
    }  
    Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
        arr = new T[capacity];
        for(int i = 0; i < size; i++) arr[i] = other.arr[i];
    }
    // moveconstructor 
    Vector(Vector&& other) noexcept : arr(other.arr), size(other.size), capacity(other.capacity) {
        other.arr = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    Vector(std::initializer_list<T> list) : size(list.size()), capacity(list.size()) {
        
        arr = new T[capacity];
        
        // std::copy is efficient and clean
        std::copy(list.begin(), list.end(), arr);
    }
    // deconstructors
    ~Vector() {
        size = 0;
        capacity = 0;
        delete[] arr; 
    }
    // operators 
    Vector<T>& operator=(const Vector& other) {
        if(this == &other) return *this; // self assignment check 
        delete[] arr;
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for(int i = 0; i < size; i++) arr[i] = other.arr[i];
        return *this;
    }
    // move operation 
    Vector<T>& operator=(Vector&& other) noexcept {
        if(this == &other) return *this; 
        delete[] arr; 
        
        size = other.size;
        capacity = other.capacity;
        arr = other.arr; 

        other.arr = nullptr;
        other.size = 0;
        other.capacity = 0;

        return *this;   
    }
    bool operator==(const Vector& other) const {
        if(size != other.size) return false;
        for(int i = 0; i < size; i++) {
            if(arr[i] != other.arr[i]) return false;
        }
        return true;
    }
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
    T& operator[](size_t idx) {
        if(idx >= size) {
            throw out_of_range("Index out of range");
        }
        return arr[idx];
    }
    const T& operator[](size_t idx) const {
        if(idx >= size) {
            throw out_of_range("Index out of range");
        }
        return arr[idx];
    }
    friend ostream& operator<<(ostream& os, const Vector& v) {
        for(int i = 0; i < v.size; i++) {
            if(i) os << ' ';
            os << v.arr[i];
        }
        return os;
    }
    // methods
    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }
    bool empty() const { return size == 0; }
    void push_back(const T& a) {
        if(size == capacity) resize();
        arr[size++] = a; 
    }
    // move version of push_back
    void push_back(T&& a) {
        if(size == capacity) resize();
        arr[size++] = std::move(a);
    }
    void pop_back() {
        if(size) size--;
    }
    T& front() {
        if(!size) throw out_of_range("Vector is empty");
        return arr[0];
    }
    T& back() {
        if(!size) throw out_of_range("Vector is empty");
        return arr[size - 1];
    }
    void insert(size_t idx, const T& val) {
        if(idx > size) throw out_of_range("Idx is out of range");
        if(size == capacity) resize();
        for(int i = size - 1; i >= (int)idx; i--) arr[i + 1] = arr[i];
        arr[idx] = val;
        size++;
    }
    void erase(size_t idx) {
        if(idx >= size) throw out_of_range("Idx is out of range");
        for(int i = idx; i < size - 1; i++) arr[i] = arr[i + 1];
        size--;
    }
    void clear() {
        size = 0;
    }
    void reserve(size_t new_cap) {
        if(new_cap <= capacity) return;
        capacity = new_cap;
        T* new_arr = new T[capacity];
        for(int i = 0; i < size; i++) new_arr[i] = std::move(arr[i]);
        delete[] arr;
        arr = new_arr;
    }
    // find first occurrence, returns index or -1
    int find(const T& val) const {
        for(int i = 0; i < size; i++) {
            if(arr[i] == val) return i;
        }
        return -1;
    }
    bool contains(const T& val) const {
        return find(val) != -1;
    }
    T* begin() { return arr; }
    T* end() { return arr + size; }
    const T* begin() const { return arr; }
    const T* end() const { return arr + size; }
    void print() {
        for(int i = 0; i < size; i++) cout << arr[i] << ' ';
        cout << "\n--------------------\n";
    }
    void print_2d() {
        for(int i = 0; i < size; i++) {
            int m = arr[i].get_size();
            for(int j = 0; j < m; j++) {
                cout << arr[i][j] << ' ';
            }
            if(i != size - 1) cout << '\n';
        }
        cout << "\n--------------------\n";
    }
};

int main() {
    Vector<int> v = {1, 2, 3, 4, 5};
    v.print();

    // push_back and pop_back
    v.push_back(6);
    v.pop_back();
    cout << v << "\n--------------------\n";

    // insert and erase
    v.insert(2, 99);
    cout << "after insert(2, 99): " << v << '\n';
    v.erase(2);
    cout << "after erase(2): " << v << '\n';

    // find and contains
    cout << "find 3: " << v.find(3) << '\n';
    cout << "contains 10: " << v.contains(10) << '\n';

    // front and back
    cout << "front: " << v.front() << " back: " << v.back() << '\n';

    // comparison
    Vector<int> v2 = {1, 2, 3, 4, 5};
    cout << "v == v2: " << (v == v2) << '\n';

    // copy and move
    Vector<int> v3 = v;
    Vector<int> v4 = std::move(v3);
    cout << "v4 after move: " << v4 << '\n';

    // 2d vector
    Vector<Vector<int>> matrix;
    matrix.push_back({1, 2, 3});
    matrix.push_back({4, 5, 6});
    matrix.push_back({7, 8, 9});
    matrix.print_2d();

    return 0;
}
