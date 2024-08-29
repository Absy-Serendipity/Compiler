#include "SymbolTable.h"

SymbolTable& SymbolTable::GetInstance()
{
	static SymbolTable symbolTable;
	return symbolTable;
}


SymbolTable::~SymbolTable()
{
	for (const auto& [functionID, functionScopeTable] : mFunctionScopeTables) 
	{
		delete functionScopeTable;
	}
}

void SymbolTable::AddFunctionSymbol(const std::string& identifier, ScopedSymbolTable* functionScopeTable)
{
	mFunctionScopeTables[identifier] = functionScopeTable;
}

void SymbolTable::Print() const
{
	for (const auto& [functionID, functionLayout] : mFunctionScopeTables) 
	{
		std::cout << "Function ID: " << functionID << std::endl;
		std::cout << "SYMBOL\tTYPE\tOFFSET" << std::endl;
		std::cout << "$bp" << "\t" << "" << "\t" << 0 << std::endl;
		std::cout << "$ra" << "\t" << "" << "\t" << WORD_SIZE << std::endl;
		std::cout << "[RET]" << "\t" << "" << "\t" << (WORD_SIZE << 1) << std::endl;

		functionLayout->Print();
		std::cout << std::endl;
	}
}



eDataType SymbolTable::GetReturnType(const std::string& functionName) const
{
	const auto& itReturnType = mFunctionSignatures.find(functionName);
	if (itReturnType == mFunctionSignatures.end()) 
	{
		throw std::runtime_error("Function " + functionName + " is not defined");
	}
	return itReturnType->second.GetReturnType();
}
void SymbolTable::AddFunctionSignature(const std::string& functionName, const eDataType returnType, const std::vector<eDataType>& parameterTypes)
{
	if (mFunctionSignatures.find(functionName) != mFunctionSignatures.end()) 
	{
		throw std::runtime_error("Symbol: '" + functionName + "' already exists");
	}
	mFunctionSignatures[functionName] = FunctionSignature(returnType, parameterTypes);

}
void SymbolTable::ValidateArgumentTypes(const std::string& functionName, const std::vector<eDataType>& argumentTypes) const
{
	mFunctionSignatures.at(functionName).VerifyParameterTypes(argumentTypes);

	const auto& itFunctionSymbolEntry = mFunctionSignatures.find(functionName);
	if (itFunctionSymbolEntry == mFunctionSignatures.end()) 
	{
		throw std::runtime_error("Symbol not found");
	}
	if (!itFunctionSymbolEntry->second.VerifyParameterTypes(argumentTypes)) 
	{
		throw std::runtime_error("Invalid argument types");
	}
}