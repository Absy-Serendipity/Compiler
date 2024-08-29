#pragma once
#include "Node.h"

class Terminal final: public Node
{
public:
    Terminal(const eSymbolName, const std::string&);
    Terminal(const eSymbolName);
	~Terminal() = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    static const std::unordered_map <eSymbolName, eDataType> DATA_TYPE_TABLE;
};

