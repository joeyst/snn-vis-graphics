
#include "Draw.h"

/* Drawing Neurons, Synapses, and Boxes. */
void DrawNeuron(vector<int> xyz, vector<Proportion> rgba) {
  glPushMatrix();
  glColor4f(
    rgba[0],
    rgba[1],
    rgba[2],
    rgba[3]
  );
  glTranslatef(
    (float)xyz[0] * (2 * (NEURON_RADIUS + NEURON_SPACING)),
    (float)xyz[1] * (2 * (NEURON_RADIUS + NEURON_SPACING)),
    (float)xyz[2] * (2 * (NEURON_RADIUS + NEURON_SPACING))
  );
  glCallList(neuron);
  glPopMatrix();
}

void DrawSynapse(vector<int> start, vector<int> end, vector<Proportion> rgba) {
  /* ADAPTED FROM CHATGPT WITH HELP FROM A FRIEND OF MINE. */
  glPushMatrix();
  glColor4f(rgba[0], rgba[1], rgba[2], rgba[3]);

  vector<float> start_coords = GetCoordsFromPoint(start);
  vector<float> end_coords = GetCoordsFromPoint(end);
  vector<float> dxyz = sub(start_coords, end_coords);
  float distance = EuclidianNorm(dxyz);

  glTranslatef(start_coords[0], start_coords[1], start_coords[2]);

  glm::vec3 lineDirection(0.0f, 1.0f, 0.0f); 
  glm::vec3 targetVector(dxyz[0], dxyz[1], dxyz[2]);

  glm::vec3 rotationAxis = glm::cross(lineDirection, targetVector);
  rotationAxis = glm::normalize(rotationAxis);

  float rotationAngle = acos(glm::dot(lineDirection, targetVector) / (glm::length(lineDirection) * glm::length(targetVector)));
  glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, rotationAxis);
  glMultMatrixf(glm::value_ptr(rotationMatrix)); 

  glScalef(1.f, distance, 1.f);
  glCallList(synapse);
  glPopMatrix();
}

void DrawBox(vector<int> center, int r, vector<Proportion> rgba) {
  glPushMatrix();
  glColor4f(rgba[0], rgba[1], rgba[2], rgba[3]);
  glTranslatef(
    (float)center[0] * (2 * (NEURON_RADIUS + NEURON_SPACING)),
    (float)center[1] * (2 * (NEURON_RADIUS + NEURON_SPACING)),
    (float)center[2] * (2 * (NEURON_RADIUS + NEURON_SPACING))
  );
  glCallList(box);
  glPopMatrix();
}

/* Initializing display lists. */ 
void InitNeuronDL() {
  neuron = glGenLists(1);
  glNewList(neuron, GL_COMPILE);
  OsuSphere(SPHERE_RADIUS, SPHERE_SLICES, SPHERE_STACKS);
  glEndList();
}

void InitSynapseDL() {
  synapse = glGenLists(1);
  glNewList(synapse, GL_COMPILE);
  OsuCone(0.25f * NEURON_RADIUS, 0.15f * NEURON_RADIUS, 1.f, SPHERE_SLICES, SPHERE_STACKS);
  glEndList();
}

void InitBoxDL() {
    glNewList( box, GL_COMPILE );
		glBegin( GL_QUADS );

    float dx = 1.f;
    float dy = 1.f;
    float dz = 1.f;

			glColor3f( 1., 0., 0. );

				glNormal3f( 1., 0., 0. );
					glVertex3f(  dx, -dy,  dz );
					glVertex3f(  dx, -dy, -dz );
					glVertex3f(  dx,  dy, -dz );
					glVertex3f(  dx,  dy,  dz );

				glNormal3f(-1., 0., 0.);
					glVertex3f( -dx, -dy,  dz);
					glVertex3f( -dx,  dy,  dz );
					glVertex3f( -dx,  dy, -dz );
					glVertex3f( -dx, -dy, -dz );

			glColor3f( 0., 1., 0. );

				glNormal3f(0., 1., 0.);
					glVertex3f( -dx,  dy,  dz );
					glVertex3f(  dx,  dy,  dz );
					glVertex3f(  dx,  dy, -dz );
					glVertex3f( -dx,  dy, -dz );

				glNormal3f(0., -1., 0.);
					glVertex3f( -dx, -dy,  dz);
					glVertex3f( -dx, -dy, -dz );
					glVertex3f(  dx, -dy, -dz );
					glVertex3f(  dx, -dy,  dz );

			glColor3f(0., 0., 1.);

				glNormal3f(0., 0., 1.);
					glVertex3f(-dx, -dy, dz);
					glVertex3f( dx, -dy, dz);
					glVertex3f( dx,  dy, dz);
					glVertex3f(-dx,  dy, dz);

				glNormal3f(0., 0., -1.);
					glVertex3f(-dx, -dy, -dz);
					glVertex3f(-dx,  dy, -dz);
					glVertex3f( dx,  dy, -dz);
					glVertex3f( dx, -dy, -dz);

		glEnd( );

	glEndList( );
}


/* Synapse rotation logic. */

vector<float> GetCoordsFromPoint(vector<int> point) {
  vector<float> coords(3);
  for (int i = 0; i < 3; i++) {
    coords[i] = ((float)point[i] * (2 * (NEURON_RADIUS + NEURON_SPACING)));
  }
  return coords;
}

float EuclidianNorm(vector<float> point) {
  float res = 0.f;
  for (int i = 0; i < 3; i++) {
    res += (point[i] * point[i]);
  }
  return sqrtf(res);
}

vector<float> sub(vector<float> start, vector<float> end) {
  vector<float> res(3);
  for (int i = 0; i < 3; i++) {
    res[i] = end[i] - start[i];
  }
  return res;
}
