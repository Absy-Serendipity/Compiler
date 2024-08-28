#pragma once
#include "Node.h"

class Condition : public Node
{
public:
    Condition(Node* conditionExpression, Node* logicExpression) :
        Node(eSymbolName::COND), mConditionExpression(conditionExpression), mLogicExpression(logicExpression) {}

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    Node* mConditionExpression;
    Node* mLogicExpression;
};