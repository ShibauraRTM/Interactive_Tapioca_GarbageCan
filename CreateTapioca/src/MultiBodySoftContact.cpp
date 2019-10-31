//本プログラムはBullet Physics SDKに付属のサンプルプログラム「MultiBodySoftContact」を改変して使用している。
#include "MultiBodySoftContact.h"

#include "BulletDynamics/Featherstone/btMultiBodyLinkCollider.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointFeedback.h"

#include "../examples/CommonInterfaces/CommonMultiBodyBase.h"
#include "../examples/Utils/b3ResourcePath.h"

#include "BulletSoftBody/btSoftBodyHelpers.h"
#include <cstdlib>
#include <ctime>

//static btScalar radius(0.2);

struct MultiBodySoftContact : public CommonMultiBodyBase
{
	btMultiBody* m_multiBody;
	btAlignedObjectArray<btMultiBodyJointFeedback*> m_jointFeedbacks;

	bool m_once;

	int TapiNum;

public:
	MultiBodySoftContact(struct GUIHelperInterface* helper);
	virtual ~MultiBodySoftContact();

	virtual void initPhysics();
	void TheWall(btVector3 xyz, btQuaternion q);
	
	virtual void stepSimulation(float deltaTime);

	virtual void resetCamera()
	{
		float dist = 1.3;
		float pitch = -19.199980;//縦角度
		float yaw = -92.000137;//横角度
		float targetPos[3] = { -4.563782,0.244460,11.988424 };
		m_guiHelper->resetCamera(dist, yaw, pitch, targetPos[0], targetPos[1], targetPos[2]);
	}
	///////////////////////////
	virtual bool keyboardCallback(int key, int state);
	void addTapioca(double x, double y, double z, btVector4 color);
	void removeTapioca(int icollision, int imultibody);
	void removeAllTapioca();
	void setTexture(int textureUniqueId, int texWidth, int texHeight, int red, int green, int blue);
	///////////////////////////
};

MultiBodySoftContact::MultiBodySoftContact(struct GUIHelperInterface* helper)
	: CommonMultiBodyBase(helper),
	  m_once(true)
{
	TapiNum = 0;
}

MultiBodySoftContact::~MultiBodySoftContact()
{
}

void MultiBodySoftContact::initPhysics()
{
	int upAxis = 2;

	m_guiHelper->setUpAxis(upAxis);

	btVector4 colors[4] =
	{
		btVector4(1, 0.8, 0.5, 1),
		btVector4(0, 1, 0, 1),
		btVector4(0, 1, 1, 1),
		btVector4(1, 1, 0, 1),
	};
	int curColor = 0;

	this->createEmptyDynamicsWorld();
	m_dynamicsWorld->setGravity(btVector3(0, 0, -1.0));

	m_guiHelper->createPhysicsDebugDrawer(m_dynamicsWorld);
	m_dynamicsWorld->getDebugDrawer()->setDebugMode(
		//btIDebugDraw::DBG_DrawConstraints
		+btIDebugDraw::DBG_DrawWireframe + btIDebugDraw::DBG_DrawContactPoints + btIDebugDraw::DBG_DrawAabb);  //+btIDebugDraw::DBG_DrawConstraintLimits);

	//create a static ground object
	if (1)
	{
		btVector3 groundHalfExtents(6, 6, 1);
		btBoxShape* box = new btBoxShape(groundHalfExtents);
		box->initializePolyhedralFeatures();

		m_guiHelper->createCollisionShapeGraphicsObject(box);
		btTransform start;
		start.setIdentity();
		btVector3 groundOrigin(0, 0, -1);
		start.setOrigin(groundOrigin);
		//	start.setRotation(groundOrn);
		btRigidBody* body = createRigidBody(0, start, box);

		//setContactStiffnessAndDamping will enable compliant rigid body contact
		body->setContactStiffnessAndDamping(300, 10);
		btVector4 color = colors[curColor];
		curColor++;
		curColor &= 3;
		m_guiHelper->createRigidBodyGraphicsObject(body, color);
	}
	
	for (int i = 0; i < 12 ; ++i)
	{
		double r, a;
		r = 5.65;
		a = 3.141592 / 6;
		btVector3 position(r*cos(a*i), r*sin(a*i), 20 );
		btQuaternion quat(btVector3(0, 0, 1), a*i);
		
		TheWall(position, quat);

	}
				
	}

	
	
