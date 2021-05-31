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
#include "Texture.h"
                      
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


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
           100.0f, 100.0f, 0.0f, 0.0f,
           200.0f, 100.0f, 1.0f, 0.0f,
           200.0f, 200.0f, 1.0f, 1.0f, 
           100.0f, 200.0f, 0.0f, 1.0f
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        GLCall(VertexBuffer vb(pos, 4 * 4 * sizeof(float)));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);


        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, -100, 0));
        


		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
        
        Shader shader("res/shaders/Sh.shader");
        
        shader.Bind();
        shader.SetUniform4f( "u_Color",r, g, b, 1.0f );  
        Texture texture("res/textures/mario.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        /* unbind everything before runtime*/
        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        
        Renderer renderer;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

        ImGui::StyleColorsDark();

		ImGui_ImplGlfwGL3_Init(window, true);

        glm::vec3 translation(0, 0, 0);

        float increment = 0.05f;

        /* Runtime Loop */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

			glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

			glm::mat4 mvp = proj * view * model; //model view projection
            

            shader.Bind();
            shader.SetUniform4f("u_Color", r, g, b, 1.0f);
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

			{  
				ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 1000.0f); 
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
