#include "SignOperation.h"

void SignOperation::Print(const int indentCount) const
{
	for (int i = 0; i < indentCount; i++) {
		std::cout << INDENT;
	}
	std::cout << "SIGN OPERATION: " << STRING_OPERATORS.at(mSign) << GetValue() << std::endl;
}
eDataType SignOperation::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
	return mOperand->CheckWellFormedness(localSymbolTable);
}
