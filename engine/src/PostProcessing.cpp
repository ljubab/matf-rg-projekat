//
// Created by ljuba on 8/15/26.
//
// clang-format off
#include <glad/glad.h>
// clang-format on
#include "spdlog/spdlog.h"

#include <engine/graphics/OpenGL.hpp>
#include <engine/graphics/PostProcessing.hpp>
#include <engine/util/Errors.hpp>

void PostProcessing::create_framebuffer(int scr_width, int scr_height) {
    if (!m_framebuffer_params.framebuffer) {
        destroy_framebuffer();
    }

    CHECKED_GL_CALL(glGenFramebuffers, 1, &m_framebuffer_params.framebuffer);
    CHECKED_GL_CALL(glBindFramebuffer, GL_FRAMEBUFFER, m_framebuffer_params.framebuffer);

    CHECKED_GL_CALL(glGenTextures, 1, &m_framebuffer_params.texture_color_buffer);
    CHECKED_GL_CALL(glBindTexture, GL_TEXTURE_2D, m_framebuffer_params.texture_color_buffer);
    CHECKED_GL_CALL(glTexImage2D, GL_TEXTURE_2D, 0, GL_RGB, scr_width, scr_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    CHECKED_GL_CALL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    CHECKED_GL_CALL(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    CHECKED_GL_CALL(glFramebufferTexture2D, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_framebuffer_params.texture_color_buffer, 0);

    CHECKED_GL_CALL(glGenRenderbuffers, 1, &m_framebuffer_params.rbo);
    CHECKED_GL_CALL(glBindRenderbuffer, GL_RENDERBUFFER, m_framebuffer_params.rbo);
    CHECKED_GL_CALL(glRenderbufferStorage, GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scr_width, scr_height);
    CHECKED_GL_CALL(glFramebufferRenderbuffer, GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_framebuffer_params.rbo);

    if (CHECKED_GL_CALL(glCheckFramebufferStatus, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw engine::util::Error("Framebuffer is not complete!");
    }

    CHECKED_GL_CALL(glBindFramebuffer, GL_FRAMEBUFFER, 0);

    float quadVertices[] = {
            // positions   // texCoords
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f};

    CHECKED_GL_CALL(glGenVertexArrays, 1, &m_framebuffer_params.quad_vao);
    CHECKED_GL_CALL(glGenBuffers, 1, &m_framebuffer_params.quad_vbo);
    CHECKED_GL_CALL(glBindVertexArray, m_framebuffer_params.quad_vao);
    CHECKED_GL_CALL(glBindBuffer, GL_ARRAY_BUFFER, m_framebuffer_params.quad_vbo);
    CHECKED_GL_CALL(glBufferData, GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    CHECKED_GL_CALL(glEnableVertexAttribArray, 0);
    CHECKED_GL_CALL(glVertexAttribPointer, 0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    CHECKED_GL_CALL(glEnableVertexAttribArray, 1);
    CHECKED_GL_CALL(glVertexAttribPointer, 1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));
}

void PostProcessing::destroy_framebuffer() {
    CHECKED_GL_CALL(glDeleteRenderbuffers, 1, &m_framebuffer_params.rbo);
    CHECKED_GL_CALL(glDeleteTextures, 1, &m_framebuffer_params.texture_color_buffer);
    CHECKED_GL_CALL(glDeleteFramebuffers, 1, &m_framebuffer_params.framebuffer);

    CHECKED_GL_CALL(glDeleteRenderbuffers, 1, &m_framebuffer_params.rbo);
    CHECKED_GL_CALL(glDeleteTextures, 1, &m_framebuffer_params.texture_color_buffer);
    CHECKED_GL_CALL(glDeleteFramebuffers, 1, &m_framebuffer_params.framebuffer);
    CHECKED_GL_CALL(glDeleteVertexArrays, 1, &m_framebuffer_params.quad_vao);
    CHECKED_GL_CALL(glDeleteBuffers, 1, &m_framebuffer_params.quad_vbo);
}

void PostProcessing::bind_framebuffer() {
    CHECKED_GL_CALL(glBindFramebuffer, GL_FRAMEBUFFER, m_framebuffer_params.framebuffer);
    CHECKED_GL_CALL(glClearColor, 0.1f, 0.1f, 0.1f, 1.0f);
    CHECKED_GL_CALL(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CHECKED_GL_CALL(glEnable, GL_DEPTH_TEST);
}

void PostProcessing::unbind_framebuffer() {
    CHECKED_GL_CALL(glBindFramebuffer, GL_FRAMEBUFFER, 0);
    CHECKED_GL_CALL(glClearColor, 1.0f, 1.0f, 1.0f, 1.0f);
    CHECKED_GL_CALL(glClear, GL_COLOR_BUFFER_BIT);
}

void PostProcessing::draw_framebuffer() {
    CHECKED_GL_CALL(glDisable, GL_DEPTH_TEST);
    CHECKED_GL_CALL(glActiveTexture, GL_TEXTURE0);
    CHECKED_GL_CALL(glBindTexture, GL_TEXTURE_2D, m_framebuffer_params.texture_color_buffer);
    CHECKED_GL_CALL(glBindVertexArray, m_framebuffer_params.quad_vao);
    CHECKED_GL_CALL(glDrawArrays, GL_TRIANGLES, 0, 6);
    CHECKED_GL_CALL(glBindVertexArray, 0);
    CHECKED_GL_CALL(glBindTexture, GL_TEXTURE_2D, 0);
    CHECKED_GL_CALL(glEnable, GL_DEPTH_TEST);
}