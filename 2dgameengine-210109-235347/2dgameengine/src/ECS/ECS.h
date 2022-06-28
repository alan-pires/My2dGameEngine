#ifndef ESC_H
#define ESC_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

// ============================== ENTITY CLASS ====================================
class Entity
{
	private:
		int id;

	public:
		Entity(int id): id(id){};
		int GetId() const;
};

// ============================== COMPONENT CLASSES ====================================
// Interface for classes that inhenrits from it
struct IComponent
{
	protected:
		static int nextId;
};

// used to assign a unique id to a component type
template <typename T>
class Component: public IComponent
{
	//returns the unique id of the component<T>
	static int GetId()
	{
		static auto id = nextId++;
		return id;
	}
};

// ============================== SYSTEM CLASS ====================================
class System
{
	private:
		Signature componentSignature;
		std::vector<Entity> entities;

	public:
		System() = default;
		~System() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityToSystem(Entity entity);
		std::vector<Entity> GetSystemEntities() const;
		const Signature& GetComponetSignature() const;

		template <typename TComponent> void RequireComponent();
};

// ============================== POOL CLASSES ====================================
class IPool
{
	public:
		virtual ~IPool(){}
};

template <typename T>
class Pool: public IPool{
	private:
		std::vector<T> data;
	
	public:
		Pool(int size = 100)
		{
			data.resize(size);
		}
		virtual ~Pool() = default;

		bool isEmpty() const
		{
			return data.empty();
		}

		int GetSize() const
		{
			return data.size();
		}

		void Resize(int n)
		{
			data.resize(n);
		}

		void Clear()
		{
			data.clear();
		}

		void Add(T object)
		{
			data.push_back(object);
		}

		void Set(int index, T object)
		{
			data[index] = object;
		}

		T& Get(int index)
		{
			return static_cast<T&>{data[index]};
		}

		T& operator [](unsigned int index)
		{
			return data[index];
		}
};

// ============================== REGISTRY (MANAGER) CLASS ====================================
class Registry
{
	private:
		int numEntities = 0;

		// Vector of components pools, each pool constains all the data for a certain component type
		// Vector index = component type id
		// Pool index = entity id
		std::vector<IPool*> componentPools;
		std::vector<Signature> entityComponentSignatures;
		std::unordered_map<std::type_index, System*> Systems;
		std::set<Entity> entitiesToBeAdded;
		std::set<Entity> entitiesToBeKilled;

	public:
		Registry() = default;

		Entity CreateEntity();
		void Update();
		void AddEntityToSystem(Entity entity);
		template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
		template <typename TComponent> void RemoveComponent(Entity entity);
		template <typename TComponent> bool HasComponent(Entity entity) const;
};

// ======================== TEMPLATE FUNCTIONS ==============================

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componetId);
}

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	if (componentId >= componentPools.size())
	{
		componentPools.resize(componentId + 1, nullptr);
	}

	if (!componentPools[componentId])
	{
		Pool<TComponent>* newComponentPool = new Pool<TComponent>();
		componentPools[componentId] = newComponentPool;
	}

	Pool<TComponent>* currentComponentPool = componentPools[componentId];

	if (entityId >= currentComponenetPool->GetSize())
	{
		currentComponentPool->Resize(numEntities);
	}

	TComponent newComponent(std::forward<TArgs>(args)...);
	currentComponentPool->Set(entityId, newComponent);
	entityComponentSignatures[entityId].set(componentId);
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	return entityComponentSignatures[entityId].test(componentId);
}

#endif