#pragma once
#include "Component.h"

// pseudo code of Z buffer method (implemented in OpenGL)
// foreach MeshComponent m in scene
//  foreach Pixel p in m
//      float depth = p.Depth()
//      if zBuffer[p.x][p.y] < depth
//          p.draw()

// child class will be SkeletanMeshComponent
class MeshComponent : public Component {
public:
	MeshComponent(class Actor* owner, bool isSkeletal = false);
	~MeshComponent();
	// Draw this mesh component with a given shader.
	virtual void Draw(class Shader* shader);
	// Set the mesh/texture index used by mesh component
	//
	virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
	void SetTextureIndex(size_t index) { mTextureIndex = index; }

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }

	bool GetIsSkeletal() const { return mIsSkeletal; }

	EComponentType GetType() const override { return EComponentType::TMeshComponent; }

	void LoadProperties(const rapidjson::Value& inObj) override;
	void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const override;

protected:
	class Mesh* mMesh;
	size_t mTextureIndex;
	bool mVisible;
	bool mIsSkeletal;
};