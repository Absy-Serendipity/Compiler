#include "VDeclaration.h"

VDeclaration::VDeclaration(const std::string& type, const std::string& identifier, const std::optional<Node*>& expression) 
    : Node(eSymbolName::VDECL, identifier)
    , mType(DATA_TYPES.at(type))
    , mAssignStatement(expression) 
{}

VDeclaration::VDeclaration(const eDataType type, const std::string& identifier, const std::optional<Node*>& expression)
    : Node(eSymbolName::VDECL, identifier)
    , mType(type)
    , mAssignStatement(expression) 
{}


void VDeclaration::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) 
    {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << "-> ID : " << GetValue();

    std::cout << " , TYPE : " << STRING_DATA_TYPES.at(mType) << std::endl;

    if (mAssignStatement.has_value()) 
    {
        mAssignStatement.value()->Print(indentCount + 1);
    }
}
eDataType VDeclaration::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    if (mAssignStatement.has_value()) 
    {
        if (mType != mAssignStatement.value()->CheckWellFormedness(localSymbolTable)) 
        {
            throw std::runtime_error("Unmatched variable type: " + GetValue());
        }
    }
    localSymbolTable->AddSymbol(GetValue(), mType);

    return mType;
}

void VDeclaration::Destroy()
{
	if (mAssignStatement.has_value()) {
		mAssignStatement.value()->Destroy();
	}
	delete this;
}
