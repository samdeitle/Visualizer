/*=========================================================================

  Program:   Visualization Toolkit
  Module:    SpecularSpheres.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This examples demonstrates the effect of specular lighting.
//
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackballActor.h>
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


vtkSmartPointer<vtkRenderer> ren3;
vtkSmartPointer<vtkRenderWindow> renWin;
unsigned char RED   = 0;
bool		  _R_   = false;
unsigned char GREEN = 0;
bool		  _G_   = false;
unsigned char BLUE  = 0;
bool		  _B_   = false;

class Triangle
{
  public:
      double         X[3];
      double         Y[3];
      double         Z[3];
};


class vtk441InteractorStyle : public vtkInteractorStyleTrackballCamera
{
        public:
                static vtk441InteractorStyle *New();

                vtk441InteractorStyle()
                {
                        shouldPick = false;
                }

                // virtual void OnChar()
                // {
                //         vtkRenderWindowInteractor *rwi = this->Interactor;
                //         char pressedChar = rwi->GetKeyCode();
                //         if (pressedChar == 'p')
                //         {
                //                 cerr << "Should pick!" << endl;
                //                 shouldPick = true;
                //         }
                //         vtkInteractorStyleTrackballCamera::OnChar();
                // };

                void TransitionColor(int r, int g, int b)
                {
                  int inc = 10;
                  int r_inc = (RED   - r)/inc;
                  int g_inc = (GREEN - g)/inc;
                  int b_inc = (BLUE  - b)/inc;
                  for (int i = 0; i < inc; ++i)
                  {
                    RED   -= r_inc;
                    BLUE  -= b_inc;
                    GREEN -= g_inc;
                  }
                }

                virtual void OnKeyDown()
                {
                 	vtkRenderWindowInteractor *rwi = this->Interactor;
              		vtkRenderWindow *rw            = rwi->GetRenderWindow();

              		std::string key = rwi->GetKeySym();
					cout << "Pressed " << key << endl;
//A -- Turn RED off/on
					if      (key.compare("a") == 0)
					{
						if (_R_){_R_ = false;}
						else    {_R_ = true;}
						cerr << "_R_: " << _R_ << endl;
					}
//S -- Turn GREEN off/on
					else if (key.compare("s") == 0)
					{
						if (_G_){_G_ = false;}
						else    {_G_ = true;}
						cerr << "_G_: " << _G_ << endl;
					}
//D -- Turn BLUE off/on
					else if (key.compare("d") == 0)
					{
						if (_B_){_B_ = false;}
						else    {_B_ = true;}
						cerr << "_B_: " << _B_ << endl;
					}
//UP -- Increase engaged channels          
					else if (key.compare("Up") == 0)
					{
						if(_R_)
						{
							/*if (RED < 250)*/  {RED += 10;}
						}
						if(_G_)
						{
							if (GREEN < 250){GREEN += 10;}
						}
						if(_B_)
						{
							if (BLUE < 250) {BLUE += 10;}
						}
						cerr << "( " << (int)RED << ", " << (int)GREEN << ", " << (int)BLUE << ")" << endl; 
						rw->Render();
					}
//DOWN -- Decrease engaged channels
					else if (key.compare("Down") == 0)
					{
						if(_R_)
						{
							if (RED >= 10)  {RED -= 10;}
						}
						if(_G_)
						{
							if (GREEN >= 10){GREEN -= 10;}
						}
						if(_B_)
						{
							if (BLUE >= 10) {BLUE -= 10;}
						}
						cerr << "( " << (int)RED << ", " << (int)GREEN << ", " << (int)BLUE << ")" << endl; 
						rw->Render();
					}

          else if (key.compare("t") == 0)
          {
            cout << "Enter R, G, B: \n";
            int R, G, B;
            cin >> R, G, B;
            int inc = 100;
            int r_inc = ((int)RED   - R)/inc;
            int g_inc = ((int)GREEN - G)/inc;
            int b_inc = ((int)BLUE  - B)/inc;
            for (int i = 0; i < inc; ++i)
            {
               RED   -= r_inc;
               BLUE  -= b_inc;
               GREEN -= g_inc;
               rw->Render();
            }
          }

          else if (key.compare("z") == 0)
          {
            for(int i = 0; i < 10; i++)
            {
            RED   = 255;
            GREEN = 255;
            BLUE  = 0;
            usleep(100000);
            rw->Render();
            GREEN = 0;
            BLUE  = 255;
            usleep(100000);
            rw->Render();
            RED   = 0;
            GREEN = 255;
            usleep(100000);
            rw->Render();
          }

          }

                };

                virtual void OnLeftButtonDown()
                {
                        if (shouldPick)
                        {
                                vtkRenderWindowInteractor *rwi = this->Interactor;
                                vtkRenderWindow *rw = rwi->GetRenderWindow();
                                int *size = rw->GetSize();
                                int x = this->Interactor->GetEventPosition()[0];
                                int y = this->Interactor->GetEventPosition()[1];
                                vtkRenderer *ren = rwi->FindPokedRenderer(x, y);
                                double pos[3];
                                pos[0] = 2.0*((double)x/(double)size[0])-1;
                                pos[1] = 2.0*((double)y/(double)size[1])-1;
                                pos[2] = ren->GetZ(x, y);
                                cerr << "Picked on " << x << ", " << y << endl;
                                cerr << " = " << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;
                                ren->ViewToWorld(pos[0], pos[1], pos[2]);
                                cerr << " converted to " << pos[0] << ", " << pos[1] << ", " << pos[2] << endl;

                                shouldPick = false;
                        }
                        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
                };

        private:
                bool shouldPick;
};
vtkStandardNewMacro(vtk441InteractorStyle);


