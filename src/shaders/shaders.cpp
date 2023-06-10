const char* fragment_shader = R"(
    #version 330 core

    out vec3 color;

    uniform float time;  
    uniform int isPressed;

    void main(){
      float pulsation = 0.6 + abs(0.4 * sin(3.14159 * time));
      if (isPressed != 0) {
        color = vec3(pulsation, 0., 0.);
      }
      else {
      color = vec3(pulsation,pulsation,pulsation);
      }
    }
)";

const char* vertex_shader = R"(
  #version 330 core
  // Input vertex data, different for all executions of this shader.
  layout(location = 0) in vec3 vertexPosition_modelspace;
  
  // Values that stay constant for the whole mesh.
  uniform mat4 MVP;
  
  void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
  }
)";