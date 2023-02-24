#pragma once
#include "jsEngine.h"
#include "jsResource.h"

namespace js
{
	class Resources
	{
	public:
		typedef std::map<std::wstring, std::shared_ptr<Resource>>::iterator ResourceIter;


		template <typename T>
		static std::shared_ptr<T> Find(const std::wstring& key)
		{
			ResourceIter iter = mResources.find(key);

			if (iter != mResources.end())
				return std::dynamic_pointer_cast<T>(iter->second);

			return nullptr;
		}


		template<typename T>
		static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path)
		{
			std::shared_ptr<T> resource = Resources::Find<T>(key);
			
			if (nullptr != resource)
				return resource;

			resource = std::make_shared<T>();
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Image Load Failed!!", L"Error", MB_OK);
				return nullptr;
			}

			resource->SetKey(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, std::dynamic_pointer_cast<Resource>(resource)));

			return resource;
		}


		template <typename T>
		static void Insert(const std::wstring& key, std::shared_ptr<T> resource)
		{
			if (nullptr == resource || key == L"")
				return;

			mResources.insert(std::make_pair(key, std::dynamic_pointer_cast<Resource>(resource)));
		}

	private:
		Resources() = delete;
		~Resources() = delete;

	private:
		static std::map<std::wstring, std::shared_ptr<Resource>> mResources;
	};
}