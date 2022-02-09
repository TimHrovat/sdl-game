#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <class T>
inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

// entity has the maximum of 32 components attached to it
constexpr std::size_t maxComponents = 32; // constexpr - evaluated at compile time, size_t - unsingned type

using ComponentBitSet = std::bitset<maxComponents>;
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
    bool active = true;
    std::vector<std::unique_ptr<Component>> components; // list (vector) of components of specific entity

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;

  public:
    void update() {
        for (auto &c : components)
            c->update(); // updates each component
    }
    void draw() {
        for (auto &c : components)
            c->draw(); // draws each component
    }
    bool isActive() const { return active; }
    void destroy() { active = false; }

    template <class T>
    bool hasComponent() const { return componentBitSet[getComponentTypeID<T>]; }

    // this function adds a component to an entity
    template <class T, class... TArgs>
    T &addComponent(TArgs &&...mArgs) { // variadic function - because component may get multiple arguments
        T *c(new T(std::forward<TArgs>(mArgs)...)); // creates new instance of component
        c->entity = this; // connects a component to an entity
        std::unique_ptr<Component> uPtr{c}; //assigns a unique pointer to a component
        components.emplace_back(std::move(uPtr)); // adds a component to the end of a vector

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

  public:
    void update() {
        for (auto &e : entities)
            e->update(); // updates each entity
    }
    void draw() {
        for (auto &e : entities)
            e->draw(); // draws each entity
    }
    void refresh() {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) {
                           return !mEntity->isActive();
                       }),
                       std::end(entities));
    }

    Entity &addEntity() {
        Entity *e = new Entity();
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};