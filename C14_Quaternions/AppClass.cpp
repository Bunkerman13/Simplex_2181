#include "AppClass.h"
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//initializing the model
	m_pModel = new Simplex::Model();

	//Load a model
	m_pModel->Load("Minecraft\\Steve.obj");

	m_pMesh = new MyMesh();

	m_pMesh->GenerateCube(2.f, C_RED);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Get a timer
	static uint uClock = m_pSystem->GenClock();
	float fTimer = m_pSystem->GetTimeSinceStart(uClock);
	float fDeltaTime = m_pSystem->GetDeltaTime(uClock);

#pragma region SLERP
	if (true)
	{
		quaternion q1;
		quaternion q2 = glm::angleAxis(glm::radians(359.9f), vector3(0.0f, 0.0f, 1.0f));
		float fPercentage = MapValue(fTimer, 0.0f, 5.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage);
		m_m4Steve = glm::toMat4(qSLERP);
		// why it scales when you do too much.  When it interpolates, tries to find shortest route, usually line, but sphereical interpolation
		// works on a sphere.  Because there is no difference between orienting at 360 or 0, it doesn't cause a proper change due to rounding errors
		// causing it to freak out and scale and do other weird things.
	}
#pragma endregion
#pragma region translate vector orientation into a matrix
	if (false)
	{
		matrix4 m4OrientX = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.x), vector3(1.0f, 0.0f, 0.0f));
		matrix4 m4OrientY = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.y), vector3(0.0f, 1.0f, 0.0f));
		matrix4 m4OrientZ = glm::rotate(IDENTITY_M4, glm::radians(m_v3Orientation.z), vector3(0.0f, 0.0f, 1.0f));

		matrix4 m4Orientation = m4OrientX * m4OrientY * m4OrientZ;
		m_m4Steve = glm::toMat4(m_qOrientation);
	}
#pragma endregion
#pragma region orientation using quaternions
	if (true)
	{
		m_m4Steve = glm::toMat4(m_qOrientation);
	}
#pragma endregion
	
	//Attach the model matrix that takes me from the world coordinate system
	m_pModel->SetModelMatrix(m_m4Steve);

	//Send the model to render list
	///m_pModel->AddToRenderList();

	
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Proj = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4Model = glm::translate(m_v3Orientation * 0.1f);
	//m4Proj = glm::ortho(-7.5f, 7.5f, -5.f, 5.f, .01f, 1000.f);  // not changing size or anything, just changing the viewpoint of the camera on the world
	
	float fFOV = 90.f;
	float fAspect = static_cast<float>(m_pSystem->GetWindowWidth()) / static_cast<float>(m_pSystem->GetWindowHeight());
	float fNear = .1f;
	float fFar = 20.f;
	m4Proj = glm::perspective(fFOV, fAspect, fNear, fFar);
	
	vector3 v3Pos = vector3(0.f, 0.f, 5.f);
	vector3 v3Target;
	vector3 v3Up = vector3(0.f, 1.f, 0.f);

	m4View = glm::lookAt(v3Pos, v3Target, v3Up);

	m_pMesh->Render(m4Proj, m4View, m4Model);
	
	matrix4 proj = m_pCameraMngr->GetProjectionMatrix();  // -1 uses the last one created
	matrix4 view = m_pCameraMngr->GetViewMatrix();

	///
	float fovy = m_fFovy;  // field of view
	float aspect = 1080.f/720.f; // aspect ratio  // can ask window for aspects
	float zNear = 0.0001f;  // near clipping plane // change to higher, the farther away things stop rendering
	float zFar = 1000.0f;  // far clipping plane
	proj = glm::perspective(fovy, aspect, zNear, zFar);

	///m_pCameraMngr->SetViewMatrix(view);
	///m_pCameraMngr->SetProjectionMatrix(proj);

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release model
	SafeDelete(m_pModel);
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}
