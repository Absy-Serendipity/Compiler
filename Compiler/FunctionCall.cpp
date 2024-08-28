#include "FunctionCall.h"

FunctionCall::FunctionCall(const std::string& identifier, Node* argument) : Node(eSymbolName::FUNC_CALL, identifier)
{
    Node* current = argument;
    while (!current->Empty()) {
        const Argument* currentArgument = dynamic_cast<Argument*> (current);

        mArguments.push_back(currentArgument->GetExpression());
        current = currentArgument->GetNextArgument();
        delete currentArgument;
    }
    delete current;
}

void FunctionCall::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << "-> ID : " << GetValue();

    std::cout << std::endl;
    for (const auto argument : mArguments) {
        argument->Print(indentCount + 1);
    }
}


eDataType FunctionCall::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    std::vector<eDataType> argumentTypes;
    for (const auto argument : mArguments) {
        eDataType argumentType = argument->CheckWellFormedness(localSymbolTable);
        argumentTypes.push_back(argumentType);
    }

    SymbolTable::GetInstance().ValidateArgumentTypes(GetValue(), argumentTypes);

    return SymbolTable::GetInstance().GetReturnType(GetValue());
}