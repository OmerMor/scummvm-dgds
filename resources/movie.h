/*
 * Movie.h
 *
 *  Created on: Jan 22, 2010
 *      Author: alex
 */

#ifndef DGDS_MOVIE_H_
#define DGDS_MOVIE_H_

#include "common/str.h"
#include "common/array.h"

#include "resource.h"

namespace Dgds {

typedef struct MovieChunk {
	uint32 code;
	Common::String name;
	Common::Array<int32> data;
} MovieChunk;

class Movie {
public:
	Movie(Resource *res);
	virtual ~Movie();

private:
	Common::String _version;
	uint16 _pages;
	Common::Array<MovieChunk *> _chunks;

}; // end of class Movie

} // end of namespace Dgds

#endif /* DGDS_MOVIE_H_ */
