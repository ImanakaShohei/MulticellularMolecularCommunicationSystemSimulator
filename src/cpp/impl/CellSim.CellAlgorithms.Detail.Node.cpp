#include "CellSim.CellAlgorithms.Detail.Node.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include <iomanip>
#include <iostream>

namespace CellSim::CellAlgorithms::Detail
{
    /**
     * @brief デフォルトのコンストラクタ
     * @brief 根ノードを宣言する際に使用
     *
     */
    Node::Node()
      : nodeID(0)
      , depth(0)
      , centerPoint(Numerics::Vector3(0, 0, 0))
      , length(Settings::Config::Simulation::FieldRadiusX() * 2)
      , isLeaf(true)
      , parent(nullptr)
      , cellInNode(nullptr)
      , numCellsInSubTree(0)
    {
        children.resize(8);
    }

    /**
     * @brief 引数付きコンストラクタ
     * @brief 主に子ノードを作成する際に使用
     *
     * @param _id
     * @param _parent
     * @param _depth
     * @param _centerPoint
     * @param _length
     */
    Node::Node(int32_t _nodeID, Node *_parent, int32_t _depth, Numerics::Vector3 _centerPoint, double _length)
      : nodeID(_nodeID)
      , depth(_depth)
      , centerPoint(_centerPoint)
      , length(_length)
      , isLeaf(true)
      , parent(_parent)
      , cellInNode(nullptr)
      , numCellsInSubTree(0)
    {
        children.resize(8);
    }

    /**
     * @brief Destroy the Node:: Node object
     *
     */
    Node::~Node()
    {
    }

    /**
     * @brief ノードの情報を出力する
     *
     */
    void Node::printNodeInfo() const
    {
        std::cout << "Node ID     : " << nodeID << "\n"
                  << "Depth       : " << depth << "\n"
                  << "Center      : (" << centerPoint.X << ", " << centerPoint.Y << ", " << centerPoint.Z << ")\n"
                  << "Length      : " << length << "\n"
                  << "Is Leaf     : " << std::boolalpha << isLeaf << "\n"
                  << "Num Cells   : " << numCellsInSubTree << "\n";

        if (cellInNode) {
            std::cout << "Cell Exists : Yes\n";
        } else {
            std::cout << "Cell Exists : No\n";
        }

        std::cout << "--------------------------" << std::endl;
    }

    /**
     * @brief 木構造を出力する
     *
     * @param d
     */
    void Node::printOctTree(int32_t d) const
    {
        // インデント（深さに応じて）
        for (int i = 0; i < d; ++i) {
            std::cout << " ";
            if (i == d - 1)
                std::cout << "-";
            else
                std::cout << " ";
        }

        // ノード情報の簡易表示
        std::cout << "(";
        if (isLeaf && numCellsInSubTree == 1)
            std::cout << "C";
        else
            std::cout << " ";
        std::cout << ") id:" << nodeID << " depth:" << depth << std::endl;

        // 子ノードを再帰的に表示
        for (const auto &child : children) {
            if (child) // nullptr チェック
            {
                child->printOctTree(d + 1);
            }
        }
    }

    /**
     * @brief 子ノードを作成する
     *
     */
    void Node::initChildren()
    {
        double childLength = length / 2.0;
        double offset      = childLength / 2.0;
        int32_t childDepth = depth + 1;

        for (int i = 0; i < 8; ++i) {
            double dx = (i & 1) ? offset : -offset;
            double dy = (i & 2) ? offset : -offset;
            double dz = (i & 4) ? offset : -offset;

            Numerics::Vector3 childCenter(centerPoint.X + dx, centerPoint.Y + dy, centerPoint.Z + dz); // 子ノードの中心座標

            int32_t childID = nodeID * 8 + i + 1; // 子ノードのID

            children[i] = new Node(childID, this, childDepth, childCenter, childLength);
        }

        isLeaf = false;
    }

    /**
     * @brief 細胞cが属する子ノードを返す
     *
     * @param c
     * @return Node*
     */
    Node *Node::findChildNode(const Cells::Cell &c) const
    {
        if (children.size() != 8) {
            std::cerr << "error: Node.cpp findChildNode() - children size is not 8" << std::endl;
            exit(1);
        }

        int index = 0;
        if (c.Position().X >= centerPoint.X)
            index |= 1;
        if (c.Position().Y >= centerPoint.Y)
            index |= 2;
        if (c.Position().Z >= centerPoint.Z)
            index |= 4;

        Node *child = children[index];
        if (!child) {
            std::cerr << "error: Node.cpp findChildNode() - child at index " << index << " is null" << std::endl;
            exit(1);
        }

        return child;
    }

    Node *Node::findLeafNode(const Cells::Cell &c) const
    {
        const Node *current = this;
        while (!current->getIsLeaf()) {
            current = current->findChildNode(c);
        }
        return const_cast<Node *>(current); // constなメンバでも返すのは非constにしたい場合
    }

    /**
     * @brief 木構造を初期化する。
     * @brief 基本的に根ノードで実行する
     *
     */
    void Node::resetTree()
    {
        for (auto &child : children) {
            if (child) {
                child->resetTree();
                delete child;
                child = nullptr;
            }
        }

        if (nodeID == 0) { // 根ノードであるならばchildrenを初期化
            children.resize(8, nullptr);
        }

        cellInNode        = nullptr;
        gravityCell       = Cells::CellInfo();
        numCellsInSubTree = 0;
        isLeaf            = true;
    }
}