class vtk441Mapper : public vtkOpenGLPolyDataMapper
{
  protected:
   GLuint displayList;
   bool   initialized;

  public:
   vtk441Mapper()
   {
     initialized = false;
   }
    
   void
   RemoveVTKOpenGLStateSideEffects()
   {
     float Info[4] = { 0, 0, 0, 1 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Info);
     float ambient[4] = { 1,1, 1, 1.0 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
     float diffuse[4] = { 1, 1, 1, 1.0 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
     float specular[4] = { 1, 1, 1, 1.0 };
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   }


   void SetupLight(void)
   {
       glEnable(GL_LIGHTING);
       glEnable(GL_LIGHT0);
       GLfloat diffuse0[4] = { 0.6, 0.6, 0.6, 1 };
       GLfloat ambient0[4] = { 0.2, 0.2, 0.2, 1 };
       GLfloat specular0[4] = { 0.0, 0.0, 0.0, 1 };
       GLfloat pos0[4] = { 0, .707, 0.707, 0 };
       glLightfv(GL_LIGHT0, GL_POSITION, pos0);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
       glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
       glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
       glEnable(GL_LIGHT1);
       GLfloat pos1[4] = { .707, -.707, 0 };
       glLightfv(GL_LIGHT1, GL_POSITION, pos1);
       glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
       glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
       glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);
       GLfloat pos2[4] = { 0, 1, 0, 0};
       glEnable(GL_LIGHT2);
       glLightfv(GL_LIGHT2, GL_POSITION, pos2);
       glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse0);
       glLightfv(GL_LIGHT2, GL_AMBIENT, ambient0);
       glLightfv(GL_LIGHT2, GL_SPECULAR, specular0);
       glDisable(GL_LIGHT3);
       glDisable(GL_LIGHT5);
       glDisable(GL_LIGHT6);
       glDisable(GL_LIGHT7);
   }
};

class vtk441MapperPart3 : public vtk441Mapper
{
 public:
   static vtk441MapperPart3 *New();
   
   GLuint displayList;
   bool   initialized;
   

   vtk441MapperPart3()
   {
     initialized = false;
   }

