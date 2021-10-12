#pragma once
#include "Component.h"
#include "SDL/SDL.h"

class SpriteComponent : public Component {
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }

	EComponentType GetType() const override { return EComponentType::TSpriteComponent; }

	void LoadProperties(const rapidjson::Value& inObj) override;
	void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const override;

protected:
	class Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
	bool mVisible;
};
