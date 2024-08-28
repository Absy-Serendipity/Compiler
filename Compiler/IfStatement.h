#pragma once
#include "Node.h"

class IfStatement : public Node
{
public:
    IfStatement(Node* condition, Node* block, Node* mElseStatement) : Node(eSymbolName::If), mCondition(condition), mBlock(block), mElseStatement(mElseStatement) {}

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    Node* mCondition;
    Node* mBlock;
    Node* mElseStatement;
};
