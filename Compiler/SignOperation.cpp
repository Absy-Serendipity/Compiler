#include "SignOperation.h"

SignOperation::SignOperation(const std::string& op, Node* operand) 
	: Node(eSymbolName::EXPR)
	, mSign(OPERATORS.at(op))
	, mOperand(operand) 
{}


void SignOperation::Print(const int indentCount) const
{
	for (int i = 0; i < indentCount; i++) 
	{
		std::cout << INDENT;
	}
	std::cout << "SIGN OPERATION: " << STRING_OPERATORS.at(mSign) << GetValue() << std::endl;
}
eDataType SignOperation::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
	return mOperand->CheckWellFormedness(localSymbolTable);
}


void SignOperation::Destroy()
{
	delete mOperand;
	delete this;
}
