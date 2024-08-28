#include "Terminal.h"

// Terminal
void Terminal::Print(const int INDENT_COUNT) const
{
    for (int i = 0; i < INDENT_COUNT; i++) {
        std::cout << INDENT;
    }
    std::cout << STRING_SYMOL_NAMES.at(GetName());
    if (!GetValue().empty()) {
        std::cout << ", VALUE: " << GetValue();
    }
    std::cout << "  TERMINAL--";
    std::cout << std::endl;
}

eDataType Terminal::CheckWellFormedness(ScopedSymbolTable* symbolTable) const
{
    if (GetName() == eSymbolName::Identifier) {
        return symbolTable->GetDataType(GetValue());
    }

    return DATA_TYPE_TABLE.at(GetName());
}

const std::unordered_map <eSymbolName, eDataType> Terminal::DATA_TYPE_TABLE = {
    {eSymbolName::Integer, eDataType::Int}, {eSymbolName::Character, eDataType::Char},{eSymbolName::Boolean, eDataType::Bool},
};