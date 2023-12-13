
#include "Draw.h"

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
