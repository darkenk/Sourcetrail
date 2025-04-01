#ifndef REFRESH_INFO_H
#define REFRESH_INFO_H

#include <iosfwd>
#include <set>

#include "FilePath.h"

enum class RefreshMode
{
	NONE,
	UPDATED_FILES,
	UPDATED_AND_INCOMPLETE_FILES,
	ALL_FILES
};

std::wostream &operator << (std::wostream &, RefreshMode);

struct RefreshInfo
{
	std::set<FilePath> filesToIndex;
	std::set<FilePath> filesToClear;
	std::set<FilePath> nonIndexedFilesToClear;

	RefreshMode mode = RefreshMode::NONE;
	bool shallow = false;
};

#endif	  // REFRESH_INFO_H
