/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** EntityFactory
*/

#include "UISystem.hpp"
#include "Transform.hpp"
#include "Button.hpp"
#include "ButtonCallbacks.hpp"
#include "Renderer.hpp"
#include "Destructible.hpp"
#include "Movement.hpp"
#include "SquareCollider.hpp"
#include "EntityFactory.hpp"
#include "Scenes.hpp"
#include "Animator.hpp"
#include "Texture.hpp"
#include "Image.hpp"
#include "TextUI.hpp"
#include "Font.hpp"
#include "PlayerInputs.hpp"
#include "SpeedBoost.hpp"
#include "CoolDownBoost.hpp"
#include "Explosion.hpp"
#include "PhysicsBody.hpp"
#include "Box.hpp"
#include "AIAlgo.hpp"
#include "TextBox.hpp"
#include "TextBoxCallback.hpp"
#include "HUDText.hpp"
#include "Drawable3D.hpp"
#include "AssetCache.hpp"
#include "TerrainShader.hpp"

EntityFactory::EntityFactory(ECS::Coordinator& coordinator, RayLib::Camera3D& camera)
    : _coordinator(coordinator), _camera(camera)
{
    _pickupFunctions.push_back(std::bind(&EntityFactory::createSpeedPickUp, this));
    _pickupFunctions.push_back(std::bind(&EntityFactory::createRangePickUp, this));
    _pickupFunctions.push_back(std::bind(&EntityFactory::createCooldownPickUp, this));
}

ECS::Entity& EntityFactory::createButton(const std::string& path)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    entity.SetTag("button");
    entity.AddComponent<Component::IUIObject, Component::Button>(path);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::ButtonCallbacks>(entity);

    return (entity);
}

ECS::Entity& EntityFactory::createTextBox(int maxLength, const std::string& fontPath, float size, float spacing, RayLib::Color color)
{
    ECS::Entity& entity = _coordinator.CreateEntity();

    entity.SetTag("TextField");
    entity.AddComponent<Component::IUIObject, Component::TextBox>(maxLength, fontPath, size, spacing, color, false, true);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    entity.AddComponent<Component::IBehaviour, Component::TextBoxCallback>(entity);
    return (entity);
}

ECS::Entity& EntityFactory::createText(const std::string& content, const std::string& fontPath, float size, float spacing)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    entity.SetTag(content);
    entity.AddComponent<Component::IUIObject, Component::TextUI>(content, fontPath, size, spacing);
    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 0.0f, 0.0f), 0.0f, RayLib::Vector3(1.0f, 1.0f, 1.0f));
    return (entity);
}

ECS::Entity& EntityFactory::createWall(RayLib::Vector3 pos)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    RayLib::Mesh cubeMesh(RayLib::Vector3(1.0f, 1.0f, 1.0f));

    entity.SetTag("Wall");
    entity.AddComponent<Component::Transform>(pos, RayLib::Vector3(90, 0, 0), RayLib::Vector3(10.0f, 10.0f, 10.0f));

    entity.AddComponent<Component::Drawable3D>(cubeMesh);
    entity.GetComponent<Component::Drawable3D>().SetTexture("../assets/Wall/Wall_texture.png");
    Component::Transform& transform = entity.GetComponent<Component::Transform>();

    //entity.AddComponent<Component::Renderer>("Wall");

    entity.AddComponent<Component::Collider, Component::SquareCollider>(entity,
                                                                        std::vector<std::string>({"Player"}),
                                                                        RayLib::Vector2<float>(pos),
                                                                        RayLib::Vector2<float>(transform.scale));

    return (entity);
}

ECS::Entity& EntityFactory::createBox(RayLib::Vector3 position, const int, const bool)
{
    ECS::Entity &entity = _coordinator.CreateEntity();

    RayLib::Mesh cubeMesh(RayLib::Vector3(1.0f, 1.0f, 1.0f));

    entity.AddComponent<Component::Drawable3D>(cubeMesh);
    entity.GetComponent<Component::Drawable3D>().SetTexture("../assets/Box/Box_texture.png");
    entity.SetTag("Box");

    entity.AddComponent<Component::Transform>(position, RayLib::Vector3(), RayLib::Vector3(10.0f, 10.0f, 10.0f));
    Component::Transform& transform = entity.GetComponent<Component::Transform>();
    //entity.AddComponent<Component::Renderer>("Box");
    entity.AddComponent<Component::Collider, Component::SquareCollider>(entity,
                                                                        std::vector<std::string>({"Player"}),
                                                                        RayLib::Vector2<float>(position),
                                                                        RayLib::Vector2<float>(transform.scale));
    //entity.AddComponent<Component::Destructible>(entity, 1);
    entity.AddComponent<Component::Box>(entity, 1, 0.1f);

    //if (draggable)
    //    entity.AddComponent<Component::IBehaviour, Component::Draggable>(entity, _camera);

    return (entity);
}

