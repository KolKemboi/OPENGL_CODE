#include <entt/entt.hpp>
#include <iostream>


void creating()
{
	entt::registry reg;

	entt::entity ent = reg.create();
	std::cout << "CREATED ENTT" << (int)ent << std::endl;

	reg.destroy(ent);
	std::cout << "DESTROYED ENTT" << (int)ent << std::endl;
}


void components()
{
	struct Pos
	{
		float x, y;
	};

	struct Vel
	{
		float dx, dy;
	};

	entt::registry reg;

	entt::entity ent = reg.create();
	reg.emplace<Pos>(ent, 10.0f, 10.0f);
	reg.emplace<Vel>(ent, 1.0f, 1.0f);

	auto& pos = reg.get<Pos>(ent);
	auto& vel = reg.get<Vel>(ent);

	pos.x += vel.dx;
	pos.y += vel.dy;

	std::cout << "Pos" << pos.x << pos.y << std::endl;

}

void removing()
{
	struct Pos
	{
		float x, y;
	};

	entt::registry reg;
	entt::entity ent = reg.create();

	reg.emplace<Pos>(ent, 10.0f, 20.0f);

	auto& pos = reg.get<Pos>(ent);

	std::cout << pos.x << pos.y << std::endl;

	reg.remove<Pos>(ent);
	
	
}

void query()
{
	struct Pos
	{
		float x, y;
	};
	struct Vel
	{
		float dx, dy;
	};

	entt::registry reg;

	for (unsigned int i = 0; i < 5; i++)
	{
		entt::entity ent = reg.create();
		reg.emplace<Pos>(ent, i * 10.0f, i * 20.0f);
		reg.emplace<Vel>(ent, i * 1.0f, i * 2.0f);

	}

	auto view = reg.view<Pos, Vel>();

	for (auto entity : view)
	{
		auto& pos = view.get<Pos>(entity);
		auto& vel = view.get<Vel>(entity);

		pos.x += vel.dx;
		pos.y += vel.dy;

		std::cout << pos.x << "  " << pos.y << std::endl;
	}
}

int main()
{
	creating();
	components();
	removing();
	query();
}