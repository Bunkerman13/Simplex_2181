#include "NewOctant.h"

/*
Display
displays the rigidbodies 
*/
void NewOctant::Display(void)
{
	// adds rigidbody of current octant to renderlist
	m_pRigidBody->AddToRenderList();

	// searches all children recursively using display
	for (int x = 0; x < 8; x++)
		if (m_pChild[x] != nullptr)
			m_pChild[x]->Display();
	/// Old Code
	///DimensionDisplay(checking);
}
/*
Overloaded Constructor
Used to create children
*/
NewOctant::NewOctant(vector3 center, float size)
{
	// instances 8 children of new octant to nullptr
	for (int x = 0; x < 8; x++)
		m_pChild[x] = nullptr;

	// gets max and min based on passed in size and cneter values
	vector3 max = vector3(center.x + size, center.y + size, center.z + size);
	vector3 min = vector3(center.x - size, center.y - size, center.z - size);

	// creates a local list, and puts max and min values within
	std::vector<vector3> list;
	list.push_back(max);
	list.push_back(min);

	// creates new rigidbody with new max min list
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
/*
Subdivide
checks if the current set of children are nullptr.
Creates new children if they're nullptr.
Subdivides again if they are not
*/
uint NewOctant::Subdivide(uint ID, uint currentLevel, uint maxLevel)
{
	// checks if the object is nullptr
	if (m_pChild[0] == nullptr)
	{
		// gets new size to pass in based on current rigidbody
		float size = m_pRigidBody->GetHalfWidth().x / 2.f;

		// creates 8 points to be used for new octants
		vector3 centerPoints[8];
		centerPoints[0] = vector3(m_pRigidBody->GetCenterLocal().x + (size), m_pRigidBody->GetCenterLocal().y + (size), m_pRigidBody->GetCenterLocal().z + (size));
		centerPoints[1] = vector3(m_pRigidBody->GetCenterLocal().x + (size), m_pRigidBody->GetCenterLocal().y + (size), m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[2] = vector3(m_pRigidBody->GetCenterLocal().x - (size), m_pRigidBody->GetCenterLocal().y + (size), m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[3] = vector3(m_pRigidBody->GetCenterLocal().x - (size), m_pRigidBody->GetCenterLocal().y + (size), m_pRigidBody->GetCenterLocal().z + (size));
																																			   
		centerPoints[4] = vector3(m_pRigidBody->GetCenterLocal().x + (size), m_pRigidBody->GetCenterLocal().y - (size), m_pRigidBody->GetCenterLocal().z + (size));
		centerPoints[5] = vector3(m_pRigidBody->GetCenterLocal().x + (size), m_pRigidBody->GetCenterLocal().y - (size), m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[6] = vector3(m_pRigidBody->GetCenterLocal().x - (size), m_pRigidBody->GetCenterLocal().y - (size), m_pRigidBody->GetCenterLocal().z - (size));
		centerPoints[7] = vector3(m_pRigidBody->GetCenterLocal().x - (size), m_pRigidBody->GetCenterLocal().y - (size), m_pRigidBody->GetCenterLocal().z + (size));

		// goes through and creates a new set of octants
		for (int x = 0; x < 8; x++)
		{
			// creates octant using overloaded constructor
			m_pChild[x] = new NewOctant(centerPoints[x], size);
			m_pChild[x]->idealEntityCount = idealEntityCount;

			// checks if there are more than ideal entity count
			// if so, go through
			if (CheckValues(m_pChild[x]))
			{
				// checks if it's the final level, then assigns an ID
				if (currentLevel == maxLevel)
				{
					ID++;
					m_pChild[x]->m_iID = ID;
				}
			}
		}
		
	}
	// if the object is nullptr, subdivide once again
	else
	{
		// subdivides for each child
		for (int x = 0; x < 8; x++)
			if (m_pChild[x] != nullptr)
				ID = m_pChild[x]->Subdivide(ID, currentLevel, maxLevel);	
	}
	
	// returns ID number when finished
	return ID;
}
/*
	CheckValues
	checks if octant needs to be made, if not then returns false
	if so, returns true.
*/
bool NewOctant::CheckValues(NewOctant * current)
{
	// gets instance of entity manager in current octant
	m_pEntityMngr = MyEntityManager::GetInstance();

	// uses local variable to count and check if amount of objects
	// colliding with octant is greater than ideal identity count
	int count = 0;
	for (int x = 0; x < m_pEntityMngr->GetEntityCount(); x++)
		if (current->m_pRigidBody->IsColliding(m_pEntityMngr->GetEntity(x)->GetRigidBody()))
			count++;

	// if count is less than ideal entity count, return false
	if (count < idealEntityCount)
		return false;

	// if count is more, return true
	return true;
}
/*
Default Constructor
Constructor called on the root octant
*/
NewOctant::NewOctant(uint maxSubNum, uint idEntCnt)
{
	idealEntityCount = idEntCnt;

	//  calls init to set up base information / octant
	Init();

	// subdivides number of time desired
	for (int x = 1; x < maxSubNum; x++)
	{
		// makes sure all dimensions are cleared before last subdivision
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

	// calls assign spaces at end to assign dimensions and objects to those dimensions
	AssignSpaces();
	
}
/*
DimensionDisplay
Custom display that that helped check 
out the different octants that were colliding
*/
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
/*
Init
Initial values are instantiated and the 
root octant and its children are created
*/
void NewOctant::Init(void)
{
	//m_pMeshMngr = MeshManager::GetInstance();
	// gets the entity manager's instance
	m_pEntityMngr = MyEntityManager::GetInstance();
	
	// creates a local list to hold position vector3's of objects
	std::vector<vector3> v3MaxMin_list;
	for (uint i = 0; i < m_pEntityMngr->GetEntityCount(); ++i)
	{
		// creates a local rigidbody and grabs the max and min of each object
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

	// creates children for the current(root) octant
	for (uint i = 0; i < 8; i++)
		m_pChild[i] = nullptr;
	
	// creates base(root) rigidbody out of the largest max and smallest min
	m_pRigidBody = new MyRigidBody(v3MaxMin_list);
	
	// sets its ID to 0
	m_iID = -1;
}
/*
AssignSpaces
Finds all of the leaves and 
calls the IsColliding method on them
*/
void NewOctant::AssignSpaces(void)
{
	// checks if children are nullptr
	// if not, recursively call AssignSpaces 
	// until all populated children have been found
	for (int x = 0; x < 8; x++)
	{
		if (m_pChild[x] != nullptr)
			m_pChild[x]->AssignSpaces();
	}
	// when it reaches a nullptr child, calls IsColliding
	// to sort objects in the proper dimension
	if (m_pChild[0] == nullptr)
	{
		IsColliding();
		//std::cout << m_iID << std::endl;
	}
		
}
/*
IsColliding
Checks if any of the entities are 
colliding with the current ocant's rigidbody
*/
void NewOctant::IsColliding(void)
{
	// put EntityManager in this octant's management variables
	m_pEntityMngr = MyEntityManager::GetInstance();

	// loops through every entity
	for (uint i = 0; i < m_pEntityMngr->GetEntityCount(); ++i)
	{
		// grabs each entity's rigidbody and tests if it's colliding with
		// this octant's rigidbody.  If colliding, sort in this octant's dimension
		MyRigidBody* pRB = m_pEntityMngr->GetEntity(i)->GetRigidBody();
		if (pRB->IsColliding(m_pRigidBody) )//&& m_iID != 0)
			m_pEntityMngr->GetEntity(i)->AddDimension(m_iID);
		
	}
}
