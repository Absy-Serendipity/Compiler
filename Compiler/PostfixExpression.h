#pragma once
#include "Node.h"

class PostfixExpression final: public Node
{
public:
    PostfixExpression(const std::string&, std::string);
	~PostfixExpression() = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    eOperator mSign;
};