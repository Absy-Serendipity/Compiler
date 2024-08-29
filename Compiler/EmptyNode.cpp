#include "EmptyNode.h"

EmptyNode::EmptyNode(eSymbolName symbol) 
    : Node(symbol) 
{}

void EmptyNode::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) 
    {
        std::cout << INDENT;
    }
    std::cout << "***EMPTY NODE***" << std::endl;
}
eDataType EmptyNode::CheckWellFormedness(ScopedSymbolTable*) const
{
    return eDataType::Void;
}

bool EmptyNode::Empty() const
{
    return true;
}