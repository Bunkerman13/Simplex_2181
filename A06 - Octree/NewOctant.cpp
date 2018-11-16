#include "NewOctant.h"

void NewOctant::Display(void)
{
	m_pRigidBody->AddToRenderList();
	for(int x = 0; x < 8; x++)
		if (m_pChild[x] != nullptr)
			m_pChild[x]->Display();
	//DimensionDisplay(checking);
}

NewOctant::NewOctant(vector3 center, float size)
{
	for (int x = 0; x < 8; x++)
		m_pChild[x] = nullptr;

	vector3 max = vector3(center.x + size, center.y + size, center.z + size);
	vector3 min = vector3(center.x - size, center.y - size, center.z - size);

	std::vector<vector3> list;

	list.push_back(max);
	list.push_back(min);

	m_pRigidBody = new MyRigidBody(list);

	#pragma region OldCode
		//currentLevel = level + 1;

		//int count = 0;
		//if (populate == true)
		//{
		//	
		//	for (int x = 0; x < parent->m_pEntityMngr->GetEntityCount(); x++)
		//		if (m_pRigidBody->IsColliding(parent->m_pEntityMngr->GetEntity(x)->GetRigidBody()))
		//			count++;//m_pEntityMngr->AddDimension(x, childNum);

		//	if (count != 0)
		//		parent->leaves.push_back(this);
		//}



		//if (populate == true)
		//{
		//	int count = 0;
		//	for (int x = 0; x < parent->m_pEntityMngr->GetEntityCount(); x++)
		//	{
		//		if (m_pRigidBody->IsColliding(parent->m_pEntityMngr->GetEntity(x)->GetRigidBody()))
		//		{
		//			count++;
		//		}
		//	}
		//	if (count > 5)
		//	{
		//		parent->leaves.push_back(this);
		//		m_pRigidBody->AddToRenderList();
		//	}
		//		
		//}
	#pragma endregion
	
}



