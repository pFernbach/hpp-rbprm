// Copyright (c) 2014, LAAS-CNRS
// Authors: Steve Tonneau (steve.tonneau@laas.fr)
//
// This file is part of hpp-rbprm.
// hpp-rbprm is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-rbprm is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-rbprm. If not, see <http://www.gnu.org/licenses/>.

#include <hpp/rbprm/sampling/sample-container.hh>
#include <hpp/fcl/shape/geometric_shapes.h>

#include <vector>

using namespace hpp;
using namespace hpp::model;
using namespace hpp::rbprm;
using namespace hpp::rbprm::sampling;
using namespace fcl;

 namespace
 {

    fcl::OcTree GenerateOctree(const std::deque<Sample>& samples, const double resolution)
    {
        octomap::OcTree* octTree = new octomap::OcTree(resolution);
        octomap::Pointcloud octPointCloud;
        for(std::deque<Sample>::const_iterator cit = samples.begin();
            cit != samples.end(); ++cit)
        {
            const fcl::Vec3f& position = cit->effectorPosition_;
            octomap::point3d endpoint((float)position[0],(float)position[1],(float)position[2]);
            octPointCloud.push_back(endpoint);
        }
        octomap::point3d origin(0.0,0.0,0.0);
        octTree->insertPointCloud(octPointCloud,origin);
        octTree->updateInnerOccupancy();
        return fcl::OcTree(boost::shared_ptr<const octomap::OcTree>(octTree));
    }

    std::vector<fcl::CollisionObject*> generateBoxesFromOctomap(const fcl::OcTree& tree)
    {
        std::vector<fcl::CollisionObject*> boxes;
        std::vector<boost::array<FCL_REAL, 6> > boxes_ = tree.toBoxes();

        for(std::size_t i = 0; i < boxes_.size(); ++i)
        {
            FCL_REAL x = boxes_[i][0];
            FCL_REAL y = boxes_[i][1];
            FCL_REAL z = boxes_[i][2];
            FCL_REAL size = boxes_[i][3];
            FCL_REAL cost = boxes_[i][4];
            FCL_REAL threshold = boxes_[i][5];

            Box* box = new Box(size, size, size);
            box->cost_density = cost;
            box->threshold_occupied = threshold;
            fcl::CollisionObject* obj = new fcl::CollisionObject(boost::shared_ptr<fcl::CollisionGeometry>(box), Transform3f(Vec3f(x, y, z)));
            boxes.push_back(obj);
        }
        return boxes;
    }
 }

SampleContainer::SampleContainer(const model::JointPtr_t limb, const std::size_t nbSamples, const double resolution)
    : samples_(GenerateSamples(limb,nbSamples))
    , octree_(GenerateOctree(samples_, resolution))
    , boxes_(generateBoxesFromOctomap(octree_))
{
    // NOTHING
}

SampleContainer::~SampleContainer()
{
    // NOTHING
}
