#pragma once
#include "Node.h"

class EmptyNode final: public Node
{
public:
    EmptyNode(eSymbolName);
    ~EmptyNode() override = default;

public:
    bool Empty() const override;
    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
};
