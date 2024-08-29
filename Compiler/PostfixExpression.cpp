#include "PostfixExpression.h"

PostfixExpression::PostfixExpression(const std::string& op, std::string identifier) 
	: Node(eSymbolName::UnaryOp, identifier)
	, mSign(OPERATORS.at(op)) 
{}


void PostfixExpression::Print(const int indentCount) const
{
	for (int i = 0; i < indentCount; i++) 
	{
		std::cout << INDENT;
	}

	std::cout << "POSTFIX EXPRESSION: " << GetValue() << STRING_OPERATORS.at(mSign) << std::endl;
}
eDataType PostfixExpression::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
	return localSymbolTable->GetDataType(GetValue());
}