   void DrawCylinder()
   {
       int nfacets = 30;
       glBegin(GL_TRIANGLES);
       for (int i = 0 ; i < nfacets ; i++)
       {
           double angle = 3.14159*2.0*i/nfacets;
           double nextAngle = (i == nfacets-1 ? 0 : 3.14159*2.0*(i+1)/nfacets);
           glNormal3f(0,0,1);
           glVertex3f(0, 0, 1);
           glVertex3f(cos(angle), sin(angle), 1);
           glVertex3f(cos(nextAngle), sin(nextAngle), 1);
           glNormal3f(0,0,-1);
           glVertex3f(0, 0, 0);
           glVertex3f(cos(angle), sin(angle), 0);
           glVertex3f(cos(nextAngle), sin(nextAngle), 0);
       }
       glEnd();
       glBegin(GL_QUADS);
       for (int i = 0 ; i < nfacets ; i++)
       {
           double angle = 3.14159*2.0*i/nfacets;
           double nextAngle = (i == nfacets-1 ? 0 : 3.14159*2.0*(i+1)/nfacets);
           glNormal3f(cos(angle), sin(angle), 0);
           glVertex3f(cos(angle), sin(angle), 1);
           glVertex3f(cos(angle), sin(angle), 0);
           glNormal3f(cos(nextAngle), sin(nextAngle), 0);
           glVertex3f(cos(nextAngle), sin(nextAngle), 0);
           glVertex3f(cos(nextAngle), sin(nextAngle), 1);
       }
       glEnd();
   }
   std::vector<Triangle> SplitTriangle(std::vector<Triangle> &list)
   {
       std::vector<Triangle> output(4*list.size());
       for (unsigned int i = 0 ; i < list.size() ; i++)
       {
           double mid1[3], mid2[3], mid3[3];
           mid1[0] = (list[i].X[0]+list[i].X[1])/2;
           mid1[1] = (list[i].Y[0]+list[i].Y[1])/2;
           mid1[2] = (list[i].Z[0]+list[i].Z[1])/2;
           mid2[0] = (list[i].X[1]+list[i].X[2])/2;
           mid2[1] = (list[i].Y[1]+list[i].Y[2])/2;
           mid2[2] = (list[i].Z[1]+list[i].Z[2])/2;
           mid3[0] = (list[i].X[0]+list[i].X[2])/2;
           mid3[1] = (list[i].Y[0]+list[i].Y[2])/2;
           mid3[2] = (list[i].Z[0]+list[i].Z[2])/2;
           output[4*i+0].X[0] = list[i].X[0];
           output[4*i+0].Y[0] = list[i].Y[0];
           output[4*i+0].Z[0] = list[i].Z[0];
           output[4*i+0].X[1] = mid1[0];
           output[4*i+0].Y[1] = mid1[1];
           output[4*i+0].Z[1] = mid1[2];
           output[4*i+0].X[2] = mid3[0];
           output[4*i+0].Y[2] = mid3[1];
           output[4*i+0].Z[2] = mid3[2];
           output[4*i+1].X[0] = list[i].X[1];
           output[4*i+1].Y[0] = list[i].Y[1];
           output[4*i+1].Z[0] = list[i].Z[1];
           output[4*i+1].X[1] = mid2[0];
           output[4*i+1].Y[1] = mid2[1];
           output[4*i+1].Z[1] = mid2[2];
           output[4*i+1].X[2] = mid1[0];
           output[4*i+1].Y[2] = mid1[1];
           output[4*i+1].Z[2] = mid1[2];
           output[4*i+2].X[0] = list[i].X[2];
           output[4*i+2].Y[0] = list[i].Y[2];
           output[4*i+2].Z[0] = list[i].Z[2];
           output[4*i+2].X[1] = mid3[0];
           output[4*i+2].Y[1] = mid3[1];
           output[4*i+2].Z[1] = mid3[2];
           output[4*i+2].X[2] = mid2[0];
           output[4*i+2].Y[2] = mid2[1];
           output[4*i+2].Z[2] = mid2[2];
           output[4*i+3].X[0] = mid1[0];
           output[4*i+3].Y[0] = mid1[1];
           output[4*i+3].Z[0] = mid1[2];
           output[4*i+3].X[1] = mid2[0];
           output[4*i+3].Y[1] = mid2[1];
           output[4*i+3].Z[1] = mid2[2];
           output[4*i+3].X[2] = mid3[0];
           output[4*i+3].Y[2] = mid3[1];
           output[4*i+3].Z[2] = mid3[2];
       }
       return output;
   }
   void DrawSphere()
   {
       int recursionLevel = 4;
       Triangle t;
       t.X[0] = 1;
       t.Y[0] = 0;
       t.Z[0] = 0;
       t.X[1] = 0;
       t.Y[1] = 1;
       t.Z[1] = 0;
       t.X[2] = 0;
       t.Y[2] = 0;
       t.Z[2] = 1;
       std::vector<Triangle> list;
       list.push_back(t);
       for (int r = 0 ; r < recursionLevel ; r++)
       {
           list = SplitTriangle(list);
       }

       // really draw `
       for (int octent = 0 ; octent < 8 ; octent++)
       {
           glPushMatrix();
           glRotatef(90*(octent%4), 0, 1, 0);
           if (octent >= 4)
               glRotatef(180, 0, 0, 1);
           glBegin(GL_TRIANGLES);
           for (unsigned int i = 0 ; i < list.size() ; i++)
           {
               for (int j = 0 ; j < 3 ; j++)
               {
                   double ptMag = sqrt(list[i].X[j]*list[i].X[j]+
                                       list[i].Y[j]*list[i].Y[j]+
                                       list[i].Z[j]*list[i].Z[j]);
                   glNormal3f(list[i].X[j]/ptMag, list[i].Y[j]/ptMag, list[i].Z[j]/ptMag);
                   glVertex3f(list[i].X[j]/ptMag, list[i].Y[j]/ptMag, list[i].Z[j]/ptMag);
               }
           }
           glEnd();
           glPopMatrix();
       }
   }

