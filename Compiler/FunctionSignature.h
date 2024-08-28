#pragma once
#include "eDataType.h"
#include <vector>


class FunctionSignature
{
public:
	FunctionSignature() : mReturnType(eDataType::Void) {};
	FunctionSignature(eDataType returnType, const std::vector<eDataType>& parameterTypes) : 
		mReturnType(returnType), mParameterTypes(parameterTypes) {}

	void AddParameterType(const eDataType);
	bool VerifyParameterTypes(const std::vector<eDataType>&) const;
	const eDataType GetReturnType() const;

private:
	eDataType mReturnType;
	std::vector<eDataType> mParameterTypes;
};

