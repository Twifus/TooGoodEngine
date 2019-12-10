#include <list>
#include <random>

#include "BSPTree.hpp"

namespace TooGoodEngine
{
	static const int MAX_LEAF_DATASIZE = 6;

	// ------------------------------------------------------------------------ //
	// ------------------------------ PLANE ----------------------------------- //
	// ------------------------------------------------------------------------ //

	BSPTree::Plane::Plane() : position(Vector3::zero), normal(Vector3::zero) {}
	
	BSPTree::Plane::Plane(const Vector3& position, const Vector3& normal) : position(position), normal(normal) {}

	// Point distance to a plan (+ - dist)
	inline double BSPTree::Plane::DistanceToPlan(const Vector3& point) const {
		return (point - position).Dot(normal);
	}

	// ------------------------------------------------------------------------ //
	// ------------------------------- NODE ----------------------------------- //
	// ------------------------------------------------------------------------ //

	BSPTree::BSPNode::BSPNode() : front(nullptr), back(nullptr), plan(), data() {};

	BSPTree::BSPNode::BSPNode(BSPNode* back, BSPNode* front, const Plane& plan, const std::list<GameObject>& data) : front(front), back(back), plan(plan), data(data) {};

	// Test if we are at end of tree
	inline bool BSPTree::BSPNode::isLeaf() const {
		return (back == nullptr && front == nullptr);
	}

	// Return position of the object in 3D space /!\ TODO : changer en fonction de comment est l'objet
	inline Vector3 objectPosition(const GameObject& o) {
		return Vector3::zero;
	}
	// Return the size of the object  /!\ TODO : changer en fonction de comment est l'objet
	inline double objectRadius(const GameObject& o) {
		return 1;
	}

	// ------------------------------------------------------------------------ //
	// ------------------------------- TREE ----------------------------------- //
	// ------------------------------------------------------------------------ //

	// Constructor
	BSPTree::BSPTree(Vector3 pos_start) : distribution(-10, 10) {
		// create node and insert in root
		root.emplace_back(nullptr, nullptr, Plane(pos_start, Vector3::zero), std::list<GameObject>());
	}

	// Split a node in two and create his children (then reallocate data)
	void BSPTree::SplitNode(BSPNode& node) {
		// select plan (and so set up the plan for splitting data)
		node.plan.position = objectPosition(node.data.front());
		node.plan.normal = Vector3(distribution(generator), distribution(generator), distribution(generator)).Normalized();
		// create leaf nodes and add to root
		root.emplace_back();		// Add the new front node to the root
		node.front = &root.back();	// To ensure we wont target a copie that doesn't exist anymore
		root.emplace_back();		// Same for back node
		node.back = &root.back();
		// insert data into it
		std::list<GameObject> result_list;
		for (const GameObject& obj : node.data) {
			double dist = node.plan.DistanceToPlan(objectPosition(obj));
			if (dist > objectRadius(obj)) {
				if (dist > 0)
					node.front->data.push_back(obj);
				else
					node.back->data.push_back(obj);
			}
			else {
				result_list.push_back(obj);
			}
		}
		node.data = result_list;
	}

	// Add an object to the tree
	void BSPTree::AddObject(const GameObject& object) { // pointer func compare +1 -1 0 (front back middle ?)
		// Iteration on nodes (plan back / front)
		BSPNode* node = &root.front();
		bool stop = false;
		while (!node->isLeaf()) {
			double dist = node->plan.DistanceToPlan(objectPosition(object));
			if (dist < objectRadius(object))
				break;
			if (dist > 0)
				node = node->front;
			else
				node = node->back;
		}
		node->data.push_back(object);
		// Is it necessary to split node in two ? (too much objects, might be good to precise)
		if (node->data.size() > MAX_LEAF_DATASIZE&& node->isLeaf())
			SplitNode(*node);
	}


	void checkFonc(GameObject& a, GameObject& b)
	{
		// do stuffs (could be in parameter of Evaluate as well for maximum gasm)
	}

	// Iterate on a node
	void BSPTree::EvaluateNode(BSPNode& node) { // ((void*) func(void)) pointer ?
		// Calling checkFonc on data
		if (node.data.size() > 1) {
			for (auto it1 = node.data.begin(); it1 != node.data.end(); ++it1) {
				for (auto it2 = it1; it2 != node.data.end(); ++it2) {
					checkFonc(*it1, *it2);
				}
			}
		}
		// recursion on children
		if (!node.isLeaf()) {
			EvaluateNode(*(node.back));
			EvaluateNode(*(node.front));
		}
	}

	// Parse BSP data and call func on every objects in the same area
	void BSPTree::Evaluate() {
		EvaluateNode(root.front());
	}

}