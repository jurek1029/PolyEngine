#include "EnginePCH.hpp"

#include "MovementSystem.hpp"

using namespace Poly;

void Poly::MovementSystem::MovementUpdatePhase(World* world)
{
	
	
	for (auto freeFloatTuple : world->IterateComponents<FreeFloatMovementComponent, TransformComponent>())
	{
		TransformComponent* transCmp = std::get<TransformComponent*>(freeFloatTuple);
		FreeFloatMovementComponent* freeFloatMovementCmp = std::get<FreeFloatMovementComponent*>(freeFloatTuple);

		Vector move;
		if (world->GetInputWorldComponent().IsPressed(eKey::KEY_W))
			move -= Vector::UNIT_Z;
		else if (world->GetInputWorldComponent().IsPressed(eKey::KEY_S))
			move += Vector::UNIT_Z;

		if (world->GetInputWorldComponent().IsPressed(eKey::KEY_A))
			move -= Vector::UNIT_X;
		else if (world->GetInputWorldComponent().IsPressed(eKey::KEY_D))
			move += Vector::UNIT_X;

		if (move.Length2() > 0)
			move.Normalize();
		move *= freeFloatMovementCmp->GetMovementSpeed() * 0.016f; //TMP dt

		transCmp->SetLocalTranslation(transCmp->GetLocalTranslation() + transCmp->GetLocalRotation() * move);
		
		if (world->GetInputWorldComponent().IsPressed(eKey::MLBUTTON))
		{
			Vector delta = world->GetInputWorldComponent().GetMousePosDelta();

			Quaternion rot = Quaternion(Vector::UNIT_Y, Angle::FromRadians(-delta.X * freeFloatMovementCmp->GetRotationSpeed()));
			rot *= transCmp->GetLocalRotation();
			rot *= Quaternion(Vector::UNIT_X, Angle::FromRadians(-delta.Y * freeFloatMovementCmp->GetRotationSpeed()));

			if (rot != Quaternion()) {
				rot.Normalize();
				transCmp->SetLocalRotation(rot);
			}
		}
	}
}

Vector Poly::MovementSystem::GetLocalForward(const TransformComponent* transform)
{
	return transform->GetLocalRotation() * -Vector::UNIT_Z;
}

Vector Poly::MovementSystem::GetLocalRight(const TransformComponent* transform)
{
	return transform->GetLocalRotation() * Vector::UNIT_X;
}

Vector Poly::MovementSystem::GetLocalUp(const TransformComponent* transform)
{
	return transform->GetLocalRotation() * Vector::UNIT_Y;
}

Vector Poly::MovementSystem::GetGlobalForward(const TransformComponent* transform)
{
	return transform->GetGlobalRotation() * -Vector::UNIT_Z;
}

Vector Poly::MovementSystem::GetGlobalRight(const TransformComponent* transform)
{
	return transform->GetGlobalRotation() * Vector::UNIT_X;
}

Vector Poly::MovementSystem::GetGlobalUp(const TransformComponent* transform)
{
	return transform->GetGlobalRotation() * Vector::UNIT_Y;
}
