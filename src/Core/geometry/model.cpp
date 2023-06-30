#include "model.hpp"
#include <unordered_map>
#include "tiny_obj_loader.h"
namespace mortal {
	Model::Model(const char* filename)
	{
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename)) {
            throw std::runtime_error(warn + err);
        }

        auto verteiesSize = attrib.vertices.size() / 3;
        m_Vertices.reserve(verteiesSize);
        std::unordered_map<Vertex, uint32_t> ver_tex_indeies;
        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};
                vertex.position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };

                vertex.color = { 1.0f, 1.0f, 1.0f };

                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };

                vertex.u = attrib.texcoords[2 * index.texcoord_index + 0];
                vertex.v = 1.0f - attrib.texcoords[2 * index.texcoord_index + 1];

                if (ver_tex_indeies.count(vertex) == 0) {
                    ver_tex_indeies[vertex] = m_Vertices.size();
                    m_Vertices.emplace_back(vertex);
                }

                m_Indices.emplace_back(ver_tex_indeies[vertex]);
            }
        }
	}

	bool Model::HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const
	{
		return false;
	}

	bool Model::AxisAlignBoundBox(double time0, double time1, AABB& aabb) const
	{
		return false;
	}

}//namespace mortal