//
// Created by ljuba on 8/15/26.
//

#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

/**
* @brief Parameters used to define a Framebuffer.
*/
struct FramebufferParams {
    unsigned int framebuffer = -1;
    unsigned int texture_color_buffer = -1;
    unsigned int rbo = -1;
    unsigned int quad_vao = -1;
    unsigned int quad_vbo = -1;
    bool initialized = false;
};

//Singleton class
class PostProcessing {
public:
    PostProcessing(const PostProcessing &) = delete;
    PostProcessing &operator=(const PostProcessing &) = delete;

    static PostProcessing &get_instance() {
        static PostProcessing instance;
        return instance;
    }

    /**
    * @brief Initialize framebuffer.
    */
    void create_framebuffer(int scr_width, int scr_height);

    /**
     * @brief Destroy framebuffer.
     */
    void destroy_framebuffer();

    /**
     * @brief Bind framebuffer.
     */
    void bind_framebuffer();

    /**
     * @brief Unbind framebuffer.
     */
    void unbind_framebuffer();

    /**
     * @brief Draw framebuffer.
     */
    void draw_framebuffer();

private:
    PostProcessing();
    FramebufferParams m_framebuffer_params;
};


#endif//POSTPROCESSING_H
