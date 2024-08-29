#pragma once
#include "Node.h"

class LogicExpression final: public Node
{
public:
    LogicExpression(const std::string& op, Node* condition) : Node(eSymbolName::LOGIC_EXPR), mSign(OPERATORS.at(op)), mCondition(condition) {}
    ~LogicExpression() override = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
	void Destroy() override;

private:
    eOperator mSign;
    Node* mCondition;
};