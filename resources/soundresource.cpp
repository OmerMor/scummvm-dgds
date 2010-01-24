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

#include "dgds/resources/soundresource.h"

namespace Dgds {

SoundResource::SoundResource() {
	// TODO Auto-generated constructor stub

}

SoundResource::~SoundResource() {
	_tags.clear();
}

bool SoundResource::init(Resource *res) {
	bool ret = false;

	Resource *snd = res->getSubResource("SND:");

	if (snd == NULL)
		return ret;

	Resource *dat = snd->getSubResource("DAT:");
	Resource *inf = snd->getSubResource("INF:");
	Resource *tag = snd->getSubResource("TAG:");
	Resource *fnm = snd->getSubResource("FNM:");

	if (dat == NULL || inf == NULL || tag == NULL || fnm == NULL)
		return ret;

	tag->seek(0);
	uint16 tagcount = tag->readUint16LE();

	for (uint16 i = 0; i < tagcount; i++) {
		uint16 tagid = tag->readUint16LE();
		Common::String tagval = tag->to_s(false);

		ResourceEntry entry;
		entry.id   = tagid;
		entry.name = tagval;

		_tags.setVal(tagid, entry);
	}
	delete tag;

	// XXX there's a VERY good chance that the FNM tag processing
	// can be skipped entirely, as it looks like (A) the filenames
	// are mapped in the same order they appear in the TAG list, and
	// (B) each sound resource is essentially the tag name + ".SND"
	fnm->seek(0);
	uint16 fnmcount = fnm->readUint16LE();
	for (uint16 j = 0; j < fnmcount; j++) {
		uint16 fnmid = fnm->readUint16LE();
		_tags[fnmid].filename = fnm->to_s(false);
	}
	delete fnm;

	/* XXX print list of resources
	ResourceTags::const_iterator iter  = _tags.begin();
	while (iter != _tags.end()) {
		printf("%d:%s:%s\n", iter->_value.id, iter->_value.name.c_str(), iter->_value.filename.c_str());
		++iter;
	}
	*/

	// XXX skipping TAG_INF for the sound resource as it appears
	// to contain nothing more than a list of the sound resource
	// id values, which we've already parsed when we processed
	// the TAG_TAG data
	delete inf;

	// TODO figure out what the TAG_DAT contains, as we've already got
	// a list of the sound resource (files) that we'll need to use along
	// with each resource entry
	delete dat;


	return true; //ret;
}

} // end of namespace Dgds
