#include "PlaneActor.h"
#include "BoxComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"


PlaneActor::PlaneActor(Game *game) : Actor(game) {
  SetScale(10.0f);
  MeshComponent *mc = new MeshComponent(this);
  Mesh *mesh = GetGame()->GetRenderer()->GetMesh("Assets/Plane.gpmesh");
  mc->SetMesh(mesh);
  // Add collision box
  BoxComponent *bc = new BoxComponent(this);
  bc->SetObjectBox(mesh->GetBox());
}
