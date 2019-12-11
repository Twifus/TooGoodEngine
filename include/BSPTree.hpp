#pragma once

#include "GameObject.hpp"
#include "CollisionData.hpp"
#include "Vector3.hpp"

#include <list>
#include <random>


// Création : BSPTree(CollisionData)
// collision data récupère les primitives pour
// la narrow phase

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

		CollisionData collision;

		std::list<BSPNode> root;
		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution;

		void SplitNode(BSPNode& node);
		void EvaluateNode(BSPNode& node, std::list<GameObject> &stack);

	public:
		BSPTree(CollisionData &collision);
		void AddGameObject(const GameObject& object);
		void Evaluate();
	};
}