#pragma once
#include "Node.h"

class PostfixExpression : public Node
{
public:
    PostfixExpression(const std::string& op, std::string identifier) : Node(eSymbolName::UnaryOp, identifier), mSign(OPERATORS.at(op)) {}
    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;


private:
    eOperator mSign;
};