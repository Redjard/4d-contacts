#pragma once

#include "4dm.h"

namespace fdm 
{
	class ResourceManager 
	{
	public:
		inline static std::unordered_map<msvc_string,Tex2D *>* textures = reinterpret_cast<std::unordered_map<msvc_string,Tex2D *>*>((base + 0x2C40F0));

		inline static const Tex2D* get(const std::string& filename, const std::string& folderOverride)
		{
			std::string path = (std::filesystem::path(folderOverride) / filename).string();

			if (textures->contains(path))
				return textures->at(path);

			Tex2D* tex = new Tex2D();
			tex->ID = 0;
			tex->height = 0;
			tex->width = 0;
			tex->target = GL_TEXTURE_2D;

			if (!tex->load(path))
			{
				delete tex;
				tex = nullptr;
			}

			textures->insert({ path, tex });
			return tex;
		}

		inline static const Tex2D* get(const std::string& filename, bool modFolder = false)
		{
			if (modFolder)
				return get(filename, fdm::getModPath(fdm::modID));

			return reinterpret_cast<const Tex2D * (__fastcall*)(const std::string&)>(
					getFuncAddr((int)Func::ResourceManager::get)
					)(filename);
		}
		
		inline static bool loadArrayTexture(const msvc_string& filename, int cols, int rows) 
		{
			return reinterpret_cast<bool (__fastcall*)(const msvc_string& filename, int cols, int rows)>(getFuncAddr((int)Func::ResourceManager::loadArrayTexture))(filename, cols, rows);
		}
	};
}
