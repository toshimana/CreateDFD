#include "FuncEdge.h"

#include <sstream>
#include <boost/foreach.hpp>

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
	BOOST_FOREACH( const std::string& node, inNodes ){
		ss << createEdge( node, func );
	}
	BOOST_FOREACH( const std::string& node, outNodes ){
		ss << createEdge( func, node );
	}
	return ss.str();
}
