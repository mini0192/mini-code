class VariableStack : public Stack<Variable> {
public:
    using Stack::Stack;
    using Stack::push;
    using Stack::pop;
    using Stack::isEmpty;
    using Stack::size;

    VariableStack() : Stack() {}
    ~VariableStack() {}

    Variable* findByName(std::string name) override {
        for (int i = 0; i < topIndex; i++) {
            if (this->elements[i].getName() == name) return &this->elements[i];
        }
        return nullptr;
    }
};