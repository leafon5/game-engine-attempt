#include "pch.h"

#include "classes/triangle.hpp"
#include "classes/shader.hpp"


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
    // float rotationSpeed = 3.0f; // Adjust the speed of rotation
    // float angleY = 0.0f; // Initial rotation angle
    // float radius = 2.0f; // Adjust the radius of the circular path
    float speed = 20.0f;
    float intensity = 0.2f;

     // create the window
    sf::Window window(sf::VideoMode(1280, 720), "test?", sf::Style::Default, sf::ContextSettings(32));
    window.setFramerateLimit(144); // Set the framerate to 60 FPS
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
        -400.0f, 300.0f, 0.0f,
        -200.0f, 300.0f, 0.0f,
        -100.0f, -300.0f, 0.0f,
    };     

    const GLfloat t2[] = {
        -200.0f, 300.0f, 0.0f,
        -100.0f, -300.0f, 0.0f,
        0.0f, -100.0f, 0.0f,
    };

    const GLfloat t3[] = {
        200.0f, 300.0f, 0.0f,
        400.0f, 300.0f, 0.0f,
        100.0f, -300.0f, 0.0f, 
    };
    const GLfloat t4[] = {
        200.0f, 300.0f, 0.0f,
        100.0f, -300.0f, 0.0f,
        0.0f, -100.0f, 0.0f,
    };
    const GLfloat t5[] = {
        -200.0f, -100.0f, 0.0f,
        200.0f, -100.0f, 0.0f,
        0.0f, 300.0f, 0.0f
    };

    const GLfloat s1_1[] = {
        -400.0f, -100.0f, 0.0f,
        -400.0f, 100.0f, 0.0f,
        -800.0f, -100.0f, 0.0f,
    };
    const GLfloat s1_2[] = {
        -400.0f, 100.0f, 0.0f,
        -800.0f, -100.0f, 0.0f,
        -800.0f, 100.0f, 0.0f
    };

    const GLfloat s2_1[] = {
        400.0f, -100.0f, 0.0f,
        400.0f, 100.0f, 0.0f,
        800.0f, -100.0f, 0.0f,
    };
    const GLfloat s2_2[] = {
        400.0f, 100.0f, 0.0f,
        800.0f, -100.0f, 0.0f,
        800.0f, 100.0f, 0.0f
    };

    triangle Triangle(t1, window);
    triangle Triangle2(t2, window);
    triangle Triangle3(t3, window);
    triangle Triangle4(t4, window);
    triangle Triangle5(t5, window);

    triangle s11(s1_1, window);
    triangle s12(s1_2, window);
    triangle s21(s2_1, window);
    triangle s22(s2_2, window);

    Triangle.buffer();
    Triangle2.buffer();
    Triangle3.buffer();
    Triangle4.buffer();
    Triangle5.buffer();

    s11.buffer();
    s12.buffer();
    s21.buffer();
    s22.buffer();

    Shader shader(vertex_shader, fragment_shader);

    glm::mat4 Projection = glm::perspective(glm::radians(90.0f), (float) 1.f / (float) 1.f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
  
    // Camera matrix
    glm::mat4 Model = glm::mat4(1.0f);

    // run the main loop
    bool running = true;
    while (running)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        // handle events
        deltaTime = clock.restart();

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
        float displacement = -4.0f * jumpHeight / (jumpDuration * jumpDuration) * (t - jumpDuration / 2.0f) * (t - jumpDuration / 2.0f) + jumpHeight;
        float spacing = s11.calculateMiddlePoint().y - s12.calculateMiddlePoint().y;
        // std::cout << displacement;
        s11.place({s11.calculateMiddlePoint().x, displacement + spacing, 0.0f});
        s12.place({s12.calculateMiddlePoint().x, displacement, 0.0f});
        s21.place({s21.calculateMiddlePoint().x, displacement + spacing, 0.0f});
        s22.place({s22.calculateMiddlePoint().x, displacement, 0.0f});

        time += deltaTime.asSeconds();
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // angleY = rotationSpeed * time; // Adjust deltaTime based on your frame time

        // // Calculate the camera position
        // float camX = radius * sin(angleY);
        // float camZ = radius * cos(angleY);
        // glm::vec3 cameraPosition(camX, 0.0f, camZ);
        glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, 1), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );
        shader.SetInt("isPressed", 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            shader.SetInt("isPressed", 1);
            glm::vec3 translation = shake(time, intensity, speed);
            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);    
        
            View = translationMatrix * View;    
        }
        // Model matrix : an identity matrix (model will be at the origin)
        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
        shader.SetFloat("time", time);
        shader.Set4fv("MVP", mvp);

        shader.Use();
        // draw...
        Triangle5.draw();
        Triangle4.draw();
        Triangle3.draw();
        Triangle2.draw();
        Triangle.draw();

        s11.draw();
        s12.draw();
        s21.draw();
        s22.draw();
        // 1st attribute buffer : vertices

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;   
}