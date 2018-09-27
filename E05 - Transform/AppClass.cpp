#include "AppClass.h"
void Application::InitVariables(void)
{
	//Make MyMesh object
	/*m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(2.0f, C_BROWN);

	//Make MyMesh object
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateCube(1.0f, C_WHITE);*/

	for (int x = 0; x < 46; x++)
	{
		cube = new MyMesh();
		cube->GenerateCube(0.5f, C_BLACK);
		invaderCubes.push_back(cube);
	}
	
		
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
	///matrix4 m4Model = matrix4(1.0f);  // IDENTITY_M4 == identity matrix also
	///m4Model = ToMatrix4(m_qArcBall);
	///matrix4 scale = glm::scale(vector3(5.0f));
	///matrix4 scale = IDENTITY_M4 * glm::scale(vector3(5.0f)); == glm::scale(IDENTITY_M4 ,vector3(5.0f));
	///matrix4 scale = glm::scale(IDENTITY_M4 ,vector3(5.0f));
	///matrix4 translate = glm::translate(IDENTITY_M4 ,vector3(1.0f, 0, 0));

	///matrix4 translate = glm::translate(scale, vector3(1.0f, 0, 0)); // same as scale * translation with identities

	///matrix4 m4Model = scale * translate;  // IDENTITY_M4 == identity matrix also
	///matrix4 m4Model = translate * scale;  // not the same as above

	///matrix4 m4Model = translate;
	
	matrix4 m4Model = glm::translate(vector3(-1.5f + value, 2.0f, 0.0f));

	vector3 pos(-1.5f + value, 1, 0);

	float var = 0;
	for (int x = 0; x < 25; x++)
	{
		
		if (x < 1)
		{
			invaderCubes[x]->Render(m4Projection, m4View, m4Model);
			m4Model = glm::translate(vector3(1.5f + value, 2.0f, 0.0f));
			invaderCubes[x + 23]->Render(m4Projection, m4View, m4Model);
		}
		else if (x < 2)
		{
			m4Model = glm::translate(vector3(-1.0f + value, 1.5f, 0.0f));
			invaderCubes[x]->Render(m4Projection, m4View, m4Model);
			m4Model = glm::translate(vector3(1.0f + value, 1.5f, 0.0f));
			invaderCubes[x + 23]->Render(m4Projection, m4View, m4Model);
		}
		else if (x < 5)
		{
			m4Model = glm::translate(vector3(-1.5f + var + value, 1, 0));
			invaderCubes[x]->Render(m4Projection, m4View, m4Model);
			m4Model = glm::translate(vector3(1.5f - var + value, 1, 0));
			invaderCubes[x + 23]->Render(m4Projection, m4View, m4Model);
			var += 0.5f;
			if (x == 4)
				var = 0;
		}
		else if (x < 9)
		{
			if (x != 7)
			{
				m4Model = glm::translate(vector3(-2.0f + var + value, 0.5f, 0));
				invaderCubes[x]->Render(m4Projection, m4View, m4Model);
				m4Model = glm::translate(vector3(2.0f - var + value, 0.5f, 0));
				invaderCubes[x + 23]->Render(m4Projection, m4View, m4Model);
			}
			
			var += 0.5f;
			if (x == 8)
				var = 0;
		}
		else if (x < 14)
		{
			
			
			m4Model = glm::translate(vector3(-2.5f + var + value, 0.0f, 0));
			invaderCubes[x]->Render(m4Projection, m4View, m4Model);
			m4Model = glm::translate(vector3(2.5f - var + value, 0.0f, 0));
			invaderCubes[x + 23]->Render(m4Projection, m4View, m4Model);
			

			var += 0.5f;
			if (x == 13)
				var = 0;
				
		}
		else if (x < 19)
		{
			if (x != 15)
			{
				m4Model = glm::translate(vector3(-2.5f + var + value, -0.5f, 0));
				invaderCubes[x]->Render(m4Projection, m4View, m4Model);
				m4Model = glm::translate(vector3(2.5f - var + value, -0.5f, 0));
				invaderCubes[x + 23]->Render(m4Projection, m4View, m4Model);
			}

			var += 0.5f;
			if (x == 18)
				var = 0;
		}
		else if (x < 22)
		{
			if (x != 20)
			{
				m4Model = glm::translate(vector3(-2.5f + var + value, -1.0f, 0));
				invaderCubes[x]->Render(m4Projection, m4View, m4Model);
				m4Model = glm::translate(vector3(2.5f - var + value, -1.0f, 0));
				invaderCubes[x + 23]->Render(m4Projection, m4View, m4Model);
			}

			var += 0.5f;
			if (x == 21)
				var = 0;
		
		}
		else if (x < 24)
		{
			m4Model = glm::translate(vector3(-1.0f + var + value, -1.5f, 0));
			invaderCubes[x]->Render(m4Projection, m4View, m4Model);
			m4Model = glm::translate(vector3(1.0f - var + value, -1.5f, 0));
			invaderCubes[x + 21]->Render(m4Projection, m4View, m4Model);

			if (x == 23)
			{
				m4Model = glm::translate(vector3(value, 1, 0));
				invaderCubes[24]->Render(m4Projection, m4View, m4Model);
				m4Model = glm::translate(vector3(value, 0.5f, 0));
				invaderCubes[25]->Render(m4Projection, m4View, m4Model);
				m4Model = glm::translate(vector3(value, 0, 0));
				invaderCubes[44]->Render(m4Projection, m4View, m4Model);
				m4Model = glm::translate(vector3(value, -0.5f, 0));
				invaderCubes[45]->Render(m4Projection, m4View, m4Model);
			}
			

			var += 0.5f;
		}
		
	}


	if (left)
	{
		value += 0.05f;
		if (value > 5.0f)
			left = !left;
	}
	else
	{
		value -= 0.05f;
		if (value < -5.0)
			left = !left;
	}
		
	
	

	///m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall));
	///m_pMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3( 3.0f, 0.0f, 0.0f)));
		
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
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}

	for (int x = 0; x < invaderCubes.size(); x++)
	{
		if (invaderCubes[x] != nullptr)
		{
			delete invaderCubes[x];
			invaderCubes[x] = nullptr;
		}
		SafeDelete(invaderCubes[x]);
	}

	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}