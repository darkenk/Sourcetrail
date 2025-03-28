#ifndef TEST_STORAGE_H
#define TEST_STORAGE_H

#include <FilePath.h>
#include <Storage.h>
#include <StorageSourceLocation.h>

#include <boost/filesystem.hpp>

#include <memory>
#include <string>
#include <vector>

class TestStorage
{
public:
	static std::shared_ptr<TestStorage> create(std::shared_ptr<const Storage> storage);

	std::vector<std::wstring> errors;
	std::vector<std::wstring> qualifiers;

	std::vector<std::wstring> packages;
	std::vector<std::wstring> typedefs;
	std::vector<std::wstring> builtinTypes;
	std::vector<std::wstring> classes;
	std::vector<std::wstring> unions;
	std::vector<std::wstring> interfaces;
	std::vector<std::wstring> records;
	std::vector<std::wstring> annotations;
	std::vector<std::wstring> enums;
	std::vector<std::wstring> enumConstants;
	std::vector<std::wstring> functions;
	std::vector<std::wstring> fields;
	std::vector<std::wstring> globalVariables;
	std::vector<std::wstring> methods;
	std::vector<std::wstring> namespaces;
	std::vector<std::wstring> modules;
	std::vector<std::wstring> structs;
	std::vector<std::wstring> macros;
	std::vector<std::wstring> typeParameters;
	std::vector<std::wstring> localSymbols;
	std::set<std::wstring> files;
	std::vector<std::wstring> comments;

	std::vector<std::wstring> inheritances;
	std::vector<std::wstring> overrides;
	std::vector<std::wstring> calls;
	std::vector<std::wstring> usages;	   // for variables
	std::vector<std::wstring> typeUses;	   // for types
	std::vector<std::wstring> macroUses;
	std::vector<std::wstring> annotationUses;
	std::vector<std::wstring> typeArguments;
	std::vector<std::wstring> templateSpecializations;
	std::vector<std::wstring> includes;
	std::vector<std::wstring> imports;

	std::vector<std::string> m_lines;

private:
	static std::wstring nodeTypeToString(NodeKind nodeType);
	static std::wstring edgeTypeToString(Edge::EdgeType edgeType);
	static std::wstring addLocationStr(const std::wstring& locationStr, const StorageSourceLocation& loc);
	static std::wstring addFileName(const std::wstring& locationStr, const FilePath& filePath);
	static bool containsLocation(const StorageSourceLocation& out, const StorageSourceLocation& in);
	
	std::vector<std::wstring>* getBinForNodeType(NodeKind nodeType);
	std::vector<std::wstring>* getBinForEdgeType(Edge::EdgeType edgeType);
	void addLine(const std::wstring& message);
};

#endif	  // TEST_STORAGE_H
