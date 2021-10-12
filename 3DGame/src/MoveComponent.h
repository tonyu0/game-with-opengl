#pragma once
#include "Component.h"

// moving but not playable actor must have this class. express movement with
// vector and angle.
class MoveComponent : public Component {
public:
	// Lower update order to update first
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	// setter
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetStrafeSpeed() const { return mStrafeSpeed; }
	// getter
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }

	EComponentType GetType() const override { return EComponentType::TMoveComponent; }

	void LoadProperties(const rapidjson::Value& inObj) override;
	void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const override;

protected:
	float mAngularSpeed;
	float mForwardSpeed;
	float mStrafeSpeed;
};
