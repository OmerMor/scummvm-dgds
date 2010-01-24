/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "dgds/resources/movie.h"
#include "dgds/compression.h"

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
	Common::SeekableReadStream *decomp = decompLZW(tt3, size);

	/*
	Resource *r = new Resource(decomp, false);
	r->dump(Common::String(getName()) + Common::String(".TT3.LZW"), false);
	delete r;
	*/

	debugC(kDebugResources, "[%s] Version[%s] Pages[%d]", getName(), _version.c_str(), _pages);

	delete ver;
	delete pag;
	delete tt3;
	delete decomp;

	return ret;
}

} // end of namespace Dgds
