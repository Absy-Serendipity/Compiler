#include "Node.h"


std::string Node::GetValue() const
{
	return mValue;
}

eSymbolName Node::GetName() const
{
	return mName;
}


void Node::Print(const int indentCount) const
{
	for (int i = 0; i < indentCount; i++) {
		std::cout << INDENT;
	}
    
    std::cout << "INVALID: "<< STRING_SYMOL_NAMES.at(GetName()) << std::endl;
}

bool Node::Empty() const
{
	return false;
}

eDataType Node::CheckWellFormedness(ScopedSymbolTable*) const
{
    return eDataType::Void;
}