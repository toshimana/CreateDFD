#include "CreateDFD.h"
#include "CreateDFD_Impl.h"

static std::string
outputDot( const std::string& body )
{
	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << body;
	ss << "}" << std::endl;

	return ss.str();
}

std::string 
CreateDFD::convert( const std::string& in )
{
	FuncEdge fe;
	bool ret = CreateDFD::Impl::parse( in, fe );

	return outputDot( fe.output() );
}
