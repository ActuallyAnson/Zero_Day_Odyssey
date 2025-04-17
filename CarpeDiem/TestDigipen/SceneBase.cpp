#include "SceneBase.h"

#include <sstream>

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	// Black background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//Camera Initialise?
	//camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//Generate Base UI
}

void SceneBase::Update(double dt)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//Keyboard Section
	fps = (float)(1.f / dt);
}

//void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
//{
//	if(!mesh || mesh->textureID <= 0)
//		return;
//	
//	glDisable(GL_DEPTH_TEST);
//	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
//	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
//	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
//	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
//	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
//	for(unsigned i = 0; i < text.length(); ++i)
//	{
//		Mtx44 characterSpacing;
//		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
//		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//	
//		mesh->Render((unsigned)text[i] * 6, 6);
//	}
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
//	glEnable(GL_DEPTH_TEST);
//}
//
//void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
//{
//	if(!mesh || mesh->textureID <= 0)
//		return;
//
//	glDisable(GL_DEPTH_TEST);
//	Mtx44 ortho;
//	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
//	projectionStack.PushMatrix();
//	projectionStack.LoadMatrix(ortho);
//	viewStack.PushMatrix();
//	viewStack.LoadIdentity();
//	modelStack.PushMatrix();
//	modelStack.LoadIdentity();
//	modelStack.Translate(x, y, 0);
//	modelStack.Scale(size, size, size);
//	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
//	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
//	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
//	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
//	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
//	for(unsigned i = 0; i < text.length(); ++i)
//	{
//		Mtx44 characterSpacing;
//		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
//		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
//		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//
//		mesh->Render((unsigned)text[i] * 6, 6);
//	}
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
//	modelStack.PopMatrix();
//	viewStack.PopMatrix();
//	projectionStack.PopMatrix();
//	glEnable(GL_DEPTH_TEST);
//}
//
//void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
//{
//	Mtx44 MVP, modelView, modelView_inverse_transpose;
//	glDisable(GL_DEPTH_TEST);
//	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
//	if(enableLight && bLightEnabled)
//	{
//		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
//		modelView = viewStack.Top() * modelStack.Top();
//		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
//		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
//		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
//		
//		//load material
//		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
//		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
//		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
//		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
//	}
//	else
//	{	
//		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
//	}
//	if(mesh->textureID > 0)
//	{
//		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
//		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
//	}
//	else
//	{
//		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
//	}
//	mesh->Render();
//	if(mesh->textureID > 0)
//	{
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//	glEnable(GL_DEPTH_TEST);
//}
//
//void SceneBase::Render()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}

void SceneBase::Exit()
{
	// Cleanup VBO
	//for(int i = 0; i < NUM_GEOMETRY; ++i)
	//{
	//	if(meshList[i])
	//		delete meshList[i];
	//}
	//glDeleteProgram(m_programID);
	//glDeleteVertexArrays(1, &m_vertexArrayID);
}
