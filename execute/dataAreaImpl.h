#include <iostream>

class DataArea {
private:
    int maxSize;
    int topIndex;
    int* elements;

    void resize() {
        maxSize *= 2;
        int* newElements = new int[maxSize];
        for (int i = 0; i <= topIndex; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    DataArea() :
        maxSize(10),
        topIndex(-1),
        elements(new int[maxSize])
    {}

    int pushNumber(int data) {
        if(topIndex >= maxSize) {
            resize();
        }
        this->elements[++topIndex] = data;
        return topIndex;
    }

    int getNumber(int index) {
        return this->elements[index];
    }

    int pushStr(std::string data) {
        while(topIndex + data.length() >= maxSize) {
            resize();
        }
        for (size_t i = 0; i < data.length(); ++i) {
            this->elements[++topIndex] = static_cast<int>(data[i]);
        }
        this->elements[++topIndex] = 0;
        return topIndex - data.length();
    }

    std::string getStr(int index) {
        std::string result;
        while (index <= topIndex && elements[index] != 0) {
            result += static_cast<char>(elements[index]);
            index++;
        }
        return result;
    }
};
