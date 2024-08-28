#include "FDeclaration.h"

FDeclaration::FDeclaration(const std::string& returnType, const std::string& identifier, Node* parameter, Node* block, Node* returnStatement) :
    Node(eSymbolName::FDECL, identifier), mBlock(block), mReturnStatement(returnStatement), mReturnType(DATA_TYPES.at(returnType))
{
    Node* current = parameter;
    while (!current->Empty()) {
        Parameter* currentParameter = dynamic_cast<Parameter*>(current);
        mParameters.push_back(new VDeclaration(currentParameter->GetType(), currentParameter->GetValue(), std::nullopt));
        current = currentParameter->GetNextParameter();
        delete currentParameter;
    }
    delete current;
}

void FDeclaration::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());

    std::cout << "-> ID : " << GetValue();
    std::cout << " , RETURN TYPE : " << STRING_DATA_TYPES.at(mReturnType) << std::endl;

    for (const auto parameter : mParameters) {
        parameter->Print(indentCount + 1);
    }
    mBlock->Print(indentCount + 1);
    mReturnStatement->Print(indentCount + 1);
}

eDataType FDeclaration::CheckWellFormedness(ScopedSymbolTable*) const
{

    ScopedSymbolTable* localSymbolTable = new ScopedSymbolTable(nullptr);

    std::vector<eDataType> parameterTypes;
    for (const auto parameter : mParameters) {
        parameterTypes.push_back(parameter->CheckWellFormedness(localSymbolTable));
    }

    SymbolTable::GetInstance().AddFunctionSignature(GetValue(), mReturnType, parameterTypes);


    mBlock->CheckWellFormedness(localSymbolTable);
    if (mReturnType != mReturnStatement->CheckWellFormedness(localSymbolTable)) {
        throw std::runtime_error("Unmatched return type: " + GetValue());
    }

    SymbolTable::GetInstance().AddFunctionSymbol(GetValue(), localSymbolTable);
    return eDataType::Void;
}