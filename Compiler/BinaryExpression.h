#pragma once
#include "Node.h"

class BinaryExpression final : public Node
{
public:
    BinaryExpression(const eSymbolName, Node*, const std::string&, Node*);
    ~BinaryExpression() override = default;

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
    void Destroy() override;

private:
    Node* mLeftOperand;
    eOperator mOperator;
    Node* mRightOperand;

    static const std::unordered_set<eOperator> COMPARISON_OPERATORS;
};
