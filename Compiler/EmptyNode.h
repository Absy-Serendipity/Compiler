#pragma once
#include "Node.h"

class EmptyNode : public Node
{
public:
    EmptyNode(eSymbolName symbol) : Node(symbol) {}
public:
    bool Empty() const override;
    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
};
