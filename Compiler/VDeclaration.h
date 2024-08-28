#pragma once
#include "Node.h"

class VDeclaration : public Node
{
public:
    VDeclaration(const std::string& type, const std::string& identifier, const std::optional<Node*>& expression) :
        Node(eSymbolName::VDECL, identifier), mType(DATA_TYPES.at(type)), mAssignStatement(expression) {}

    VDeclaration(eDataType type, const std::string& identifier, const std::optional<Node*>& expression) :
        Node(eSymbolName::VDECL, identifier), mType(type), mAssignStatement(expression) {}

    void Print(const int) const override;
    eDataType CheckWellFormedness(ScopedSymbolTable*) const override;

private:
    eDataType mType;
    std::optional<Node*> mAssignStatement;
};