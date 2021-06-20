/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** Texture
*/

#include "Texture.hpp"
#include <rlgl.h>
#include <iostream>

namespace RayLib
{
    Texture::Texture(const std::string& filename) : _texture(LoadTexture(filename.c_str())), _fileName(filename)
    {

    }

    Texture::Texture(Image image, bool isCubemap)
    {
        if (!isCubemap)
            _texture = LoadTextureFromImage(image.GetImage());
        else
            _texture = LoadTextureCubemap(image.GetImage(), CUBEMAP_LAYOUT_AUTO_DETECT);
        _fileName = "";
    }

    Texture::Texture(::Texture texture) : _texture(texture), _fileName("")
    {
    }

    Texture::Texture(RayLib::Shader& shader, RayLib::Texture& texture, int size, float format)
    {
        rlDisableBackfaceCulling();     // Disable backface culling to render inside the cube

        // STEP 1: Setup framebuffer
        //------------------------------------------------------------------------------------------
        unsigned int rbo = rlLoadTextureDepth(size, size, true);
        _texture.id = rlLoadTextureCubemap(0, size, format);

        unsigned int fbo = rlLoadFramebuffer(size, size);
        rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
        rlFramebufferAttach(fbo, _texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

        // Check if framebuffer is complete with attachments (valid)
        if (rlFramebufferComplete(fbo)) TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", fbo);
        //------------------------------------------------------------------------------------------

        // STEP 2: Draw to framebuffer
        //------------------------------------------------------------------------------------------
        // NOTE: Shader is used to convert HDR equirectangular environment map to cubemap equivalent (6 faces)
        rlEnableShader(shader.GetShader().id);

        // Define projection matrix and send it to shader
        Matrix matFboProjection = MatrixPerspective(90.0*DEG2RAD, 1.0, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
        rlSetUniformMatrix(shader.GetShader().locs[SHADER_LOC_MATRIX_PROJECTION], matFboProjection);

        // Define view matrix for every side of the cubemap
        Matrix fboViews[6] = {
            MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
            MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ -1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
            MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f,  1.0f }),
            MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f, -1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f, -1.0f }),
            MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  0.0f,  1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
            MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  0.0f, -1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f })
        };

        rlViewport(0, 0, size, size);   // Set viewport to current fbo dimensions

        // Activate and enable texture for drawing to cubemap faces
        rlActiveTextureSlot(0);
        rlEnableTexture(texture.GetTexture().id);

        for (int i = 0; i < 6; i++)
        {
            // Set the view matrix for the current cube face
            rlSetUniformMatrix(shader.GetShader().locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);

            // Select the current cubemap face attachment for the fbo
            // WARNING: This function by default enables->attach->disables fbo!!!
            rlFramebufferAttach(fbo, _texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
            rlEnableFramebuffer(fbo);

            // Load and draw a cube, it uses the current enabled texture
            rlClearScreenBuffers();
            rlLoadDrawCube();

            // ALTERNATIVE: Try to use internal batch system to draw the cube instead of rlLoadDrawCube
            // for some reason this method does not work, maybe due to cube triangles definition? normals pointing out?
            // TODO: Investigate this issue...
            //rlSetTexture(panorama.id); // WARNING: It must be called after enabling current framebuffer if using internal batch system!
            //rlClearScreenBuffers();
            //DrawCubeV(Vector3Zero(), Vector3One(), WHITE);
            //rlDrawRenderBatchActive();
        }
        //------------------------------------------------------------------------------------------

        // STEP 3: Unload framebuffer and reset state
        //------------------------------------------------------------------------------------------
        rlDisableShader();          // Unbind shader
        rlDisableTexture();         // Unbind texture
        rlDisableFramebuffer();     // Unbind framebuffer
        rlUnloadFramebuffer(fbo);   // Unload framebuffer (and automatically attached depth texture/renderbuffer)

        // Reset viewport dimensions to default
        rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
        rlEnableBackfaceCulling();
        //------------------------------------------------------------------------------------------

        _texture.width = size;
        _texture.height = size;
        _texture.mipmaps = 1;
        _texture.format = format;

        _fileName = "";
    }

    void Texture::DrawTexture(Vector2<float> position, Color tint)
    {
        ::DrawTextureV(_texture, position.getVector2(), tint.getColor());
    }

    void Texture::DrawTextureEx(Vector2<float> position, float rotation, float scale, Color tint)
    {
        ::DrawTextureEx(_texture, position.getVector2(), rotation, scale, tint.getColor());
    }

    void Texture::DrawTextureRec(RayLib::Rectangle source, RayLib::Vector2<float> position, RayLib::Color col)
    {
        ::DrawTextureRec(_texture, source.GetRectangle(), position.getVector2(), col.getColor());
    }

    void Texture::DrawBillboard(RayLib::Camera3D camera, RayLib::Vector3 center, float size, Color tint)
    {
        ::DrawBillboard(camera.GetCamera(), _texture, center.getVector3(), size, tint.getColor());
    }

    void Texture::DrawTextureNPatch(Vector2<float> position, float rotation, Vector2<float> scale, Color tint)
    {
        Rectangle source(0.0f, 0.0f, static_cast<float>(_texture.width), static_cast<float>(_texture.height));
        NPatchInfo info = {source.GetRectangle(), 0, 0, 0, 0, NPATCH_NINE_PATCH};
        Rectangle dest(position.x, position.y, _texture.width * scale.x, _texture.height * scale.y);
        Vector2 vect(0, 0);

        ::DrawTextureNPatch(_texture, info, dest.GetRectangle(), vect.getVector2(), rotation, tint);
    }

    ::Texture2D Texture::GetTexture()
    {
        return (_texture);
    }

    Texture::~Texture()
    {
        UnloadTexture(_texture);
    }

    const std::string& Texture::GetFileName() const
    {
        return (_fileName);
    }
}