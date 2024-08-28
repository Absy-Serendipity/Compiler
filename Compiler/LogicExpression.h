#pragma once
#include "Node.h"

class LogicExpression : public Node
{
public:
    LogicExpression(const std::string& op, Node* condition) : Node(eSymbolName::LOGIC_EXPR), mSign(OPERATORS.at(op)), mCondition(condition) {}

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    eOperator mSign;
    Node* mCondition;
};