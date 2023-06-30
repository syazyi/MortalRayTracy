#pragma once
#include "IHittbale.hpp"
namespace mortal
{
    struct Vertex
    {
        Point3 position;
        Vec3 normal;
        Vec3 color;
        double u;
        double v;

        bool operator==(const Vertex& rhs) const {
            return position == rhs.position && color == rhs.color && normal == rhs.normal && u == rhs.u && v == rhs.v;
        }
    };
    
    class Model : public IHittbale{
    public:
        Model() = default;
        explicit Model(const char* filename);
        virtual bool HitIntersectionRay(const Ray& ray, double tMin, double tMax, HitResult& hitResult) const;
        virtual bool AxisAlignBoundBox(double time0, double time1, AABB& aabb) const;
    private:
        //normal interpolation
        
    private:
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
    } ;


} // namespace mortal

template<>
struct std::hash<mortal::Vertex> {
    size_t operator()(mortal::Vertex const& vertex) const {
        return (hash<double>{}(vertex.position.x) ^ 
            hash<double>{}(vertex.position.y) ^ 
            hash<double>{}(vertex.position.z) ^ 
            (hash<double>{}(vertex.normal.x) << 1 )^
            (hash<double>{}(vertex.normal.y) << 1 )^
            (hash<double>{}(vertex.normal.z) << 1 )^
            (hash<double>{}(vertex.u) << 2) ^ (hash<double>{}(vertex.v) << 2));
    }
};