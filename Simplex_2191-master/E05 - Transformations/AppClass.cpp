#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_BLUE);
	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);
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
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f,2.0f,2.0f));
	static float value = 0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 2.0f, 3.0f));
	value += 0.01f;

	//matrix4 m4Model = m4Translate * m4Scale;
	matrix4 m4Model = m4Scale * m4Translate;

	m_pMesh->Render(m4Projection, m4View, m4Model);
	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(1.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(-1.0f, 1.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(3.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(4.0f, 0.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(5.0f, 1.0f, 0.0f)));

	for (int i = -1; i < 6; i++)
	{
		m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(i, 2.0f, 0.0f)));
	}

	for (int i = -3; i < 8; i++)
	{
		m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(i, 3.0f, 0.0f)));
	}

	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(-3, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(-3, 1.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(7, 2.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(7, 1.0f, 0.0f)));

	for (int i = -2; i < 7; i++)
	{
		if(i != 0 && i != 4)
			m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(i, 4.0f, 0.0f)));
	}

	for (int i = -1; i < 6; i++)
		m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(i, 5.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(0.0f, 6.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(-1.0f, 7.0f, 0.0f)));

	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(4.0f, 6.0f, 0.0f)));
	m_pMesh->Render(m4Projection, m4View, m4Model * glm::translate(IDENTITY_M4, vector3(5.0f, 7.0f, 0.0f)));


	
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