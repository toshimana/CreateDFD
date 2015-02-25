#pragma once

#include <string>
#include <vector>

namespace CreateDFD
{
	struct FuncEdge
	{
		std::string func;
		std::vector<std::string> inNodes;
		std::vector<std::string> outNodes;

		std::string output() const;
	};
};
