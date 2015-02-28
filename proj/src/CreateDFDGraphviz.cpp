#include "CreateDFDGraphviz.h"

#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include "CreateDFD.h"

namespace fs = boost::filesystem;

const fs::path DOTPATH( "C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe" );

namespace CreateDFDGraphviz
{
	struct TempFile
	{
		fs::path path;

		TempFile( const fs::path& _path )
			: path( _path ){}

		~TempFile()
		{
			fs::remove( path );
		}
	};
}

int
CreateDFDGraphviz::createDFD( const std::string& inFile )
{
	std::string str;
	{
		std::ifstream ifs( inFile.c_str() );
		if ( !ifs.is_open() ) {
			return -1;
		}

		try {
			str = std::string( (std::istreambuf_iterator<char>( ifs )), std::istreambuf_iterator<char>() );
		}
		catch ( ... ) {
			return -1;
		}
	}

	std::string out = CreateDFD::convert( str );

	fs::path inPath( inFile );
	fs::path rootDir = inPath.parent_path();
	TempFile dotPath( rootDir / fs::unique_path() );
	fs::path outFile( inFile );
	outFile.replace_extension( "pdf" );

	{
		std::ofstream ofs( dotPath.path.string().c_str() );
		ofs << out;
	}

	std::stringstream cmd;
	cmd << DOTPATH << ' ';
	cmd << "-Kdot -Tpdf ";
	cmd << dotPath.path.string() << " -o " << outFile.string();
	return system( cmd.str().c_str() );
}