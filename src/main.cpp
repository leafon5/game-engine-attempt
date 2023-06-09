#include "pch.h"
#include "classes/triangle.hpp"
#include <SFML/Window.hpp>

int main()
{
     // create the window
    sf::Window window(sf::VideoMode(1280, 720), "test?", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

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
    // run the main loop
    bool running = true;
    while (running)
    {
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

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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