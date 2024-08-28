#pragma once
#include "Node.h"



class BinaryExpression : public Node
{
public:
    BinaryExpression(const eSymbolName symbol, Node* leftOperand, const std::string& op, Node* rightOperand) :
        Node(symbol), mLeftOperand(leftOperand), mOperator(OPERATORS.at(op)), mRightOperand(rightOperand) {}


    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    Node* mLeftOperand;
    eOperator mOperator;
    Node* mRightOperand;

    static const std::unordered_set<eOperator> COMPARISON_OPERATORS;
};
