#include <iostream>

class DataArea {
private:
    int startPoint;
    int endPoint;

    int maxSize;
    int* elements;

    void resize() {
        maxSize *= 2;
        int* newElements = new int[maxSize];
        for (int i = 0; i <= endPoint; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    DataArea() :
        maxSize(10),
        startPoint(0),
        endPoint(0),
        elements(new int[maxSize])
    {}

    int pushNumber(int data) {
        int start = endPoint;
        if(endPoint >= maxSize) {
            resize();
        }
        this->elements[endPoint++] = data;
        return start;
    }

    int getNumber(int index) {
        return this->elements[index];
    }

    int pushStr(std::string data) {
        int start = endPoint;
        while(endPoint + data.length() >= maxSize) {
            resize();
        }
        for (size_t i = 0; i < data.length(); ++i) {
            this->elements[endPoint++] = static_cast<int>(data[i]);
        }
        this->elements[endPoint++] = 0;
        return start;
    }

    std::string getStr(int index) {
        std::string result;
        while (index <= endPoint && elements[index] != 0) {
            result += static_cast<char>(elements[index]);
            index++;
        }
        return result;
    }
};
