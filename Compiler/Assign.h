#pragma once
#include "Node.h"

class Assign : public Node
{
public:
    Assign(const std::string& identifier, Node* expression) : Node(eSymbolName::ASSIGN, identifier), mExpression(expression) {}

    Node* GetExpression() const;
    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    Node* mExpression;
};