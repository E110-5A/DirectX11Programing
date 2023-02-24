#pragma once
#include "jsEntity.h"

using namespace js::enums;

namespace js
{
	class Resource : public Entity
	{
	public:
		Resource(eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& strPath) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }

		void SetKey(const std::wstring& strKey) { mKey = strKey; }
		void SetPath(const std::wstring& strPath) { mPath = strPath; }

	private:
		std::wstring mKey;
		std::wstring mPath;
		eResourceType mType;
	};
}