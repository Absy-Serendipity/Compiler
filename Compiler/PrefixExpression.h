#pragma once
#include "Node.h"

class PrefixExpression final: public Node
{
public:
    PrefixExpression(const std::string&, const std::string&);
	~PrefixExpression() override = default;
    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    eOperator mSign;
};