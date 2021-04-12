#pragma once

#include "Alpha/Renderer/Buffer.h"
#include <memory>

namespace Alpha
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>> GetVertexBuffers() = 0;
		virtual const Ref<IndexBuffer> GetIndexbuffer() = 0;

		static VertexArray* Create();
	};
}