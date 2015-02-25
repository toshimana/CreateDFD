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

		FuncEdge(){};
		FuncEdge( const std::string& _func, const std::string& _in, const std::string& _out )
			: func( _func ), inNode( _in ), outNode( _out ) {}

		std::string output() const
		{
			std::stringstream ss;
			ss << '\t';
			ss << inNode  << " -> ";
			ss << func    << " -> ";
			ss << outNode << std::endl;
			return ss.str();
		}
	};
};
