#include "FuncEdge.h"


static std::string 
createEdge( const std::string& a, const std::string& b )
{
	std::stringstream ss;
	ss << '\t' << a << " -> " << b << std::endl;
	return ss.str();
}

std::string 
CreateDFD::FuncEdge::output() const
{
	std::stringstream ss;
	ss << createEdge( inNode, func );
	ss << createEdge( func, outNode );
	return ss.str();
}
