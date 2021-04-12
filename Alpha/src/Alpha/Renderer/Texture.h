#pragma once
#include <string>
#include "Alpha/Core.h"

namespace Alpha
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& filePath);
	};
<<<<<<< HEAD

	class TextureCubemap : public Texture
	{
	public:
		static Ref<TextureCubemap> Create(const std::array<std::string, 6>& filepaths);
		static Ref<TextureCubemap> Create(const std::string& filepath);
	};

	class Texture3D : public Texture
	{
	public:
		static Ref<Texture3D> Create(const std::string& filePath);
	};
=======
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
}

