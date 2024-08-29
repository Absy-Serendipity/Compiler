#include "ScopedSymbolTable.h"


unsigned int ScopedSymbolTable::sOffset;

ScopedSymbolTable::ScopedSymbolTable(ScopedSymbolTable* outerSymbolTable) 
	: mOuterSymbolTable(outerSymbolTable)
{
	if (mOuterSymbolTable != nullptr) 
	{
		mOuterSymbolTable->mInnerSymbolTables.push_back(this);
	}
	
	// current table is a function scope symbol table
	// which means offset should be reset
	if (mOuterSymbolTable == nullptr) 
	{
		// $fp, $ra, RET
		sOffset = WORD_SIZE * 3;
	}
}

ScopedSymbolTable::~ScopedSymbolTable()
{
	for (auto& innerTable : mInnerSymbolTables) {
		delete innerTable;
	}
}

void ScopedSymbolTable::AddSymbol(const std::string& symbol, const eDataType dataType)
{
	if (mLocalSymbols.find(symbol) != mLocalSymbols.end()) 
	{
		throw std::runtime_error("Symbol: '" + symbol + "' already exists");
	}
	
	mLocalSymbols[symbol] = SymbolTableEntry{ dataType, ScopedSymbolTable::GetOffset() };
}

const eDataType ScopedSymbolTable::GetDataType(const std::string& symbol) const
{
	const auto itDataType = mLocalSymbols.find(symbol);
	if (itDataType == mLocalSymbols.end()) 
	{
		if (mOuterSymbolTable == nullptr) 
		{
			throw std::runtime_error("Symbol not found");
		}
		return mOuterSymbolTable->GetDataType(symbol);
	}
	return itDataType->second.DataType;
}

unsigned int ScopedSymbolTable::GetOffset() const
{
	uint16_t offset = sOffset;
	sOffset += WORD_SIZE;
	return offset;
}

void ScopedSymbolTable::Print() const
{
	for (const auto& [symbol, symbolEntry] : mLocalSymbols) 
	{
		std::cout << symbol << "\t" << STRING_DATA_TYPES.at(symbolEntry.DataType) << "\t" << symbolEntry.Offset << std::endl;
	}
	
	for (const auto& innerTable : mInnerSymbolTables) 
	{
		innerTable->Print();
	}
}