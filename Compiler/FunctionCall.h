#pragma once
#include "Node.h"
#include "Argument.h"

class FunctionCall final: public Node
{
public:
    FunctionCall(const std::string&, Node*);
	~FunctionCall() override = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
	void Destroy() override;

private:
    std::vector<Node*> mArguments;
};