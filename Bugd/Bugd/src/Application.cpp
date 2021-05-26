#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GL_ERROR.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Bugd", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW Error" << std::endl;
    
    std::cout << glGetString(GL_VERSION) << std::endl; //Print openGL version to console
    {
        float pos[] =
        {
           -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
           -0.5f,  0.5f,
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        GLCall(VertexBuffer vb(pos, 4 * 2 * sizeof(float)));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

        IndexBuffer ib(indices, 6);

		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
        
        Shader shader("res/shaders/Sh.shader");
        
        shader.Bind();
        shader.SetUniform4f( "u_Color",r, g, b, 1.0f );  

        /* unbind vertex buffer*/
        
        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        
        Renderer renderer;

        float increment = 0.05f;

        /* Runtime Loop */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            shader.Bind();
            shader.SetUniform4f("u_Color", r, g, b, 1.0f);

            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
