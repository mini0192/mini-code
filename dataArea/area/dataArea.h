#ifndef DATAAREA_H
#define DATAAREA_H

class DataArea {
private:
    int topIndex;
    int maxSize;
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
        topIndex(0),
        maxSize(10),
        elements(new int[maxSize])
    {}

    ~DataArea() {
        delete[] elements;
    }

    int pushNumber(int data) {
        int start = topIndex;
        if(topIndex >= maxSize) {
            resize();
        }
        this->elements[topIndex++] = data;
        return start;
    }

    int getNumber(int index) {
        return this->elements[index];
    }

    int pushStr(std::string data) {
        int start = topIndex;
        while(topIndex + data.length() >= maxSize) {
            resize();
        }
        for (size_t i = 0; i < data.length(); ++i) {
            this->elements[topIndex++] = static_cast<int>(data[i]);
        }
        this->elements[topIndex++] = 0;
        return start;
    }

    std::string getStr(int index) {
        std::string result;
        while (index <= topIndex && elements[index] != 0) {
            result += static_cast<char>(elements[index]);
            index++;
        }
        return result;
    }

    void clearData(int index) {
        topIndex = index - 1;
    }
};

#endif