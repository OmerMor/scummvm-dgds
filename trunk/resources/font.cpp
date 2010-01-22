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

#include "dgds/resources/font.h"

#include "dgds/compression.h"

namespace Dgds {

Font::Font() :
	_offsets(NULL), _widths(NULL), _faces(NULL) {
}

Font::~Font() {
	empty();
}

bool Font::load(ResourceManager *resman, Common::String const &name) {
	bool ret = false;

	Resource *res = resman->getResource(name);

	if (res) {
		ret = loadFNT(res->getSubResource("FNT:"));
		delete res;
	} else {
		warning("Couldn't find the resource");
	}

	return ret;
}

void Font::empty() {
	if (_offsets) {
		delete [] _offsets;
		_offsets = NULL;
	}
	if (_widths) {
		delete [] _widths;
		_widths = NULL;
	}
	if (_faces) {
		delete [] _faces;
		_faces = NULL;
	}
}

bool Font::loadFNT(Resource *resFNT) {
	empty();

	bool ret = false;

	if (resFNT) {
		_sizex = resFNT->readByte();
		if (_sizex == 0xFF) {
			// Complex font
			_sizex = resFNT->readByte();
			_sizey = resFNT->readByte();
			_lineHeight = resFNT->readByte(); // sure?
			_firstChar = resFNT->readByte();
			_numChars = resFNT->readByte();
			int16 size = resFNT->readUint16LE();

			byte comprMethod = resFNT->readByte();
			int32 size2 = resFNT->readUint32LE();
			assert (comprMethod == 2);
			assert (size == size2);

			Common::SeekableReadStream *decomp = decompLZW(resFNT, size2);

			// Get the beginning of each character
			_offsets = new uint16[_numChars];
			for (int i = 0; i < _numChars; i++) {
				_offsets[i] = decomp->readUint16LE();
				//if (_offsets[i] != i * 8)
					//printf("WARNING: got %d expected %d\n", size, i * 8);
			}

			// Get the width of the characters
			_widths = new uint8[_numChars];
			decomp->read(_widths, _numChars);

			// Read the face of the characters
			_faces = new byte[_sizey * _numChars];
			decomp->read(_faces, _sizey * _numChars);
			delete decomp;
			ret = true;

		} else {
			// Simple font
			_sizey = resFNT->readByte();
			_firstChar = resFNT->readByte();
			_numChars = resFNT->readByte();

			_faces = new byte[_sizey * _numChars];
			resFNT->read(_faces, _sizey * _numChars);
			ret = true;
		}
		delete resFNT;
		printf("size(%dx%d) first(%d) number(%d)\n", _sizex, _sizey, _firstChar, _numChars);
	} else {
		warning("The resource doesn't contain a font");
	}

	return ret;
}

bool Font::hasChar(char c) {
	return (c >= _firstChar && c <= _firstChar + _numChars);
}

uint16 Font::getCharOffset(char c) {
	if (!hasChar(c))
		return 0;

	if (!_offsets) {
		// Simple font
		return (c - _firstChar) * _sizey;
	} else {
		// Complex font
		return _offsets[c - _firstChar];
	}
}

uint8 Font::getCharWidth(char c) {
	if (!hasChar(c))
		return 0;

	if (!_widths) {
		// Simple font
		return _sizex;
	} else {
		// Complex font
		return _widths[c - _firstChar];
	}
}

uint8 Font::getLineHeight(void) {
	if (!_widths) {
		// Simple font
		return _sizey + 1;
	} else {
		// Complex font
		return _lineHeight + 1;
	}
}

bool Font::drawChar(Graphics::Surface *surf, int screenx, int screeny, char c, int color) {
	if (!_faces)
		return false;

	if (!hasChar(c))
		return false;

	byte* area = (byte*)surf->getBasePtr(screenx, screeny);
	uint16 offset = getCharOffset(c);

	for (int y = 0; y < _sizey; y++, offset++) {
		int bit = 0;
		byte line;
		for (int x = 0; x < _sizex && bit < 8; x++, bit++) {
			if (bit == 0)
				line = _faces[offset];

			if (line & (1 << (7 - bit)))
				area[x + y * surf->pitch] = color;

			if (bit == 7 && getCharWidth(c) > x + 1) {
				bit = -1;
				offset++;
			}
		}
	}

	return true;
}

bool Font::drawString(Graphics::Surface *surf, int screenx, int screeny, const char *str, int color) {
	int len = strlen(str);
	bool ret = true;

	for (int i = 0; i < len; i++) {
		ret &= drawChar(surf, screenx, screeny, str[i], color);
		screenx += getCharWidth(str[i]);
	}

	return ret;
}

void Font::show(Graphics::Surface *surf, int screenx, int screeny, int color) {
	int curx = screenx;
	for (int i = 0; i < _numChars; i++) {
		drawChar(surf, curx, screeny, i + _firstChar, color);
		curx += getCharWidth(i + _firstChar);
		if (curx > 310) {
			curx = screenx;
			screeny += getLineHeight();
		}
	}
}

} // End of namespace Dgds
