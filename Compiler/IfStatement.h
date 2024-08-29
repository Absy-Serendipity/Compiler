#pragma once
#include "Node.h"

class IfStatement final : public Node
{
public:
    IfStatement(Node*, Node*, Node*);
    ~IfStatement() override = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
	void Destroy() override;

private:
    Node* mCondition;
    Node* mBlock;
    Node* mElseStatement;
};
