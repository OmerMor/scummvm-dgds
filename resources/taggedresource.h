/*
 * TaggedResource.h
 *
 *  Created on: Jan 23, 2010
 *      Author: alex
 */

#ifndef DGDS_TAGGEDRESOURCE_H_
#define DGDS_TAGGEDRESOURCE_H_

#include "dgds/resourcemanager.h"

namespace Dgds {

enum ResourceTag {
	TAG_ADS = 0x3a534441,
	TAG_BMP = 0x3a504d42,
	TAG_FNT = 0x3a544e46,
	TAG_INF = 0x3a464e49,
	TAG_PAG = 0x3a474150,
	TAG_PAL = 0x3a4c4150,
	TAG_RES = 0x3a534552,
	TAG_SCR = 0x3a524353,
	TAG_SND = 0x3a444e53,
	TAG_TAG = 0x3a474154,
	TAG_TT3 = 0x3a335454,
	TAG_VER = 0x3a524556,
	TAG_VGA = 0x3a414756
};

class TaggedResource {
public:
	TaggedResource();
	virtual ~TaggedResource();

	/**
	 * Load the filename from the resourcemanager
	 */
	bool load(ResourceManager *resman, Common::String name);


protected:
	const char *name() { return _filename.c_str(); }

	/**
	 * Initialize the TaggedResource to the base resource
	 * instance and do any class-specific initialization
	 */
	virtual bool init(Resource *res) = 0;

private:
	// XXX this is just here for convenience, so that
	// when we load() a resource, we can keep an internal reference
	// to the filename (mostly for debug output and such)
	Common::String _filename;

}; // end of class TaggedResource

} // end of namespace Dgds

#endif /* DGDS_TAGGEDRESOURCE_H_ */
