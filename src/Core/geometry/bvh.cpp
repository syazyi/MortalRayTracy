#include "bvh.hpp"

namespace mortal
{
    BVHNode::BVHNode(const HitList& list, size_t start, size_t end, float time0, float time1)
    {
        if (FirstBuildNode) {
           AABB wholeAABB;
            list.AxisAlignBoundBox(time0, time1, wholeAABB);
            m_Box = wholeAABB;
        }

        auto tempList = list;

        auto longestAxis = m_Box.GetLongestAxis();
        switch (longestAxis)
        {
        case mortal::EAxis::eX:
            std::sort(tempList.m_Objects.begin() + start, tempList.m_Objects.begin() + end,
                [&time0, &time1](const std::shared_ptr<IHittbale>& left, const std::shared_ptr<IHittbale>& right)-> bool{
                    AABB leftAABB;
                    AABB rightAABB;
                    left->AxisAlignBoundBox(time0, time1, leftAABB);
                    right->AxisAlignBoundBox(time0, time1, rightAABB);
                    auto leftX = leftAABB.GetAxisLength(EAxis::eX);
                    auto rightX = rightAABB.GetAxisLength(EAxis::eX);
                    return leftX < rightX;
                });
            break;
        case mortal::EAxis::eY:
            std::sort(tempList.m_Objects.begin() + start, tempList.m_Objects.begin() + end,
                [&time0, &time1](const std::shared_ptr<IHittbale>& left, const std::shared_ptr<IHittbale>& right)-> bool {
                    AABB leftAABB;
                    AABB rightAABB;
                    left->AxisAlignBoundBox(time0, time1, leftAABB);
                    right->AxisAlignBoundBox(time0, time1, rightAABB);
                    auto leftY = leftAABB.GetAxisLength(EAxis::eY);
                    auto rightY = rightAABB.GetAxisLength(EAxis::eY);
                    return leftY < rightY;
                });
            break;
        case mortal::EAxis::eZ:
            std::sort(tempList.m_Objects.begin() + start, tempList.m_Objects.begin() + end,
                [&time0, &time1](const std::shared_ptr<IHittbale>& left, const std::shared_ptr<IHittbale>& right)-> bool {
                    AABB leftAABB;
                    AABB rightAABB;
                    left->AxisAlignBoundBox(time0, time1, leftAABB);
                    right->AxisAlignBoundBox(time0, time1, rightAABB);
                    auto leftZ = leftAABB.GetAxisLength(EAxis::eZ);
                    auto rightZ = rightAABB.GetAxisLength(EAxis::eZ);
                    return leftZ < rightZ;
                 });
            break;
        }

    }

    bool BVHNode::HitIntersectionRay(const Ray& ray, float tMin, float tMax, HitResult& hitResult) const
    {
        if (!m_Box.BeHit(ray, tMin, tMax)) {
            return false;
        }
        HitResult temp;
        bool hitLeft = m_Left->HitIntersectionRay(ray, tMin, tMax, temp);
        bool hitRight = m_Right->HitIntersectionRay(ray, tMin, tMax, temp);
        return hitLeft || hitRight;
    }

    bool BVHNode::AxisAlignBoundBox(float time0, float time1, AABB& aabb) const
    {
        aabb = m_Box;
        return true;
    }

} // namespace mortal
