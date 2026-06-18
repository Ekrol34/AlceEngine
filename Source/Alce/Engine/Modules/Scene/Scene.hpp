#pragma once

#include <memory>

#include "../../../Libs/Libs.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Chrono/Chrono.hpp"
#include "../B2World/B2World.hpp"
#include "../Interface/Interface.hpp"
#include "../Lighting/Lighting.hpp"

namespace alce
{
    typedef std::shared_ptr<List<GameObjectPtr>> GameObjectListPtr;

    class Scene : public Object
    {
    public:

        Scene(String name);

        void InitPhysics(Vector2 gravity);

        void AddGameObject(GameObjectPtr gameObject, String alias = false);

        List<GameObjectPtr> GetAllGameObjects();

        void AddCanvas(CanvasPtr canvasPtr, ComponentPtr camera);

        String GetName();

        void Pause(bool flag = true);

        bool IsPaused();

        void Clear();

        B2WorldPtr GetWorld();

        void DevelopmentMode(bool flag = true);
        
        bool IsDevelopmentMode()
        {
            return developmentMode;
        }

        void Shell(String prompt);

        void Save();

        bool persist = false;

        int gridMargin = 3;

        bool IsLoading()
        {
            return loading;
        }

        virtual void Init()
        {
            
        }

        virtual void Start()
        {
            
        }

        bool SmartRender = true;

        unsigned int GridScale = 5;

        unsigned int GridTextSize = 9;

        Color GridColor = sf::Color(100, 100, 255, 150);

        Color AxisYColor = sf::Color(50, 150, 255, 200);

        Color AxisXColor = sf::Color(255, 100, 100, 200);

    private:

        friend class CORE;
        friend class GameObject;
        friend class ARL_PROCESSOR;
        friend class Rigidbody2D;
        friend class ParticleSystem;
        
        B2WorldPtr world = nullptr;

        LightingSystem ls;

        String name;
        List<GameObjectPtr> gameObjectList;
        List<GameObjectPtr> pendingAdd;
        unsigned int maxLayer;

        List<CanvasPtr> canvasList;
        List<Object*> cameras;
        bool paused = false;
        bool developmentMode = false;
        bool loading = false;

        Json json;

        void EventsManager(sf::Event& e);

        void Render();

        void Update();

        void SetCardinals(GameObjectPtr gameObject, Dictionary<String, Vector2Ptr> cardinals);

        void RenderGrid(sf::RenderWindow& window, const sf::View& view);

        void UpdateJson();

        void LoadFromJson()
        {
            json.FromFile("./Scenes/" + GetName().ToAnsiString() + ".json");
          
            for(auto& go : gameObjectList)
            {
                bool hasAlias = json.Has(go->alias);
                bool hasId = json.Has(go->id);

                if(hasAlias || hasId) 
                {
                    go->transform.position.FromString(json.GetJson(hasAlias ? go->alias : go->id).GetJson("transform").Get("position"));
                }
            }
        }

        bool JsonFileExists()
        {
            File file("./Scenes/" + GetName().ToAnsiString() + ".json");
            return file.Exists();
        }
       
    };

    typedef std::shared_ptr<Scene> ScenePtr;
}