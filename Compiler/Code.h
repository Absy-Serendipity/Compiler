#pragma once
#include "Node.h"

class Code : public Node
{
public:
    Code() : Node(eSymbolName::CODE) {}

    void AddDeclaration(Node*);
    void AddDeclarations(const std::vector<Node*>&);
    const std::vector<Node*>& GetDeclarations() const;


    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;


private:
    std::vector<Node*> mFunctionDeclarations;
};