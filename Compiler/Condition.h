#pragma once
#include "Node.h"

class Condition final: public Node
{
public:
    Condition(Node*, Node*);
    ~Condition() override = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
	void Destroy() override;

private:
    Node* mConditionExpression;
    Node* mLogicExpression;
};