uint NewOctant::Subdivide(uint ID, uint currentLevel, uint maxLevel)
{
	if (m_pChild[0] == nullptr)
	{
		float size = m_pRigidBody->GetHalfWidth().x / 2.f;

		vector3 centerPoints[8];
		centerPoints[0] = vector3(m_pRigidBody->GetCenterLocal().x + (size), m_pRigidBody->GetCenterLocal().y + (size), m_pRigidBody->GetCenterLocal().z + (size));
		centerPoints[1] = vector3(m_pRigidBody->GetCenterLocal().x + (size), m_pRigidBody->GetCenterLocal().y + (size), m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[2] = vector3(m_pRigidBody->GetCenterLocal().x - (size), m_pRigidBody->GetCenterLocal().y + (size), m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[3] = vector3(m_pRigidBody->GetCenterLocal().x - (size), m_pRigidBody->GetCenterLocal().y + (size), m_pRigidBody->GetCenterLocal().z + (size));
																																			   
		centerPoints[4] = vector3(m_pRigidBody->GetCenterLocal().x + (size), m_pRigidBody->GetCenterLocal().y - (size), m_pRigidBody->GetCenterLocal().z + (size));
		centerPoints[5] = vector3(m_pRigidBody->GetCenterLocal().x + (size), m_pRigidBody->GetCenterLocal().y - (size), m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[6] = vector3(m_pRigidBody->GetCenterLocal().x - (size), m_pRigidBody->GetCenterLocal().y - (size), m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[7] = vector3(m_pRigidBody->GetCenterLocal().x - (size), m_pRigidBody->GetCenterLocal().y - (size), m_pRigidBody->GetCenterLocal().z + (size));

		for (int x = 0; x < 8; x++)
		{
			m_pChild[x] = new NewOctant(centerPoints[x], size);
			if (CheckValues(m_pChild[x]))
			{
				if (currentLevel == maxLevel)
				{
					ID++;
					m_pChild[x]->m_iID = ID;
				}
			}
			/*else
				m_pChild[x] = nullptr;*/
		}
		
	}
	else
	{
		for (int x = 0; x < 8; x++)
		{

			if (m_pChild[x] != nullptr)
			{
				ID = m_pChild[x]->Subdivide(ID, currentLevel, maxLevel);
				
			}
				
		}
			
	}
	
	return ID;
}

bool NewOctant::CheckValues(NewOctant * current)
{
	m_pEntityMngr = MyEntityManager::GetInstance();

	int count = 0;
	for (int x = 0; x < m_pEntityMngr->GetEntityCount(); x++)
		if (current->m_pRigidBody->IsColliding(m_pEntityMngr->GetEntity(x)->GetRigidBody()))
			count++;

	if (count < 5)
		return false;

	return true;
}


NewOctant::NewOctant(uint maxSubNum, uint idealEntityCount)
{
	
	Init();
	//visual = false;
	for (int x = 1; x < maxSubNum; x++)
	{
		m_pEntityMngr->ClearDimensionSetAll();
		Subdivide(m_iID, x+1, maxSubNum);
	}
	
	#pragma region OldCode
		/*int num = pow(8, currentLevel);
		for (int x = 0; x < num; x++)
		{
		m_pEntityMngr->AddDimension(currentLevel, num);
		}*/
		//std::cout << "Previous: " << parent->leaves.size() << std::endl;

		//for (int x = 0; x < parent->leaves.size(); x++)
		//{
		//	//int count = 0;
		//	for (int y = 0; y < parent->m_pEntityMngr->GetEntityCount(); y++)
		//		if (parent->leaves[x]->m_pRigidBody->IsColliding(parent->m_pEntityMngr->GetEntity(y)->GetRigidBody()))
		//		{
		//			parent->m_pEntityMngr->AddDimension(y, x);
		//			//count++;
		//		}
		//	//if (count == 0) { SafeDelete(parent->leaves[x]); parent->leaves.erase(parent->leaves.cbegin + x); }
		//		

		//}
		//std::cout << "After: " << parent->leaves.size() << std::endl;
	#pragma endregion

	AssignSpaces();
	
}

	#pragma region OldCode
		//old code
		/*oid NewOctant::Subdivide(NewOctant* child)
		{

		if (child->m_pChild[0] == nullptr)
		{
		float size = (child->m_pRigidBody->GetMaxLocal().x - child->m_pRigidBody->GetCenterLocal().x) / 2.f;

		vector3 centerPoints[8];
		centerPoints[0] = vector3(child->m_pRigidBody->GetCenterLocal().x + (size), child->m_pRigidBody->GetCenterLocal().y + (size), child->m_pRigidBody->GetCenterLocal().z + (size));
		centerPoints[1] = vector3(child->m_pRigidBody->GetCenterLocal().x + (size), child->m_pRigidBody->GetCenterLocal().y + (size), child->m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[2] = vector3(child->m_pRigidBody->GetCenterLocal().x - (size), child->m_pRigidBody->GetCenterLocal().y + (size), child->m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[3] = vector3(child->m_pRigidBody->GetCenterLocal().x - (size), child->m_pRigidBody->GetCenterLocal().y + (size), child->m_pRigidBody->GetCenterLocal().z + (size));

		centerPoints[4] = vector3(child->m_pRigidBody->GetCenterLocal().x + (size), child->m_pRigidBody->GetCenterLocal().y - (size), child->m_pRigidBody->GetCenterLocal().z + (size));
		centerPoints[5] = vector3(child->m_pRigidBody->GetCenterLocal().x + (size), child->m_pRigidBody->GetCenterLocal().y - (size), child->m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[6] = vector3(child->m_pRigidBody->GetCenterLocal().x - (size), child->m_pRigidBody->GetCenterLocal().y - (size), child->m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[7] = vector3(child->m_pRigidBody->GetCenterLocal().x - (size), child->m_pRigidBody->GetCenterLocal().y - (size), child->m_pRigidBody->GetCenterLocal().z + (size));


		for (int x = 0; x < 8; x++)
		child->m_pChild[x] = new NewOctant(centerPoints[x], size);
		}
		else
		for (int x = 0; x < 8; x++)
		child->m_pChild[x]->Subdivide(child->m_pChild[x]);
		}*/
	#pragma endregion



void NewOctant::DimensionDisplay(uint index)
{
	for (int x = 0; x < 8; x++)
		if(m_pChild[x] != nullptr)
			if (m_pChild[x]->m_iID == index)
				m_pChild[x]->m_pRigidBody->AddToRenderList();

	for (int x = 0; x < 8; x++)
		if (m_pChild[x] != nullptr)
			m_pChild[x]->DimensionDisplay(index);

}

void NewOctant::Init(void)
{
	visual = false;
	//m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();
	
	std::vector<vector3> v3MaxMin_list;
	for (uint i = 0; i < m_pEntityMngr->GetEntityCount(); ++i)
	{
		MyRigidBody* pRG = m_pEntityMngr->GetEntity(i)->GetRigidBody();
		vector3 v3Min = pRG->GetMinGlobal();
		vector3 v3Max = pRG->GetMaxGlobal();
		v3MaxMin_list.push_back(v3Min);
		v3MaxMin_list.push_back(v3Max);

		#pragma region OldCode
			//vector3 v3Position = pRG->GetCenterGlobal();

			/*if (v3Position.x < 0.0f)
			{
			if (v3Position.x < -17.0f)
			m_pEntityMngr->AddDimension(i, 1);
			else
			m_pEntityMngr->AddDimension(i, 2);
			}
			else if (v3Position.x > 0.0f)
			{
			if (v3Position.x > 17.0f)
			m_pEntityMngr->AddDimension(i, 3);
			else
			m_pEntityMngr->AddDimension(i, 4);
			vector3 v3Min = pRG->GetMinGlobal();
			}*/
	#pragma endregion
	}

	for (uint i = 0; i < 8; i++)
	{
		m_pChild[i] = nullptr;
	}
	m_pRigidBody = new MyRigidBody(v3MaxMin_list);
	
	m_iID = 0;
}

void NewOctant::AssignSpaces(void)
{
	for (int x = 0; x < 8; x++)
	{
		if (m_pChild[x] != nullptr)
			m_pChild[x]->AssignSpaces();
	}

	if (m_pChild[0] == nullptr)
	{
		IsColliding();
		std::cout << m_iID << std::endl;
	}
		
}

void NewOctant::IsColliding(void)
{
	m_pEntityMngr = MyEntityManager::GetInstance();
	for (uint i = 0; i < m_pEntityMngr->GetEntityCount(); ++i)
	{
		MyRigidBody* pRB = m_pEntityMngr->GetEntity(i)->GetRigidBody();
		if (pRB->IsColliding(m_pRigidBody) && m_iID != 0)
		{
			m_pEntityMngr->GetEntity(i)->AddDimension(m_iID);
		}
	}
}
