#include "CreateDFDMain.h"
#include "CreateDFDGraphviz.h"

extern "C" int CreateDFDMain( int argc, char* argv[] )
{

	return CreateDFDGraphviz::createDFD( argv[1] );
}
