#include "BinaryExpression.h"


void BinaryExpression::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << ", BINARY OPERATOR: " << STRING_OPERATORS.at(mOperator) << std::endl;

    mLeftOperand->Print(indentCount + 1);
    mRightOperand->Print(indentCount + 1);
}

eDataType BinaryExpression::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    const eDataType leftType = mLeftOperand->CheckWellFormedness(localSymbolTable);
    const eDataType rightType = mRightOperand->CheckWellFormedness(localSymbolTable);
    if (leftType == rightType) {
        if (COMPARISON_OPERATORS.find(mOperator) != COMPARISON_OPERATORS.end()) {
            return eDataType::Bool;
        }
        return leftType;
    }

    throw std::runtime_error("Unmatched variable type: Binary Expression");
}


const std::unordered_set<eOperator> BinaryExpression::COMPARISON_OPERATORS = {
    Equal, NotEqual, Less, Greater, LessEqual, GreaterEqual
};