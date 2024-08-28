#pragma once
#include "eDataType.h"
#include <unordered_map>
#include <string>
#include <iostream>

constexpr unsigned int WORD_SIZE = 4;

const std::unordered_map<eDataType, std::string> STRING_DATA_TYPES = {
	{eDataType::Int, "int"},
	{eDataType::Char, "char"},
	{eDataType::Bool, "bool"},
	{eDataType::Void, "void"}
};


class ScopedSymbolTable
{
private:
	typedef struct _SymbolTableEntry
	{
		eDataType DataType;
		unsigned int Offset;
	} SymbolTableEntry;

public:
	ScopedSymbolTable(ScopedSymbolTable* outerSymbolTable);
	void AddSymbol(const std::string&, const eDataType);
	const eDataType GetDataType(const std::string&) const;


	void Print() const;
private:

	unsigned int GetOffset() const;

private:
	ScopedSymbolTable* mOuterSymbolTable;
	std::unordered_map<std::string, SymbolTableEntry> mLocalSymbols;
	std::vector<ScopedSymbolTable*> mInnerSymbolTables;

	static unsigned int sOffset;
};


