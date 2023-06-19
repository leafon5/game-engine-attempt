#include "pch.h"

#include "classes/triangle.hpp"
#include "classes/shader.hpp"

#include "managers/TriangleManager.hpp"

#include "shaders/shaders.cpp"

#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/noise.hpp>

glm::vec3 shake(float time, float intensity, float speed) {
    // Adjust the parameters as needed for the desired effect
    float x = time * speed; // Use time as the input coordinate for animation
    float y = 0.0f; // You can modify the y-coordinate if desired
    float z = 0.0f; // You can modify the z-coordinate if desired

    // Generate Perlin noise values at the specified coordinates
    float noiseX = glm::perlin(glm::vec3(x, y, z));
    float noiseY = glm::perlin(glm::vec3(x + 100.0f, y, z)); // Offset the x-coordinate for different noise
    // Calculate the shake offset using the noise values
    float offsetX = noiseX * intensity;
    float offsetY = noiseY * intensity;

    return glm::vec3(offsetX, offsetY, 0.0f);
}

int main()
{
    float jumpHeight = 0.5f; // Maximum height of the jump
    float jumpDuration = 2.f; // Duration of the jump in seconds
    float time = 0.0f;
    float rotationSpeed = 3.0f; // Adjust the speed of rotation
    float angleY = 0.0f; // Initial rotation angle
    float radius = 2.0f; // Adjust the radius of the circular path
    float speed = 20.0f;
    float intensity = 0.2f;
    float ticksInterval = 1.0f / 60.0f;  // Time interval for updating the translation (e.g., 0.1 seconds)
     // Time counter for tracking the placethis.getPosition   // create the window
    sf::Window window(sf::VideoMode(1280, 720), "test?", sf::Style::Default, sf::ContextSettings(32));
    window.setFramerateLimit(240); // Set the framerate to 60 FPS
    // activate the window
    window.setActive(true);
    sf::Clock clock;
    sf::Time deltaTime;
    // load resources, initialize the OpenGL states, ...

    GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK)
    {
        // GLEW initialization failed
        return -1;
    }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // An array of 3 vectors which represents 3 vertices
    const GLfloat t1[] = {
        -4.0f, 3.0f, 0.0f,
        -2.0f, 3.0f, 0.0f,
        -1.0f, -3.0f, 0.0f,
    };     

    const GLfloat t2[] = {
        -2.0f, 3.0f, 0.0f,
        -1.0f, -3.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
    };

    const GLfloat t3[] = {
        2.0f, 3.0f, 0.0f,
        4.0f, 3.0f, 0.0f,
        1.0f, -3.0f, 0.0f, 
    };
    const GLfloat t4[] = {
        2.0f, 3.0f, 0.0f,
        1.0f, -3.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
    };
    const GLfloat t5[] = {
        -2.0f, -1.0f, 0.0f,
        2.0f, -1.0f, 0.0f,
        0.0f, 3.0f, 0.0f
    };

    const GLfloat s1_1[] = {
        -4.0f, -1.0f, 0.0f,
        -4.0f, 1.0f, 0.0f,
        -8.0f, -1.0f, 0.0f,
    };
    const GLfloat s1_2[] = {
        -4.0f, 1.0f, 0.0f,
        -8.0f, -1.0f, 0.0f,
        -8.0f, 1.0f, 0.0f
    };

    const GLfloat s2_1[] = {
        4.0f, -1.0f, 0.0f,
        4.0f, 1.0f, 0.0f,
        8.0f, -1.0f, 0.0f,
    };
    const GLfloat s2_2[] = {
        4.0f, 1.0f, 0.0f,
        8.0f, -1.0f, 0.0f,
        8.0f, 1.0f, 0.0f
    };

    Shader shader(vertex_shader, fragment_shader);

    TriangleManager triangleManager(window, shader);

    triangle *Triangle = triangleManager.addTriangle(t1);
    triangle *triangle2 = triangleManager.addTriangle(t2);
    triangle *triangle3 = triangleManager.addTriangle(t3);
    triangle *triangle4 = triangleManager.addTriangle(t4);
    triangle *triangle5 = triangleManager.addTriangle(t5);

    triangle *s11 = triangleManager.addTriangle(s1_1);
    triangle *s12 = triangleManager.addTriangle(s1_2);
    triangle *s21 = triangleManager.addTriangle(s2_1);
    triangle *s22 = triangleManager.addTriangle(s2_2);


    glm::mat4 Projection = glm::perspective(glm::radians(90.0f), (float) 1280.f / (float) 720.f, 0.1f, 100.0f);
  
    // Camera matrix
    glm::mat4 effectView = glm::mat4(1.0f);
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, 10), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    
    // run the main loop
    bool running = true;
    while (running)
    {
        deltaTime = clock.restart();
        time += deltaTime.asSeconds();
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        // Calculate the vertical displacement based on time and duration
        float t = std::fmod(time, jumpDuration);


        float displacement = 2.f * sin(3.1415f * time);

        
        // tick loop
        
        glm::mat4 transMatrix = glm::mat4(1.0f);

        transMatrix[3][1] = displacement;
        
        float midiff1 = s11->calculateMiddlePoint().y - s12->calculateMiddlePoint().y;
        float midiff2 = s21->calculateMiddlePoint().y - s22->calculateMiddlePoint().y;

        s11->place(glm::vec3(s11->calculateMiddlePoint().x, displacement + midiff1, 0.0f));
        s12->place(glm::vec3(s12->calculateMiddlePoint().x, displacement, 0.0f));
        s21->place(glm::vec3(s21->calculateMiddlePoint().x, displacement + midiff2, 0.0f));
        s22->place(glm::vec3(s22->calculateMiddlePoint().x, displacement, 0.f));


        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // angleY = rotationSpeed * time; // Adjust deltaTime based on your frame time

        // // Calculate the camera position
        // glm::vec3 axis(0.0f, 1.0f, 0.0f);

        // glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), time, axis);

        shader.SetInt("isPressed", 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            shader.SetInt("isPressed", 1);
            glm::vec3 translation = shake(time, intensity, speed);
            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);    
        
            effectView = translationMatrix * effectView;    
        } else {
            effectView = glm::mat4(1.0f);
        };

        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 mvp = Projection * View * effectView; // Remember, matrix multiplication is the other way around
        shader.SetFloat("time", time);
        triangleManager.render(mvp);

        window.display();
    }

    // release resources...

    return 0;   
}