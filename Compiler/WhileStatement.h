#pragma once
#include "Node.h"

class WhileStatement final: public Node
{
public:
    WhileStatement(Node*, Node*);
    ~WhileStatement() = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
	void Destroy() override;


private:
    Node* mConditionStatement;
    Node* mBlock;
};

