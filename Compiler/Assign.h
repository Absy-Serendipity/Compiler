#pragma once
#include "Node.h"

class Assign final: public Node
{
public:
    Assign(const std::string&, Node*);
    ~Assign() override = default;

    Node* GetExpression() const;
    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    Node* mExpression;
};