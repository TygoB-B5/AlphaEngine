#include "appch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Alpha
{
	static GLenum ShaderDataTypeToOpenglBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Alpha::ShaderDataType::Float:  return GL_FLOAT;
		case Alpha::ShaderDataType::Float2: return GL_FLOAT;
		case Alpha::ShaderDataType::Float3: return GL_FLOAT;
		case Alpha::ShaderDataType::Float4: return GL_FLOAT;
		case Alpha::ShaderDataType::Mat3:   return GL_FLOAT;
		case Alpha::ShaderDataType::Mat4:   return GL_FLOAT;
		case Alpha::ShaderDataType::Int:    return GL_INT;
		case Alpha::ShaderDataType::Int2:   return GL_INT;
		case Alpha::ShaderDataType::Int3:   return GL_INT;
		case Alpha::ShaderDataType::Int4:   return GL_INT;
		case Alpha::ShaderDataType::Bool:   return GL_BOOL;
		}

		AP_CORE_ASSERT(false, "Unknown Shadertype!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RenderID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RenderID);
		vertexBuffer->Bind();

		AP_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenglBaseType(element.Type),
				element.Normalised ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)(uint64_t)element.Offset);

			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RenderID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}