#include "Simplex/Simplex.h"
#include "MyEntityManager.h"
using namespace Simplex;

class NewOctant
{
	// EntityManager singleton
	MyEntityManager* m_pEntityMngr = nullptr; 

	// children of octant
	NewOctant* m_pChild[8];

	// octant's rigidbody
	MyRigidBody* m_pRigidBody = nullptr;

	// the number that contributes to the octant's dimension
	uint m_iID;
public:
	// used to keep track of idealEntityCount
	uint idealEntityCount;
	// used for DimensionDisplay
	uint checking;
	/*
	Display
	displays the rigidbodies
	*/
	void Display(void);
	/*
	Default Constructor
	Constructor called on the root octant
	*/
	NewOctant(uint maxSubNum = 0, uint idEntCnt = 5);
private:
	/*
	Subdivide
	checks if the current set of children are nullptr.
	Creates new children if they're nullptr.
	Subdivides again if they are not
	*/
	uint Subdivide(uint ID, uint currentLevel, uint maxLevel);
	/*
	Overloaded Constructor
	Used to create children
	*/
	NewOctant(vector3 center, float size);
	/*
	CheckValues
	checks if octant needs to be made, if not then returns false
	if so, returns true.
	*/
	bool CheckValues(NewOctant* current);
	/*
	Init
	Initial values are instantiated and the
	root octant and its children are created
	*/
	void Init(void);
	/*
	AssignSpaces
	Finds all of the leaves and
	calls the IsColliding method on them
	*/
	void AssignSpaces(void);
	/*
	IsColliding
	Checks if any of the entities are
	colliding with the current ocant's rigidbody
	*/
	void IsColliding(void);
	/*
	DimensionDisplay
	Custom display that that helped check
	out the different octants that were colliding
	*/
	void DimensionDisplay(uint index);
};
