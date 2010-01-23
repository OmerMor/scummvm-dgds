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

#include "common/system.h"

#include "dgds/resources/palette.h"

namespace Dgds {

bool Palette::init(Resource *res) {
	bool ret = false;

	Resource *resPAL = res->getSubResource("PAL:");
	if (resPAL) {
		ret = loadVGA(resPAL->getSubResource("VGA:"));
		delete resPAL;
	} else {
		warning("The resource doesn't contain a palette");
	}

	return ret;
}

bool Palette::loadVGA(Resource *resVGA) {
	bool ret = false;

	if (resVGA) {
		if (resVGA->size() == 768) {
			byte shift = 2;
			for (int i = 0; i < 256 * 4; i += 4) {
				_palette[i + 0] = resVGA->readByte() << shift;
				_palette[i + 1] = resVGA->readByte() << shift;
				_palette[i + 2] = resVGA->readByte() << shift;
				_palette[i + 3] = 255;
			}
			ret = true;
		} else {
			warning("Bad size for a VGA palette: %d", resVGA->size());
		}
		delete resVGA;
	} else {
		warning("The resource doesn't contain a VGA palette");
	}

	return ret;
}

void Palette::apply() {
	g_system->setPalette(_palette, 0, 256);
}

} // End of namespace Dgds
