#include "Code.h"


Code::Code() 
    : Node(eSymbolName::CODE) 
{}


void Code::AddDeclaration(Node* fDeclaration)
{
    mFunctionDeclarations.push_back(fDeclaration);
}

const std::vector<Node*>& Code::GetDeclarations() const
{
    return mFunctionDeclarations;
}

void Code::AddDeclarations(const std::vector<Node*>& fDeclaration)
{
    mFunctionDeclarations.insert(mFunctionDeclarations.end(), fDeclaration.begin(), fDeclaration.end());
}



void Code::Print(const int indentCount) const
{
    for (int i = 0; i < indentCount; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());

    for (auto rit = mFunctionDeclarations.rbegin(); rit != mFunctionDeclarations.rend(); ++rit) {
        std::cout << std::endl;
        (*rit)->Print(indentCount + 1);
    }

}

eDataType Code::CheckWellFormedness(ScopedSymbolTable*) const
{
    for (auto rit = mFunctionDeclarations.rbegin(); rit != mFunctionDeclarations.rend(); ++rit) {
        std::cout << std::endl;
        (*rit)->CheckWellFormedness(nullptr);
    }

    return eDataType::Void;
}

void Code::Destroy()
{
    for (auto& fDeclaration : mFunctionDeclarations) 
    {
        fDeclaration->Destroy();
    }
    delete this;
}