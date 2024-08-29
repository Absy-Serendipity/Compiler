#pragma once

#include "SymbolTable.h"
#include "eOperator.h"

#include <unordered_set>
#include <optional>
#include <unordered_map>



enum class eSymbolName 
{
    // type
    Character, Integer, Boolean,
	// syntactic symbols
    LParen, RParen, LBrace, RBrace, Comma, Semi, WhiteSpace,
	// keywords
    Return, While, Type, Else, If,
	// operators
    AddSub, MulDiv, UnaryOp, CompOp, LogicOp, Assign,
	// identifier
    Identifier,
          
    // Non terminals
    $,
    EXPR, FACT, FUNC_CALL, POSTFIX_STMT, CODE, VDECL, FDECL, BLOCK, ASSIGN, MORE_PARAMETER, COND, MORE_ARGUMENT,
    COND_EXPR, ELSE, PARAMETER, PREFIX_STMT, STMT, TERM, ARGUMENT, S, RETURN, LOGIC_EXPR,
};


const std::unordered_map <std::string, eOperator> OPERATORS = 
{
    {"+", ADD}, {"-", SUB},{"*", MUL},{"/", DIV},{"++", UNARY_ADD},{"--", UNARY_SUB},{"=", MOV},{"&", AND},
    {"|", OR}, {"==", Equal},{"!=", NotEqual},{"<", Less},{">", Greater},{"<=", LessEqual},{">=", GreaterEqual}
};
const std::unordered_map < std::string, eDataType> DATA_TYPES = 
{
    {"int", eDataType::Int}, {"char", eDataType::Char},{"bool", eDataType::Bool},
};
const std::unordered_map<eOperator, std::string> STRING_OPERATORS = 
{
    {ADD, "+"}, {SUB, "-"}, {MUL, "*"}, {DIV, "/"}, {UNARY_ADD, "++"},
    {UNARY_SUB, "--"}, {MOV, "="}, {AND, "&"}, {OR, "|"},
    {Equal, "=="}, {NotEqual, "!="}, {Less, "<"}, {Greater, ">"},
    {LessEqual, "<="}, {GreaterEqual, ">="}
};
const std::unordered_map<eSymbolName, std::string> STRING_SYMOL_NAMES = 
{
    {eSymbolName::Character, "Character"},
    {eSymbolName::Integer, "Integer"},
    {eSymbolName::Boolean, "Boolean"},
    {eSymbolName::LParen, "LParen"},
    {eSymbolName::RParen, "RParen"},
    {eSymbolName::LBrace, "LBrace"},
    {eSymbolName::RBrace, "RBrace"},
    {eSymbolName::Comma, "Comma"},
    {eSymbolName::Semi, "Semi"},
    {eSymbolName::WhiteSpace, "WhiteSpace"},
    {eSymbolName::Return, "Return"},
    {eSymbolName::While, "While"},
    {eSymbolName::Type, "Type"},
    {eSymbolName::Else, "Else"},
    {eSymbolName::If, "If"},
    {eSymbolName::AddSub, "AddSub"},
    {eSymbolName::MulDiv, "MulDiv"},
    {eSymbolName::UnaryOp, "UnaryOp"},
    {eSymbolName::CompOp, "CompOp"},
    {eSymbolName::LogicOp, "LogicOp"},
    {eSymbolName::Assign, "Assign"},
    {eSymbolName::Identifier, "Identifier"},
    {eSymbolName::$, "END_MARK"},
    {eSymbolName::EXPR, "EXPR"},
    {eSymbolName::FACT, "FACT"},
    {eSymbolName::FUNC_CALL, "FUNC_CALL"},
    {eSymbolName::POSTFIX_STMT, "POSTFIX_STMT"},
    {eSymbolName::CODE, "CODE"},
    {eSymbolName::VDECL, "VDECL"},
    {eSymbolName::FDECL, "FDECL"},
    {eSymbolName::BLOCK, "BLOCK"},
    {eSymbolName::ASSIGN, "ASSIGN"},
    {eSymbolName::MORE_PARAMETER, "MORE_PARAMETER"},
    {eSymbolName::COND, "COND"},
    {eSymbolName::MORE_ARGUMENT, "MORE_ARGUMENT"},
    {eSymbolName::COND_EXPR, "COND_EXPR"},
    {eSymbolName::ELSE, "ELSE"},
    {eSymbolName::PARAMETER, "PARAMETER"},
    {eSymbolName::PREFIX_STMT, "PREFIX_STMT"},
    {eSymbolName::STMT, "STMT"},
    {eSymbolName::TERM, "TERM"},
    {eSymbolName::ARGUMENT, "ARGUMENT"},
    {eSymbolName::S, "S"},
    {eSymbolName::RETURN, "RETURN"},
    {eSymbolName::LOGIC_EXPR, "LOGIC_EXPR"}
};


constexpr char INDENT = '-';

class Node 
{
public:
    Node(const eSymbolName);
    Node(const eSymbolName, const std::string&);
    virtual ~Node() = default;

    std::string GetValue() const;
    eSymbolName GetName() const;
    
    virtual eDataType CheckWellFormedness(ScopedSymbolTable*) const;
    virtual void Print(const int) const;
    virtual bool Empty() const;
	virtual void Destroy();

private:
    eSymbolName mName;
    std::string mValue;
};