void MultiBodySoftContact::stepSimulation(float deltaTime)
{
	if (0)  //m_once)
	{
		m_once = false;
		m_multiBody->addJointTorque(0, 10.0);//kokoha?hankei?

		btScalar torque = m_multiBody->getJointTorque(0);
		b3Printf("t = %f,%f,%f\n", torque, torque, torque);  //[0],torque[1],torque[2]);
	}

	m_dynamicsWorld->stepSimulation(deltaTime);
}

bool MultiBodySoftContact::keyboardCallback(int key, int state)
{
	static int i = 6;
	if ((key == B3G_F3) && state && m_dynamicsWorld)
	{
		btDefaultSerializer* serializer = new btDefaultSerializer();
		m_dynamicsWorld->serialize(serializer);

		FILE* file=fopen("testFILE.bullet", "wb");
		fwrite(serializer->getBufferPointer(), serializer->getCurrentBufferSize(), 1, file);
		fclose(file);

		delete serializer;
		return true;
	}
	if (key == 'a' && state) {

		addTapioca((double)rand() / RAND_MAX , (double)rand() / RAND_MAX , 15, btVector4(0.3, 0.3, 0.3, 0.8));
	}
	else if (key == 'r' && state) {
		//removeTapioca(m_dynamicsWorld->getNumCollisionObjects() - 5, m_dynamicsWorld->getNumMultibodies() - 5);
		removeAllTapioca();
	}
}

void MultiBodySoftContact::addTapioca(double x, double y, double z, btVector4 color)
{
	btCollisionShape* childShape = new btSphereShape(btScalar(1.0));
	m_guiHelper->createCollisionShapeGraphicsObject(childShape);

	btScalar mass = 1;
	btVector3 baseInertiaDiag;
	bool isFixed = (mass == 0);
	childShape->calculateLocalInertia(mass, baseInertiaDiag);
	btMultiBody* pMultiBody = new btMultiBody(0, 1, baseInertiaDiag, false, false);
	btTransform startTrans;
	startTrans.setIdentity();
	//startTrans.setOrigin(btVector3(0, 0, 20));

	startTrans.setOrigin(btVector3(x, y, z));

	pMultiBody->setBaseWorldTransform(startTrans);

	btMultiBodyLinkCollider* col = new btMultiBodyLinkCollider(pMultiBody, -1);
	col->setCollisionShape(childShape);
	pMultiBody->setBaseCollider(col);
	bool isDynamic = (mass > 0 && !isFixed);
	int collisionFilterGroup = isDynamic ? int(btBroadphaseProxy::DefaultFilter) : int(btBroadphaseProxy::StaticFilter);
	int collisionFilterMask = isDynamic ? int(btBroadphaseProxy::AllFilter) : int(btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);

	m_dynamicsWorld->addCollisionObject(col, collisionFilterGroup, collisionFilterMask);  //, 2,1+2);

	pMultiBody->finalizeMultiDof();

	m_dynamicsWorld->addMultiBody(pMultiBody);

	btAlignedObjectArray<btQuaternion> scratch_q;
	btAlignedObjectArray<btVector3> scratch_m;
	pMultiBody->forwardKinematics(scratch_q, scratch_m);
	btAlignedObjectArray<btQuaternion> world_to_local;
	btAlignedObjectArray<btVector3> local_origin;
	pMultiBody->updateCollisionObjectWorldTransforms(world_to_local, local_origin);
	//

	//generate graphic object
	btCollisionObject* colObj = m_dynamicsWorld->getCollisionObjectArray()[m_dynamicsWorld->getNumCollisionObjects() - 1];
	btSoftBody* sb = btSoftBody::upcast(colObj);
	if (sb)
	{
		colObj->getCollisionShape()->setUserPointer(sb);
	}
	m_guiHelper->createCollisionShapeGraphicsObject(colObj->getCollisionShape());

	m_guiHelper->createCollisionObjectGraphicsObject(colObj, color);
	//Texture
	setTexture(2, 1024, 1024, 192, 192, 192);
/*
	//testcamera
	float a[16], b[16], c[3], d[3], e[3], f[3], yaw, pitch, dist, target[3];
	int w, h;

	m_guiHelper->getCameraInfo(&w, &h, a, b, c, d, e, f, &yaw, &pitch, &dist, target);
	printf("yaw=%f \n pitch=%f \n dist=%f \n target=%f,%f,%f \n", yaw, pitch, dist, target[0], target[1], target[2]);
	*/

	TapiNum++;
	}

