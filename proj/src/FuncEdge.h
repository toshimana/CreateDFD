#pragma once

#include <string>
#include <sstream>

namespace CreateDFD
{
	struct FuncEdge
	{
		std::string func;
		std::string inNode;
		std::string outNode;

		std::string output() const;
	};
};
