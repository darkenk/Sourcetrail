#ifndef LANGUAGE_TYPE_H
#define LANGUAGE_TYPE_H

#include "SourceGroupType.h"

#include <QMetaType>

#include <string>

enum class LanguageType
{
	UNKNOWN,
#if BUILD_CXX_LANGUAGE_PACKAGE
	CXX,
	C,
#endif
#if BUILD_JAVA_LANGUAGE_PACKAGE
	JAVA,
#endif
#if BUILD_PYTHON_LANGUAGE_PACKAGE
	PYTHON,
#endif
	CUSTOM
};

Q_DECLARE_METATYPE(LanguageType)

std::string languageTypeToString(LanguageType t);

LanguageType getLanguageTypeForSourceGroupType(SourceGroupType t);

#endif
