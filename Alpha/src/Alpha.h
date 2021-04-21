#pragma once

// For use by alpha applications

#include "Alpha/Application.h"
#include "Alpha/Log.h"
#include "Alpha/Layer.h"

// Input
#include "Alpha/Input.h"
#include "Alpha/KeyCodes.h"
#include "Alpha/MouseButtoncodes.h"

// Renderer
#include "Alpha/Renderer/Shader.h"
#include "Alpha/Renderer/Renderer.h"
#include "Alpha/Renderer/RenderCommand.h"
#include "Alpha/Renderer/OrtographicCamera.h"
#include "Alpha/Renderer/PerspectiveCamera.h"
#include "Alpha/Renderer/Texture.h"
#include "Alpha/Renderer/DirectionalLight.h"
#include "Alpha/Renderer/Skybox.h"
#include "Alpha/Renderer/DebugLine.h"


// Macro
#include "Alpha/Platform/OpenGL/OpenGLMacros.h"

// GameObject
#include "Alpha/Objects/GameObject.h"
#include "Alpha/Objects/MeshRenderer.h"
#include "Alpha/Objects/Transform.h"
#include "Alpha/Objects/PhysicsBody.h"

// Time
#include "Alpha/Time.h"

// ImGui Layer
#include "Alpha/ImGui/ImGuiLayer.h"

/// ---Entry point--------------
#include "Alpha/EntryPoint.h" 
/// ----------------------------