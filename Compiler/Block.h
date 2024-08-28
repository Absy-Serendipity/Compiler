#pragma once
#include "Node.h"

class Block : public Node
{
public:
    Block() : Node(eSymbolName::BLOCK) {}
    void AddStatement(Node*);

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

    const std::vector<Node*>& GetStatements() const;
    void AddStatements(const std::vector<Node*>&);

private:
    std::vector<Node*> mStatements;
};