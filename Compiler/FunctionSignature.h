#pragma once
#include "eDataType.h"
#include <vector>


class FunctionSignature
{
public:
	FunctionSignature();
	FunctionSignature(const eDataType, const std::vector<eDataType>&);
	~FunctionSignature() = default;

	void AddParameterType(const eDataType);
	bool VerifyParameterTypes(const std::vector<eDataType>&) const;
	const eDataType GetReturnType() const;

private:
	eDataType mReturnType;
	std::vector<eDataType> mParameterTypes;
};

