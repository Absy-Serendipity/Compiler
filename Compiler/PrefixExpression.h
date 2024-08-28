#pragma once
#include "Node.h"

class PrefixExpression : public Node
{
public:
    PrefixExpression(const std::string& op, std::string identifier) : Node(eSymbolName::UnaryOp, identifier), mSign(OPERATORS.at(op)) {}
    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    eOperator mSign;
};