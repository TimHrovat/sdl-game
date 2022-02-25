#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
    static ComponentID lastID = 0u;
    return lastID++;
}

template <class T>
inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

// entity has the maximum of 32 components attached to it
constexpr std::size_t maxComponents = 32; // constexpr - evaluated at compile time, size_t - unsingned type
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component {

  public:
    Entity *entity;

    virtual void init() {}   // redeclared in component files
    virtual void update() {} // redeclared in component files
    virtual void draw() {}   // redeclared in component files

    virtual ~Component() {} // redeclared in component files
};

class Entity {
  private:
    Manager &manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components; // list (vector) of components of specific entity

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

  public:
    Entity(Manager &mManager) : manager(mManager) {}

    void update() {
        for (auto &c : components)
            c->update(); // updates each component
    }
    void draw() {
        for (auto &c : components)
            c->draw(); // draws each component
    }
    bool isActive() const {
        return active;
    }
    void destroy() {
        active = false;
    }

    template <class T>
    bool hasComponent() const {
        return componentBitSet[getComponentTypeID<T>()];
    }

    bool hasGroup(Group mGroup) {
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup) {
        groupBitSet[mGroup] = false;
    }

    // this function adds a component to an entity
    template <class T, class... TArgs>
    T &addComponent(TArgs &&...mArgs) {             // variadic function - because component may get multiple arguments
        T *c(new T(std::forward<TArgs>(mArgs)...)); // creates new instance of component
        c->entity = this;                           // connects a component to an entity
        std::unique_ptr<Component> uPtr{c};         // assigns a unique pointer to a component
        components.emplace_back(std::move(uPtr));   // adds a component to the end of a vector

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init(); // initializes the component
        return *c;
    }

    template <class T>
    T &getComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(ptr);
    }
};

class Manager {
  private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity *>, maxGroups> groupedEntities;

  public:
    void
    update() {
        for (auto &e : entities)
            e->update(); // updates each entity
    }
    void draw() {
        for (auto &e : entities)
            e->draw(); // draws each entity
    }
    void refresh() {
        for (auto i(0u); i < maxGroups; i++) {
            auto &v(groupedEntities[i]);
            v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity *mEntity) { return !mEntity->isActive() || !mEntity->hasGroup(i); }), std::end(v));
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) {
                           return !mEntity->isActive();
                       }),
                       std::end(entities));
    }

    void AddToGroup(Entity *mEntity, Group mGroup) {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity *> &getGroup(Group mGroup) {
        return groupedEntities[mGroup];
    }

    Entity &addEntity() {
        Entity *e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};