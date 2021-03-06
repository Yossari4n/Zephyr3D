#ifndef GravityGun_h
#define GravityGun_h

#include <Zephyr3D/cbs/components/Component.h>
#include <Zephyr3D/cbs/components/Transform.h>
#include <Zephyr3D/cbs/connections/PropertyIn.h>

#include <Zephyr3D/cbs/Object.h>
#include <Zephyr3D/Scene.h>

#include <Zephyr3D/ZephyrEngine.h>

#pragma warning(push, 0)
#include <GLFW/glfw3.h>
#pragma warning(pop)

class GravityGun : public zephyr::cbs::Component {
public:
	GravityGun(class zephyr::cbs::Object& object, ID_t id, float range, float impuls_force);

	void Initialize() override;
	void Update() override;

	zephyr::cbs::PropertyIn<zephyr::cbs::Transform*> TransformIn{ this };

private:
	int m_PickUpKey{ GLFW_MOUSE_BUTTON_1 };
	int m_PushKey{ GLFW_MOUSE_BUTTON_2 };

	float m_Range;
	float m_ImpulsForce;

	btRigidBody* m_Target{ nullptr };
	btPoint2PointConstraint* m_Constraint{ nullptr };
	btScalar m_OldPickingDistance{ 0.0f };
	int m_SavedState{ 0 };
	
};

#endif
