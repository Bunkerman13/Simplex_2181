#include "AppClass.h"
void Application::InitVariables(void)
{

	//init the mesh
	m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	m_pMesh->GenerateCone(2.0f, 5.0f, 3, C_WHITE);
	//m_pMesh->GenerateCone(1.0f, 1.0f, 6, C_RED);
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 12, ZERO_V3, AXIS_Y);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	

	//quaternion xRot = glm::angleAxis(glm::radians(m_v3Rotation.x), AXIS_X);
	//quaternion yRot = glm::angleAxis(glm::radians(m_v3Rotation.y), AXIS_Y);
	//quaternion zRot = glm::angleAxis(glm::radians(m_v3Rotation.z), AXIS_Z);

	

	///glm::quat q; //same as quaternion
	///quaternion qq = glm::angleAxis(glm::radians(1.0f), AXIS_Z);
	///static quaternion qqq = q * qq;
	///qqq = qqq * qq;

	m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_qOrientation));
	///m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_m4Model));

	//m_qOrientation = m_qOrientation * glm::angleAxis(glm::radians(1.0f), vector3(1.0f));
	//m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_qOrientation));
	
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
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}