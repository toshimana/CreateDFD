#pragma once

#include "FuncEdge.h"

namespace CreateDFD
{
	namespace Impl
	{
		bool parse( const std::string& in, std::vector<FuncEdge>& edges );
	}
};