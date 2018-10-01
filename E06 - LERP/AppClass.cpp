#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(vector3(5.0f,3.0f,15.0f), ZERO_V3, AXIS_Y);

	m_pModel = new Simplex::Model();
	m_pModel->Load("Sorted\\WallEye.bto");
	
	m_stopsList.push_back(vector3(-4.0f, -2.0f, 5.0f));
	m_stopsList.push_back(vector3(1.0f, -2.0f, 5.0f));

	m_stopsList.push_back(vector3(-3.0f, -1.0f, 3.0f));
	m_stopsList.push_back(vector3(2.0f, -1.0f, 3.0f));

	m_stopsList.push_back(vector3(-2.0f, 0.0f, 0.0f));
	m_stopsList.push_back(vector3(3.0f, 0.0f, 0.0f));

	m_stopsList.push_back(vector3(-1.0f, 1.0f, -3.0f));
	m_stopsList.push_back(vector3(4.0f, 1.0f, -3.0f));

	m_stopsList.push_back(vector3(0.0f, 2.0f, -5.0f));
	m_stopsList.push_back(vector3(5.0f, 2.0f, -5.0f));

	m_stopsList.push_back(vector3(1.0f, 3.0f, -5.0f));
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

	// Draw the model
	m_pModel->PlaySequence();

	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	//calculate the current position
	static vector3 v3CurrentPos;
	static float percent = 0;
	static int position = 0;

	// used to help send object back to start from last element
	// NOTE: couldn't figure out effective use of swap as it so I used this instead
	static int subVal = 0;
	vector3 start = m_stopsList[position];
	vector3 end = m_stopsList[position + 1 - subVal];
	
	// uses built in lerp function
	v3CurrentPos = glm::lerp(start, end, percent);

	// increases percentage of lerp completed
	percent += 0.03f;

	// if percent is 1.0 or more, then it is completed
	if (percent >= 1.0f)
	{
		// percent resets for next lerp and position increments for new start and end
		percent = 0.0f;
		position++;

		// checks if the position is greater than or equal to size of list - 1
		if (position >= m_stopsList.size() - 1)
		{
			// changes subVal to equal list size for subtraction
			subVal = m_stopsList.size();

			// after one round through, changes elements back to 0 for restarting list order
			if (position == m_stopsList.size())
			{
				position = 0;
				subVal = 0;
			}		
		}
	}
		
	/// --------NOTES---------
	///static float percent = 0.0f;
	///static vector3 start(0, 0, 0);
	///static vector3 end(5, 0, 0);
	///vector3 position = glm::lerp(start, end, percent);
	///matrix4 m4Pos = glm::translate(IDENTITY_M4, m_stopsList[0]);

	///if (percent >= 1.0f)
	///{
		///std::swap(start, end);
		///percent = 0.0f;
	///}
	///percent += 0.01f;

	//your code goes here
	//v3CurrentPos = vector3(0.0f, 0.0f, 0.0f);
	//-------------------
	


	
	matrix4 m4Model = glm::translate(v3CurrentPos);
	m_pModel->SetModelMatrix(m4Model);

	m_pMeshMngr->Print("\nTimer: ");//Add a line on top
	m_pMeshMngr->PrintLine(std::to_string(fTimer), C_YELLOW);

	// Draw stops
	for (uint i = 0; i < m_stopsList.size(); ++i)
	{
		m_pMeshMngr->AddSphereToRenderList(glm::translate(m_stopsList[i]) * glm::scale(vector3(0.05f)), C_GREEN, RENDER_WIRE);
	}
	
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
	SafeDelete(m_pModel);
	//release GUI
	ShutdownGUI();
}