   void Brown(void) { glColor3ub(205, 133, 63); };
   void LightBrown(void) { glColor3ub(245, 222, 179); };
   void DarkBrown(void) { glColor3ub(162, 82, 45); };
   void Pink(void) { glColor3ub(250, 128, 114); };
   void White(void) { glColor3ub(255, 255, 255); };
   void Black(void) { glColor3ub(0, 0, 0); };
   void BlueGrey(void) { glColor3ub(128, 145, 183); };
   void Red(void) { glColor3ub(255, 0, 0); };

   // void DrawEyeball(void)
   // {
   //     glPushMatrix();
   //     White();
   //     glScalef(eyeballSize, eyeballSize, eyeballSize);
   //     DrawSphere();
   //     Black();
   //     glTranslatef(1-pupilSize/2, 0, 0);
   //     glScalef(pupilSize, pupilSize, pupilSize);
   //     DrawSphere();
   //     glPopMatrix();
   // }
   
   // void DrawCapsule(void)
   // {
	  //  glPushMatrix();

	  //  glScalef(bodyLength, bodyWidth, bodyHeight);
	  //  glRotatef(90, 0, 1 ,0);
	  //  DrawCylinder();
	  //  glPushMatrix();
	  //  glTranslatef(0, 0, +1);
	  //  DrawSphere();
	  //  glTranslatef(0, 0, -1);
	  //  DrawSphere();
	  //  glPopMatrix();
	  //  glPopMatrix();
   // }
   
   // void DrawNeck(void)
   // {
	  //  glPushMatrix();
	  //  glRotatef(-20, 0, -1, 0);
	  //  glScalef(.6, .6, 1.75);
	  //  glTranslatef(0, 0, -bodyHeight);
	  //  DrawCylinder();
	  //  glPopMatrix();
   // }
   
   // void DrawLeg(void)
   // {
	  //  BlueGrey();
	  //  glPushMatrix();
	  //  glScalef(.3, .3, 2.5);


	  //  DrawCylinder();
	  //  Black();
	  //  glPushMatrix();
	  //  glTranslatef(.45, 0, 0);
	  //  glScalef(1.65, 1.45, .1);
	  //  DrawSphere();
	  //  glPopMatrix();
	   


	  //  glPopMatrix();
   // }

   virtual void RenderPiece(vtkRenderer *ren, vtkActor *act)
   {
   	// if (!initialized)
   	// {  		
       RemoveVTKOpenGLStateSideEffects();
       SetupLight();
    //    initialized = true;
    // }

       glEnable(GL_COLOR_MATERIAL);
    
       glMatrixMode(GL_MODELVIEW);

       glColor3ub(RED, GREEN, BLUE);
       glPushMatrix();
       glScalef(15, 15, 15);
       DrawSphere();
       glPopMatrix();
       float r, g, b;
       r = (255.0 - RED)/255.0;
       g = (255.0 - GREEN)/255.0;
       b = (255.0 - BLUE)/255.0;
       ren->SetBackground(r, g, b);
   }
};

vtkStandardNewMacro(vtk441MapperPart3);


int main()
{
  // Dummy input so VTK pipeline mojo is happy.
  //
  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetThetaResolution(100);
  sphere->SetPhiResolution(50);

  vtkSmartPointer<vtk441MapperPart3> win3Mapper =
    vtkSmartPointer<vtk441MapperPart3>::New();
  win3Mapper->SetInputConnection(sphere->GetOutputPort());

  vtkSmartPointer<vtkActor> win3Actor =
    vtkSmartPointer<vtkActor>::New();
  win3Actor->SetMapper(win3Mapper);

  ren3 = vtkSmartPointer<vtkRenderer>::New();

  renWin = vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren3);
  ren3->SetViewport(0, 0, 1, 1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

    vtk441InteractorStyle *style = vtk441InteractorStyle::New();
  iren->SetInteractorStyle(style);

  // Add the actors to the renderer, set the background and size.
  //
  bool doWindow3 = true;
  if (doWindow3)
      ren3->AddActor(win3Actor);
  ren3->SetBackground(1, 1, 1);
  renWin->SetSize(1000, 1000);

  // Set up the lighting.
  //
  vtkSmartPointer<vtkLight> light =
    vtkSmartPointer<vtkLight>::New();
  light->SetFocalPoint(1.875,0.6125,0);
  light->SetPosition(0.875,1.6125,1);
  ren3->AddLight(light);

  ren3->GetActiveCamera()->SetFocalPoint(0,0,0);
  ren3->GetActiveCamera()->SetPosition(0,0,70);
  ren3->GetActiveCamera()->SetViewUp(0,1,0);
  ren3->GetActiveCamera()->SetClippingRange(20, 120);
  ren3->GetActiveCamera()->SetDistance(70);
  
  // This starts the event loop and invokes an initial render.
  //
  ((vtkInteractorStyle *)iren->GetInteractorStyle())->SetAutoAdjustCameraClippingRange(0);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}




