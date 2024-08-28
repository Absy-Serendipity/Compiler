#pragma once
#include "Node.h"

class Terminal : public Node
{
public:
    Terminal(const eSymbolName name, const std::string& value) : Node(name, value) {};
    Terminal(const eSymbolName name) :Node(name) {};

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    static const std::unordered_map <eSymbolName, eDataType> DATA_TYPE_TABLE;
};

