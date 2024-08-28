#include "Block.h"


void Block::AddStatement(Node* childNode)
{
    mStatements.push_back(childNode);
}

const std::vector<Node*>& Block::GetStatements() const
{
    return mStatements;
}

void Block::AddStatements(const std::vector<Node*>& statements)
{
    mStatements.insert(mStatements.end(), statements.begin(), statements.end());
}


void Block::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    std::cout << std::endl;

    for (auto rit = mStatements.rbegin(); rit != mStatements.rend(); ++rit) {
        (*rit)->Print(indentCount + 1);
    }
}


eDataType Block::CheckWellFormedness(ScopedSymbolTable* localSymbolTable) const
{
    for (auto rit = mStatements.rbegin(); rit != mStatements.rend(); ++rit) {
        (*rit)->CheckWellFormedness(localSymbolTable);
    }
    return eDataType::Void;
}