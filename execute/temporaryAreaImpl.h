class TemporaryArea {
private:
    int maxSize;
    Variable* elements;
    int topIndex;
    int bottomIndex;

    void resize() {
        maxSize *= 2;
        Variable* newElements = new Variable[maxSize];
        for (int i = 0; i <= topIndex; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:
    TemporaryArea() :
        maxSize(10),
        topIndex(0),
        bottomIndex(0),
        elements(new Variable[maxSize])
    {}

    ~TemporaryArea() {
        delete[] elements;
    }

    void callFunction() {
        Variable funcData;
        funcData.setType(FUNCTION_DATA);
        funcData.setDataFunc(bottomIndex);
        push(funcData);

        bottomIndex = topIndex;
    }

    void doneFunction() {
        topIndex = bottomIndex;
        Variable funcData = findByIndex(bottomIndex);
        bottomIndex = funcData.getDataFunc();
    }

    void push(Variable data) {
        if (topIndex >= maxSize) resize();
        elements[topIndex++] = data;
    }

    Variable findByIndex(int index) {
        return elements[index];
    }

    Variable pop() {
        return elements[--topIndex];
    }

    Variable* findByName(std::string name) {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return &this->elements[i];
        }
        return nullptr;
    }

    bool isEmpty() {
        return topIndex <= 0;
    }

    int size() {
        return topIndex;
    }
};