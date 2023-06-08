#include "bvh.hpp"

namespace mortal
{
    /*
        Need to modify, if according to my idea, AABB needs to be stored in each object first. 
        But here, follow the tutorial first.
    */
    BVHNode::BVHNode(const HitList& list, size_t start, size_t end, float time0, float time1)
    {
        HitList tempList;
        tempList.m_Objects = std::vector<std::shared_ptr<IHittbale>>(list.m_Objects.begin() + start, list.m_Objects.begin() + end);
        AABB wholeAABB;
        list.AxisAlignBoundBox(time0, time1, wholeAABB);
        m_Box = wholeAABB;

        auto longestAxis = m_Box.GetLongestAxis();

        auto object_span = end - start;

        if (object_span == 1) {
            m_Left = m_Right = tempList.m_Objects[start];
        }
        else {
            //sort
            switch (longestAxis)
            {
            case mortal::EAxis::eX:
                std::sort(tempList.m_Objects.begin() + start, tempList.m_Objects.begin() + end,
                    [&time0, &time1](const std::shared_ptr<IHittbale>& left, const std::shared_ptr<IHittbale>& right)-> bool{
                        AABB leftAABB;
                        AABB rightAABB;
                        //every object be caculate many times!!!
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
            if (object_span == 2) {
                m_Left = tempList.m_Objects[start];
                m_Right = tempList.m_Objects[start + 1];
            }
            else {
                auto mid = start + (object_span >> 1);

                m_Left = std::make_shared<BVHNode>(tempList, start, mid, time0, time1);
                m_Right = std::make_shared<BVHNode>(tempList, mid, end, time0, time1);
            }
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
