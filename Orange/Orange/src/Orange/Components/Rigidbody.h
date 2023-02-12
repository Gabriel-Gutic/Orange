#pragma once


namespace Orange
{
	struct Rigidbody
	{
		float Mass;
		bool Gravity;

		Rigidbody() = default;

		static std::string GetName();
	};
}