ECS::Entity& EntityFactory::createPlayer(Engine::playerkeys& keys, int nbrOfThePlayer)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    if (nbrOfThePlayer <= 9)
        entity.SetTag("PlayerEntity_00" + std::to_string(nbrOfThePlayer));
    else if (nbrOfThePlayer <= 99)
        entity.SetTag("PlayerEntity_0" + std::to_string(nbrOfThePlayer));
    else if (nbrOfThePlayer <= 999)
        entity.SetTag("PlayerEntity_" + std::to_string(nbrOfThePlayer));
    entity.AddComponent<Component::Transform>(RayLib::Vector3(), RayLib::Vector3(), RayLib::Vector3(6, 6, 6));
    entity.AddComponent<Component::PhysicsBody>();

    Component::Transform& transform = entity.GetComponent<Component::Transform>();

    entity.AddComponent<Component::Collider, Component::SquareCollider>(entity,
                                                                        std::vector<std::string>({"Wall", "Box", "Bomb"}),
                                                                        RayLib::Vector2<float>(transform.position),
                                                                        RayLib::Vector2<float>(transform.scale));

    entity.AddComponent<Component::IBehaviour, Component::PlayerInputs>(entity, keys.movementInput, keys.actionKey);

    entity.AddComponent<Component::Drawable3D>("../assets/Player/Player_model.glb", "../assets/Player/Player_texture.png");

    entity.AddComponent<Component::Animator>(entity, "../assets/Player/Player_anim_Idle.glb", "Idle");
    entity.GetComponent<Component::Animator>().AddState("../assets/Player/Player_anim_Run.glb", "Run");

    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(90.0f, 0.0f, 0.0f);
    entity.AddComponent<Component::Destructible>(entity, 1);
    return (entity);
}

ECS::Entity& EntityFactory::createAI()
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("AI");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(), RayLib::Vector3(), RayLib::Vector3(6, 6, 6));
    entity.AddComponent<Component::PhysicsBody>();

    entity.AddComponent<Component::Drawable3D>("../assets/Player/Player_model.glb", "../assets/Player/Player_texture.png");
    entity.AddComponent<Component::Animator>(entity, "../assets/Player/Player_anim_Idle.glb", "Idle");
    entity.GetComponent<Component::Animator>().AddState("../assets/Player/Player_anim_Run.glb", "Run");

    Component::Transform& transform = entity.GetComponent<Component::Transform>();
    entity.AddComponent<Component::Collider, Component::SquareCollider>(entity,
                                                                        std::vector<std::string>({"Wall", "Box", "Bomb"}),
                                                                        RayLib::Vector2<float>(transform.position),
                                                                        RayLib::Vector2<float>(transform.scale));

    entity.AddComponent<Component::Destructible>(entity, 1);
    //AIMapsGenerator& mapsgen = _coordinator.GetSystem<AIMapsGenerator>();
    entity.GetComponent<Component::Transform>().rotation = RayLib::Vector3(90.0f, 0.0f, 0.0f);

    entity.AddComponent<Component::IBehaviour, Component::AIAlgo>(entity, 0.75f, 5.0f);
    // add destructible
    return (entity);
}

ECS::Entity& EntityFactory::createHUDText(Component::AController &controller, int nbrOfThePlayer)
{
    ECS::Entity &entity = createBaseHUD(controller, nbrOfThePlayer);

    entity.SetTag(entity.GetTag() + "_text");
    entity.AddComponent<Component::Renderer>();
    entity.AddComponent<Component::IUIObject, Component::TextUI>("Player " + std::to_string(nbrOfThePlayer), "../assets/pixelplay.png", 50.0f, 4.0f);
    entity.GetComponent<Component::Transform>().position += RayLib::Vector3(0, 0, 0);
    return (entity);
}

ECS::Entity& EntityFactory::createBaseHUD(Component::AController &controller, int nbrOfThePlayer)
{
    ECS::Entity &entity = _coordinator.CreateEntity();
    if (nbrOfThePlayer <= 9)
        entity.SetTag("HUD_00" + std::to_string(nbrOfThePlayer));
    else if (nbrOfThePlayer <= 99)
        entity.SetTag("HUD_0" + std::to_string(nbrOfThePlayer));
    else if (nbrOfThePlayer <= 999)
        entity.SetTag("HUD_" + std::to_string(nbrOfThePlayer));

    entity.AddComponent<Component::HUDText>(controller, nbrOfThePlayer);
    RayLib::Vector3 &offset = entity.GetComponent<Component::HUDText>().getOffset();
    entity.AddComponent<Component::Transform>(offset, RayLib::Vector3(0, 0, 0), RayLib::Vector3(6, 6, 6));
    return (entity);
}

