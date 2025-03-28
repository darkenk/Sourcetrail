#ifndef STORAGE_COMPONENT_ACCESS_H
#define STORAGE_COMPONENT_ACCESS_H

#include "AccessKind.h"
#include "Id.h"

struct StorageComponentAccess
{
	StorageComponentAccess(): nodeId(0), type(AccessKind::NONE) {}

	StorageComponentAccess(Id nodeId, AccessKind type): nodeId(nodeId), type(type) {}

	bool operator<(const StorageComponentAccess& other) const
	{
		return nodeId < other.nodeId;
	}

	Id nodeId;
	AccessKind type;
};

#endif	  // STORAGE_COMPONENT_ACCESS_H
