#include "Assign.h"


Node* Assign::GetExpression() const
{
    return mExpression;
}

void Assign::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << "-> ID : " << GetValue();

    std::cout << std::endl;
    mExpression->Print(indentCount + 1);
}

eDataType Assign::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    const eDataType dataType = localSymbolTable->GetDataType(GetValue());

    if (dataType != mExpression->CheckWellFormedness(localSymbolTable)) {
        throw std::runtime_error("Unmatched variable type: " + GetValue());
    }

    return eDataType::Void;
}