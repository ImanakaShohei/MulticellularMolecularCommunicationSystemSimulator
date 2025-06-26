#ifndef CELLSIM_CELLALGORITHMS_DETAILS_NODE
#define CELLSIM_CELLALGORITHMS_DETAILS_NODE

#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.Optimization.hpp"

enum Octant
{
    LLB = 0, // Lower Left Back
    LRB = 1,
    LLF = 2,
    LRF = 3,
    ULB = 4,
    URB = 5,
    ULF = 6,
    URF = 7 // Upper Right Front
};

namespace CellSim::CellAlgorithms::Detail
{
    class Node {
        protected:
        int32_t nodeID;                // ノードのID
        int32_t depth;                 // ノードの深さ
        Numerics::Vector3 centerPoint; // グリッドの中心座標
        double length;                 // グリッドの１辺の長さ
        bool isLeaf;                   // ノードが葉であるかどうか

        Node *parent; // 親ノードのポインタ

        public:
        int32_t numCellsInSubTree;                    // 子孫ノードが持つ全細胞数
        Cells::Cell const *cellInNode;                // ノードが直接持っている細胞のポインタ
        Cells::CellInfo gravityCell;                  // ノードの重心細胞のポインタ
        std::vector<Node *> children;                 // 子ノードのポインタを格納する配列
        std::vector<Cells::CellInfo> affectableCells; // DualTreeBHで使用する、ノードの重心に作用を及ぼす細胞のリスト

        Node();
        Node(int32_t _nodeID, Node *_parent, int32_t _depth, Numerics::Vector3 _centerPoint, double _length);
        ~Node();

        constexpr int32_t getNodeID() const;
        constexpr int32_t getDepth() const;
        constexpr Numerics::Vector3 getCenterPoint() const;
        constexpr double getLength() const;
        constexpr bool getIsLeaf() const;

        void printNodeInfo() const;
        void printOctTree(int32_t d = 0) const;
        void initChildren();
        Node *findChildNode(const Cells::Cell &c) const;
        Node *findLeafNode(const Cells::Cell &c) const;
        void resetTree();
    };
}

namespace CellSim::CellAlgorithms::Detail
{
    constexpr int32_t Node::getNodeID() const
    {
        return nodeID;
    }

    constexpr int32_t Node::getDepth() const
    {
        return depth;
    }

    constexpr Numerics::Vector3 Node::getCenterPoint() const
    {
        return centerPoint;
    }

    constexpr double Node::getLength() const
    {
        return length;
    }

    constexpr bool Node::getIsLeaf() const
    {
        return isLeaf;
    }
}

#endif //!CELLSIM_CELLALGORITHMS_DETAILS_NODE