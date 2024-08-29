#pragma once
#include "Node.h"

class SignOperation final : public Node
{
public:
	SignOperation(const std::string&, Node*);
	~SignOperation() override = default;

	void Print(const int) const override;
	eDataType CheckWellFormedness(ScopedSymbolTable*) const override;
	void Destroy() override;

private:
	eOperator mSign;
	Node* mOperand;
};
