#pragma once
#include "Node.h"

class WhileStatement : public Node
{
public:
    WhileStatement(Node* conditionStatement, Node* block) : Node(eSymbolName::While), mConditionStatement(conditionStatement), mBlock(block) {}
    
    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;



private:
    Node* mConditionStatement;
    Node* mBlock;
};

