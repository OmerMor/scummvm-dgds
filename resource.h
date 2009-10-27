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

#ifndef DGDS_RESOURCE_H
#define DGDS_RESOURCE_H

#include "common/stream.h"
#include "common/hash-str.h"

namespace Dgds {

struct ResourceInfo {
	uint32 offset;
	uint32 size;
	bool hasSubres;
};

typedef Common::HashMap<Common::String, ResourceInfo, Common::IgnoreCase_Hash, Common::IgnoreCase_EqualTo> SubResources;

class Resource : public Common::SeekableReadStream {
public:
	Resource(Common::SeekableReadStream *stream, bool hasSubres);
	~Resource();

	Resource *getSubResource(Common::String const &tag);

	void dump(Common::String const &outFilename, bool dumpSubres);

	// SeekableReadStream members
	bool   eos() const { return _stream->eos(); }
	uint32 read(void *dataPtr, uint32 dataSize) { return _stream->read(dataPtr, dataSize); }
	int32  pos() const { return _stream->pos(); }
	int32  size() const { return _stream->size(); }
	bool   seek(int32 offset, int whence = SEEK_SET) { return _stream->seek(offset, whence); }

private:
	Resource *getSubResource(ResourceInfo const &subResourceInfo);

	Common::SeekableReadStream *_stream;

	SubResources _subResources;
};

} // End of namespace Dgds

#endif // DGDS_RESOURCE_H
