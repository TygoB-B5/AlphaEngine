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

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() = 0;
		virtual const std::shared_ptr<IndexBuffer> GetIndexbuffer() = 0;

		static VertexArray* Create();
	};
}