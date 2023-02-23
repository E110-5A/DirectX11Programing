#pragma once
#include "jsEntity.h"

namespace js
{
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& strPath) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }

		void SetKey(const std::wstring& strKey) { mKey = strKey; }
		void SetPath(const std::wstring& strPath) { mPath = strPath; }

	private:
		std::wstring mKey;
		std::wstring mPath;
	};
}