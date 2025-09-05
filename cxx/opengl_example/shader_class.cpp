#include "shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLenum err = glewInit();

    Shader shaderProgram("./shaders/3.3.shader.vs", "./shaders/3.3.shader.fs");

    // render triangle
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// left
            0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right
            0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f // top
    };

    // VAO 数据的清单，用于描述数据
    // VBO 真实数据对象
    GLuint VBO, VAO;
    // 先创建VAO和VBO的对象，获取两个的ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // gl绑定VAO，代表之后的顶点属性配置、VBO 绑定等状态会记录到这个 VAO 里。
    glBindVertexArray(VAO);

    // 绑定 VBO 到 GL_ARRAY_BUFFER 目标。
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 把本地内存的顶点数据 vertices 上传到 GPU 显存里，使用方式为 GL_STATIC_DRAW（表示数据不会频繁改动，主要用于绘制）
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 告诉 OpenGL 如何解释当前绑定的 VBO 里的数据，并和 顶点着色器的 layout(location = 0) 变量对应。
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    // 启用这个顶点属性（否则不会传输到着色器）。
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 解绑 VBO 和 VAO，防止误操作。
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        shaderProgram.use();

        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}