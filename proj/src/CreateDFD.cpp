#include "CreateDFD.h"

#include <sstream>

std::string 
CreateDFD::convert( const std::string& in )
{
	std::stringstream ss;
	ss << "digraph mygraph {" << std::endl;
	ss << "\tA -> Test -> B" << std::endl;
	ss << "}" << std::endl;

	return ss.str();
}