ECS::Entity& EntityFactory::createRangePickUp(void)
{
    RayLib::Mesh cubeMesh(RayLib::Vector3(1.0f, 1.0f, 1.0f));

    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("RangePickUp");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::Drawable3D>(cubeMesh);
    entity.GetComponent<Component::Drawable3D>().SetTexture("../assets/PickUps/RangePickUp_texture.png");

    entity.AddComponent<Component::IBehaviour, Component::RangeBoost>(entity, 5.0f);
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(5.0f, 5.0f, 5.0f);
    return (entity);
}

ECS::Entity& EntityFactory::createCooldownPickUp(void)
{
    RayLib::Mesh cubeMesh(RayLib::Vector3(1.0f, 1.0f, 1.0f));

    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("CoolDownPickUp");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::Drawable3D>(cubeMesh);
    entity.GetComponent<Component::Drawable3D>().SetTexture("../assets/PickUps/CoolDownPickUp_texture.png");
    entity.AddComponent<Component::IBehaviour, Component::CoolDownBoost>(entity, 5.0f);
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(5.0f, 5.0f, 5.0f);
    return (entity);
}

ECS::Entity& EntityFactory::createSpeedPickUp(void)
{
    RayLib::Mesh cubeMesh(RayLib::Vector3(1.0f, 1.0f, 1.0f));

    ECS::Entity &entity = _coordinator.CreateEntity();
    entity.SetTag("SpeedPickUp");
    entity.AddComponent<Component::Transform>();
    entity.AddComponent<Component::Drawable3D>(cubeMesh);
    entity.GetComponent<Component::Drawable3D>().SetTexture("../assets/PickUps/SpeedPickUp_texture.png");
    entity.AddComponent<Component::IBehaviour, Component::SpeedBoost>(entity, 5.0f);
    entity.GetComponent<Component::Transform>().scale = RayLib::Vector3(5.0f, 5.0f, 5.0f);

    return (entity);
}

ECS::Entity& EntityFactory::createPickUp(void)
{
    int index = rand() % (_pickupFunctions.size());
    ECS::Entity &entity = _pickupFunctions[index]();
    return (entity);
}

ECS::Entity& EntityFactory::createBomb(float radius, Component::Explosion::ExplosionType type)
{
    ECS::Entity& entity = _coordinator.CreateEntity();

    entity.AddComponent<Component::Drawable3D>("../assets/bomb/Bomb_model.iqm", "../assets/bomb/Bomb_texture.png");

    entity.SetTag("Bomb");
    entity.AddComponent<Component::Transform>(RayLib::Vector3(), RayLib::Vector3(), RayLib::Vector3(BOX_SIZE, BOX_SIZE, BOX_SIZE));
    //! si on spawn une bombe sur le joueur, on est bloqués
    //entity.AddComponent<Collider, BoxCollider>(entity, _coordinator);
    entity.AddComponent<Component::IBehaviour, Component::Explosion>(entity, entity, radius, type);
    return (entity);
}

ECS::Entity& EntityFactory::createCamera(void)
{
    ECS::Entity& entity = _coordinator.CreateEntity();

    entity.SetTag("Camera");

    entity.AddComponent<Component::Transform>(RayLib::Vector3(0.0f, 100.0f, -50.0f));
    entity.AddComponent<Component::IBehaviour, Component::Camera>(entity, _camera);
    return (entity);
}

ECS::Entity& EntityFactory::createFloor(RayLib::Vector2<float> mapSize)
{
    RayLib::Vector2<float> planeSize(mapSize.x*BOX_SIZE, mapSize.y*BOX_SIZE);
    ECS::Entity& entity = _coordinator.CreateEntity();

    RayLib::Vector3 position(planeSize.x/2-BOX_SIZE/2, -BOX_SIZE/2+1, planeSize.y/2-BOX_SIZE/2);
    RayLib::Mesh planeMesh(planeSize.x, planeSize.y, 1, 1);

    entity.AddComponent<Component::Transform>(position);
    entity.AddComponent<Component::ModelShader, TerrainShader>("../assets/shaders/terrainShader", planeSize);
    entity.AddComponent<Component::Drawable3D>(planeMesh);
    entity.GetComponent<Component::Drawable3D>().SetTexture("../assets/floor.png");
    entity.GetComponent<Component::Drawable3D>().SetShader("../assets/shaders/terrainShader");

    return (entity);
}
