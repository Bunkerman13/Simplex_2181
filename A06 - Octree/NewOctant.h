#include "Simplex/Simplex.h"
#include "MyEntityManager.h"

using namespace Simplex;

class NewOctant
{
	MeshManager* m_pMeshMngr = nullptr;//Mesh Manager singleton
	MyEntityManager* m_pEntityMngr = nullptr; //Entity Manager Singleton

	NewOctant* m_pChild[8];//Will store the children of the current octant

	MyRigidBody* m_pRigidBody = nullptr;
public:
	bool visual;
	uint m_iID;
	NewOctant(vector3 center, float size);
	void Display(void);
	uint Subdivide(uint ID, uint currentLevel, uint maxLevel);
	bool CheckValues(NewOctant* current);
	uint checking;
	NewOctant(uint maxSubNum = 0, uint idealEntityCount = 5);
	
private:
	void Init(void);
	void AssignSpaces(void);
	void IsColliding(void);
	void DimensionDisplay(uint index);
};
