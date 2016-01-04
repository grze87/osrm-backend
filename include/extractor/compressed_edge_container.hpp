#ifndef GEOMETRY_COMPRESSOR_HPP_
#define GEOMETRY_COMPRESSOR_HPP_

#include "util/typedefs.hpp"

#include <unordered_map>

#include <string>
#include <vector>

class CompressedEdgeContainer
{
  public:
    using CompressedNode = std::pair<NodeID, EdgeWeight>;
    using EdgeBucket = std::vector<CompressedNode>;

    CompressedEdgeContainer();
    void CompressEdge(const EdgeID surviving_edge_id,
                      const EdgeID removed_edge_id,
                      const NodeID via_node_id,
                      const NodeID target_node,
                      const EdgeWeight weight1,
                      const EdgeWeight weight2);

    bool HasEntryForID(const EdgeID edge_id) const;
    void PrintStatistics() const;
    void SerializeInternalVector(const std::string &path) const;
    unsigned GetPositionForID(const EdgeID edge_id) const;
    const EdgeBucket& GetBucketReference(const EdgeID edge_id) const;
    NodeID GetFirstEdgeTargetID(const EdgeID edge_id) const;
    NodeID GetLastEdgeSourceID(const EdgeID edge_id) const;

  private:
    int free_list_maximum = 0;

    void IncreaseFreeList();
    std::vector<EdgeBucket> m_compressed_geometries;
    std::vector<unsigned> m_free_list;
    std::unordered_map<EdgeID, unsigned> m_edge_id_to_list_index_map;
};

#endif // GEOMETRY_COMPRESSOR_HPP_
