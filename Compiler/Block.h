#pragma once
#include "Node.h"

class Block final: public Node
{
public:
    Block();
	~Block() override = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
    void Destroy() override;

    void AddStatement(Node*);
    void AddStatements(const std::vector<Node*>&);
    const std::vector<Node*>& GetStatements() const;

private:
    std::vector<Node*> mStatements;
};