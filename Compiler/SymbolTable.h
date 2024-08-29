#pragma once
#include "ScopedSymbolTable.h"
#include "FunctionSignature.h"

class SymbolTable
{
public:
	static SymbolTable& GetInstance();
	~SymbolTable();

	void AddFunctionSymbol(const std::string&, ScopedSymbolTable*);
	eDataType GetReturnType(const std::string&) const;
	void AddFunctionSignature(const std::string&, const eDataType, const std::vector<eDataType>&);
	void ValidateArgumentTypes(const std::string&, const std::vector<eDataType>&) const;

	void Print() const;

private:
	SymbolTable() = default;
	SymbolTable(const SymbolTable&) = delete;
	SymbolTable& operator=(const SymbolTable&) = delete;

private:
	std::unordered_map<std::string, ScopedSymbolTable*> mFunctionScopeTables;
	std::unordered_map<std::string, FunctionSignature> mFunctionSignatures;
};