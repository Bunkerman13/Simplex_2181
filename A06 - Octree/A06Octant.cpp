#include "A06Octant.h"
using namespace Simplex;

void Simplex::A06Octant::Init(void)
{
	//m_pMeshMngr = MeshManager::GetInstance();
	//m_pEntityMngr = MyEntityManager::GetInstance();
	////std::vector<MyEntity*> l_Entity_List = m_pEntityMngr->GetEntityList();
	////uint iEntityCount = l_Entity_List.size();
	//std::vector<vector3> v3MaxMin_list;
	//for (uint i = 0; i < iEntityCount; ++i)
	//{
	//	MyRigidBody* pRG = l_Entity_List[i]->GetRigidBody();
	//	vector3 v3Min = pRG->GetMinGlobal();
	//	vector3 v3Max = pRG->GetMaxGlobal();
	//	v3MaxMin_list.push_back(v3Min);
	//	v3MaxMin_list.push_back(v3Max);
	//
	//}
	//for (uint i = 0; i < 8; i++)
	//{
	//	m_pChild[i] = nullptr;
	//}
	//m_pRigidBody = new MyRigidBody(v3MaxMin_list);
}

bool Simplex::A06Octant::IsColliding(uint a_uRBIndex)
{
	return false;
}

void Simplex::A06Octant::Display(vector3 a_v3Color)
{
	m_pRigidBody->AddToRenderList();
}

void Simplex::A06Octant::Subdivide(void)
{
}

Simplex::A06Octant::A06Octant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	Init();
}
