#pragma once
#include "Node.h"

class SignOperation : public Node
{
public:
	SignOperation(const std::string& op, Node* operand) :
		Node(eSymbolName::EXPR), mSign(OPERATORS.at(op)), mOperand(operand) {}

	void Print(const int) const override;
	eDataType CheckWellFormedness(ScopedSymbolTable*) const override;


private:
	eOperator mSign;
	Node* mOperand;
};
