/*
 * TaggedResource.cpp
 *
 *  Created on: Jan 23, 2010
 *      Author: alex
 */

#include "dgds/resources/taggedresource.h"

namespace Dgds {

TaggedResource::TaggedResource() {
	// TODO Auto-generated constructor stub

}

TaggedResource::~TaggedResource() {
	// TODO Auto-generated destructor stub
}

bool TaggedResource::load(ResourceManager *resman, Common::String name) {
	_filename = name;
	Resource *res = resman->getResource(name);
	bool ret = false;

	if (res) {
		ret = init(res);
		delete res;
	} else
		warning ("Couldn't find [%s]", name.c_str());

	return ret;
}

} // end of namespace Dgds
