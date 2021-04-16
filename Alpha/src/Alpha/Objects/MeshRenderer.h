#pragma once
#include "Alpha/Core.h"
#include "Component.h"
#include "Alpha/Renderer/Materials/Material.h"
#include "Alpha/Renderer/VertexArray.h"
#include "Alpha/Renderer/Buffer.h"

namespace Alpha
{
	class Mesh
	{
	public:
		void SetVertices(const std::vector<float>& vertices) { m_Vertices = vertices; }
		void SetIndices(const std::vector<uint32_t>& indices) { m_Indices = indices; }

		const std::vector<float>& GetVertices() const { return m_Vertices; }
		const std::vector<uint32_t>& GetIndices() const { return m_Indices; }
		const void LoadMeshFromFile(const std::string& filepath);
		const bool IsLoaded() const { return m_IsLoaded; }

	private:
		std::vector<float> m_Vertices;
		std::vector<uint32_t> m_Indices;
		bool m_IsLoaded = false;
	};

	class MeshRenderer : public Component
	{
	public:
		virtual std::string GetTypeName() const override { return "MeshRenderer"; }
		static std::string GetStaticName() { return "MeshRenderer"; }

	public:
		void SetMesh(const Ref<Mesh>& mesh) { m_Mesh = mesh; }
		void SetMaterial(const Ref<Material>& material);

		const void InitMesh();
		const bool IsReadyToInit();

		const bool IsInitialized() const { return m_IsInitialized; }
		const Ref<Mesh>& GetMesh() const { return m_Mesh; }
		const Ref<Material>& GetMaterial() const { return m_Material; }
		const Ref<VertexArray>& GetVertexArray() const { return m_VertexArray; }

	private:
		bool m_IsInitialized = false;
		Ref<Mesh> m_Mesh = nullptr;
		Ref<Material> m_Material = nullptr;

		Ref<IndexBuffer> m_IndexBuffer = nullptr;
		Ref<VertexBuffer> m_VertexBuffer = nullptr;
		Ref<VertexArray> m_VertexArray = nullptr;
	};
}