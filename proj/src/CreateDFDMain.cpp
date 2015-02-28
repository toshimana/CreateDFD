#include "CreateDFDMain.h"
#include "CreateDFDGraphviz.h"

#include <glog/logging.h>

namespace CreateDFDMain_Impl
{
	class GoogleLogging
	{
	public:
		static void init( const char* argv0 )
		{
			static GoogleLogging p( argv0 );
		}

	private:
		GoogleLogging( const char* argv0 )
		{
			google::InitGoogleLogging( argv0 );
		}
	};
}

extern "C" int CreateDFDMain( int argc, char* argv[] )
{
	CreateDFDMain_Impl::GoogleLogging::init( argv[0] );

	if ( argc != 2 ){
		LOG( ERROR ) << "ERROR : Num Of Arguments. expect : 1, actual : " << (argc-1);
		return -1;
	}
	return CreateDFDGraphviz::createDFD( argv[1] );
}
