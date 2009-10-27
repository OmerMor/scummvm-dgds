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
#include "graphics/surface.h"

#include "dgds/test.h"

namespace Dgds {

Test::Test(ResourceManager *resMgr) {
	_resMgr = resMgr;

	if(!_palette.load(_resMgr, "DYNAMIX.PAL")) {
		printf("palette error\n");
	}
	_palette.apply();

	_step = 0;
	_resIter = _resMgr->_resourceFiles.begin();
	next();
}

void Test::drawBg() {
	Graphics::Surface *screen = g_system->lockScreen();

	for (int i = 0; i < 256; i++) {
 		screen->vLine(i, 0, 199, i);
	}

	g_system->unlockScreen();
}

Common::String Test::getNext(Common::String ext) {
	Common::String name;

	while (!name.size() && _resIter != _resMgr->_resourceFiles.end()) {
		if (_resIter->_key.hasSuffix(ext.c_str()))
			name = _resIter->_key;

		++_resIter;
	}

	return name;
}

void Test::next() {
	Common::String name;

	drawBg();

	name = getNext("FNT");
	printf("%s\n", name.c_str());
	if(!_fnt.load(_resMgr, name)) {
		printf("font error\n");
	} else {
		Graphics::Surface *screen = g_system->lockScreen();
		_fnt.drawString(screen, 10, 10, name.c_str(), 10);
		_fnt.drawString(screen, 5, 20, "Dynamix Game Development System font example", 14);
		_fnt.show(screen, 5, 40, 14);
		g_system->unlockScreen();
	}

	/*
	//name = "DYNAMIX.PAL";
	name = getNext("PAL");
	printf("%s\n", name.c_str());
	if(!_palette.load(_resMgr, name)) {
		printf("palette error\n");
	} else {
		_palette.apply();
	}


	/*
	name = getNext("BMP");
	printf("%s\n", name.c_str());
	if(!_bmp.load(_resMgr, name)) {

		printf("bmp error\n");
	}
	*/

	g_system->updateScreen();
}

} // End of namespace Dgds
