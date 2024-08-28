#pragma once
#include "Node.h"
#include "Argument.h"

class FunctionCall : public Node
{
public:
    FunctionCall(const std::string&, Node*);

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;


private:
    std::vector<Node*> mArguments;
};