void MultiBodySoftContact::setTexture(int textureUniqueId, int texWidth, int texHeight, int red, int green, int blue)
{
	btAlignedObjectArray<unsigned char> texels;
	texels.resize(texWidth * texHeight * 3);
	for (int i = 0; i < texWidth; i++)
	{
		for (int j = 0; j < texHeight; j++)
		{
			texels[(i + j * texWidth) * 3 + 0] = red;
			texels[(i + j * texWidth) * 3 + 1] = green;
			texels[(i + j * texWidth) * 3 + 2] = blue;
		}
	}
	m_guiHelper->changeTexture(textureUniqueId, &texels[0], texWidth, texHeight);
}

void MultiBodySoftContact::TheWall(btVector3 xyz, btQuaternion q)
{
	btVector3 groundHalfExtents(0.25, 1.5, 21);
	btBoxShape* box = new btBoxShape(groundHalfExtents);
	box->initializePolyhedralFeatures();

	m_guiHelper->createCollisionShapeGraphicsObject(box);
	btTransform start(q, xyz);

	btRigidBody* body = createRigidBody(0, start, box);

	//setContactStiffnessAndDamping will enable compliant rigid body contact
	body->setContactStiffnessAndDamping(300, 10);
	btVector4 colors[4] =
	{
		btVector4(1, 0.8, 0.5, 1),
		btVector4(0, 1, 0, 1),
		btVector4(0, 1, 1, 1),
		btVector4(1, 1, 0, 1),
	};
	int curColor = 0;
	btVector4 color = colors[curColor];
	curColor++;
	curColor &= 3;
	m_guiHelper->createRigidBodyGraphicsObject(body, color);
	m_guiHelper->autogenerateGraphicsObjects(m_dynamicsWorld);
}

void MultiBodySoftContact::removeTapioca(int icollision, int imultibody)
{
	//error check
	if (icollision >= m_dynamicsWorld->getNumCollisionObjects() && icollision < m_dynamicsWorld->getNumCollisionObjects()-TapiNum) { return; }

	//removeObject
	m_guiHelper->removeGraphicsInstance(m_dynamicsWorld->getCollisionObjectArray()[icollision]->getUserIndex());
	printf("remove index= %d, Uid=%d\n", icollision , m_dynamicsWorld->getCollisionObjectArray()[icollision]->getUserIndex());

	if (m_dynamicsWorld)
	{
		btMultiBody* mb = m_dynamicsWorld->getMultiBody(imultibody);
		m_dynamicsWorld->removeMultiBody(mb);
		delete mb;

		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[icollision];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject(obj);
		delete obj;

		TapiNum--;
	}
}

void MultiBodySoftContact::removeAllTapioca()
{
	while (TapiNum != 0) {
		removeTapioca(m_dynamicsWorld->getNumCollisionObjects() - 1, m_dynamicsWorld->getNumMultibodies() - 1);
	}
}


class CommonExampleInterface* MultiBodySoftContactCreateFunc(struct CommonExampleOptions& options)
{
	return new MultiBodySoftContact(options.m_guiHelper);
}
