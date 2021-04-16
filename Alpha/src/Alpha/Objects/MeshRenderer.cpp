#include "appch.h"
#include "MeshRenderer.h"
#include <stdio.h>

namespace Alpha
{
	const void Mesh::LoadMeshFromFile(const std::string& filepath)
	{
		m_IsLoaded = false;

		const size_t found = filepath.find_last_of(".");
		const std::string fileType = filepath.substr(found + 1);

		AP_CORE_ASSERT((fileType == "obj"), "No filetype other than .obj supported for now")

		std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> tempVertices;
		std::vector<glm::vec2> tempTexcoords;
		std::vector<glm::vec3> tempNormals;

		FILE* file = fopen(filepath.c_str(), "r");

		AP_CORE_ASSERT(!(file == NULL), "Could not open file!")
			AP_CORE_INFO("Reading file: {0}", filepath);

		while (true)
		{
			char lineHeader[128] = { 0 };

			int res = fscanf(file, "%s", lineHeader);

			if (res == EOF)
				break;

			if (strcmp(lineHeader, "v") == NULL)
			{
				glm::vec3 vertex = glm::vec3(0);
				auto a = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				tempVertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == NULL)
			{
				glm::vec2 uv = glm::vec3(0);
				auto a = fscanf(file, "%f %f\n", &uv.x, &uv.y);
				tempTexcoords.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == NULL)
			{
				glm::vec3 normal = glm::vec3(0);
				auto a = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				tempNormals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == NULL)
			{
				unsigned int vertexIndex[3] = {}, uvIndex[3] = {}, normalIndex[3] = {};
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				AP_CORE_ASSERT((matches == 9), "Indices could not be read! Model probably not triangulated")

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		fclose(file);

		AP_CORE_ASSERT(!(vertexIndices.empty()), "File does not contain correct data!")

		std::vector<float> finalVertices;
		std::vector<uint32_t> finalIndices;

		for (uint32_t i = 0; i < vertexIndices.size(); i++)
		{
			finalIndices.push_back(i);

			finalVertices.push_back(tempVertices[vertexIndices[i] - 1].x);
			finalVertices.push_back(tempVertices[vertexIndices[i] - 1].y);
			finalVertices.push_back(tempVertices[vertexIndices[i] - 1].z);

			finalVertices.push_back(tempTexcoords[uvIndices[i] - 1].x);
			finalVertices.push_back(tempTexcoords[uvIndices[i] - 1].y);

			finalVertices.push_back(tempNormals[normalIndices[i] - 1].x);
			finalVertices.push_back(tempNormals[normalIndices[i] - 1].y);
			finalVertices.push_back(tempNormals[normalIndices[i] - 1].z);
		}

		SetVertices(finalVertices);
		SetIndices(finalIndices);

		m_IsLoaded = true;
	}

	const void MeshRenderer::InitMesh()
	{
		auto& vertices = m_Mesh->GetVertices();

		if (vertices.empty())
			return;

		std::vector<uint32_t> indices = m_Mesh->GetIndices();

		m_VertexBuffer.reset(VertexBuffer::Create((float*)&vertices[0], (uint32_t)vertices.size() * 4));
		m_VertexBuffer->SetLayout(
			{
				{ShaderDataType::Float3, "u_Position" },
				{ShaderDataType::Float2, "u_TexCoord" },
				{ShaderDataType::Float3, "u_Normal" }
			});

		m_IndexBuffer.reset(IndexBuffer::Create((uint32_t*)&indices[0], (uint32_t)indices.size()));

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_IsInitialized = true;
	}

	const bool MeshRenderer::IsReadyToInit()
	{
		if (!GetMesh()->IsLoaded())
			return false;
		else if (!IsInitialized())
			InitMesh();

		return true;
	}



	void MeshRenderer::SetMaterial(const Ref<Material>& material)
	{
		m_Material = material;
	}

}