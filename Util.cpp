#include "Util.h"




std::string Util::WChartToStdString( const wchar_t *s, char dfault, const std::locale& loc) {
	std::ostringstream stm;

	while( *s != L'\0' ) {
		stm << std::use_facet< std::ctype<wchar_t> >( loc ).narrow( *s++, dfault );
	}
	return stm.str();
}