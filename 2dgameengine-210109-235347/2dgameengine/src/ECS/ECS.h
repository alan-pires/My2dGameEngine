#ifndef ESC_H
#define ESC_H

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class Entity
{
	private:
		int id;

	public:
		Entity(int id): id(id){};
		int GetId() const;
};

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

class Registry
{

};

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componetId);
}

#endif