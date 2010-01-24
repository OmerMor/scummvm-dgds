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

#ifndef DGDS_ANIMATION_H_
#define DGDS_ANIMATION_H_

#include "dgds/resources/taggedresource.h"

namespace Dgds {

struct AnimationInfo {
	Common::String name;
	Common::String resource;
};

typedef Common::HashMap<Common::String, AnimationInfo, Common::IgnoreCase_Hash, Common::IgnoreCase_EqualTo> AnimationMap;

class Animation: public TaggedResource {
public:
	Animation();
	virtual ~Animation();

protected:
	bool init(Resource *res);

private:
	Resource *_script;
	Common::String _version;

	AnimationMap _animationMap;

}; // end of class Animation

} // end of namespace Dgds

#endif /* DGDS_ANIMATION_H_ */
