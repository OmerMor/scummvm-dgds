/*
 * Movie.cpp
 *
 *  Created on: Jan 22, 2010
 *      Author: alex
 */

#include "dgds/resources/movie.h"
#include "dgds/compression.h"
#include "dgds/dgds.h"

#include "common/debug.h"

namespace Dgds {

Movie::Movie() {
}

Movie::~Movie() {
	// TODO Auto-generated destructor stub
}

bool Movie::init(Resource *res) {
	bool ret = false;

	Resource *ver = res->getSubResource("VER:");
	if (!ver)
		error("VER tag not found for Movie Resource");
	Resource *pag = res->getSubResource("PAG:");
	if (!pag)
		error("PAG tag not found for Movie Resource");
	Resource *tt3 = res->getSubResource("TT3:");
	if (!tt3)
		error ("TT3 tag not found for Movie Resource");

	_version = ver->to_s();
	pag->seek(0);
	_pages   = pag->readUint16LE();

	tt3->seek(1);
	uint32 size = tt3->readUint32LE();
	//Common::SeekableReadStream *decomp = decompRLE(tt3, size);

	debugC(kDebugResources, "[%s] Version[%s] Pages[%d]", name(), _version.c_str(), _pages);

	return ret;
}

} // end of namespace Dgds
