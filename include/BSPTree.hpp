#pragma once

#include "Vector3.hpp"
#include <list>

struct GameObject {};

namespace TooGoodEngine
{
	class BSPTree
	{
	private:
		struct Plane {
			Vector3 position;
			Vector3 normal;

			Plane();
			Plane(const Vector3& position, const Vector3& normal);
			inline double DistanceToPlan(const Vector3& point) const;
		};

		struct BSPNode {
			BSPNode* back;
			BSPNode* front;
			Plane plan;
			std::list<GameObject> data;

			BSPNode();
			BSPNode(BSPNode* back, BSPNode* front, const Plane& plan, const std::list<GameObject>& data);
			inline bool isLeaf() const;
		};

		std::list<BSPNode> root;
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution;

		void SplitNode(BSPNode& node);
		void EvaluateNode(BSPNode& node);

	public:
		BSPTree(Vector3 pos_start);
		void AddObject(const GameObject& object);
		void Evaluate();
	};
}