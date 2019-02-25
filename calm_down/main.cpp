#include <irrlicht.h>
#include <S3DVertex.h>
#include <cmath>

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif



int main() {
	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 32, false);
	if (!device) {
		return 1;
	}
	irr::video::IVideoDriver *driver = device->getVideoDriver();
	irr::scene::ISceneManager *manager = device->getSceneManager();
	manager->addCameraSceneNode(0, irr::core::vector3df(0, -2, 0), irr::core::vector3df(0, 0, 0));
	irr::scene::SMesh *mesh = new irr::scene::SMesh();
	irr::scene::SMeshBuffer *buffer = new irr::scene::SMeshBuffer();
	mesh->addMeshBuffer(buffer);
	buffer->drop();

	irr::f32 angy0 = irr::core::PI / 2 - atan(1 / 2);
	irr::f32 angy1 = irr::core::PI / 2 - atan(-1 / 2);
	irr::f32 angz0 = irr::core::PI / 5;
	irr::f32 angz1 = angz0 * 2;
	irr::f32 angz2 = angz1 * 2;
	irr::f32 x0 = 0;
	irr::f32 x1 = sin(angy0) * sin(angz2);
	irr::f32 x2 = sin(angy0) * sin(angz1);
	irr::f32 y0 = cos(angy0);
	irr::f32 y1 = 1;
	irr::f32 z0 = 0;
	irr::f32 z1 = sin(angy0) * cos(angz1);
	irr::f32 z2 = sin(angy1) * cos(angz0);
	irr::f32 z3 = sin(angy0);

	irr::core::vector3df v[12];

	v[0] = irr::core::vector3df(x0, y1, z0);
	v[1] = irr::core::vector3df(x0, y0, z3);
	v[2] = irr::core::vector3df(x2, y0, z1);
	v[3] = irr::core::vector3df(x1, y0, -z2);
	v[4] = irr::core::vector3df(-x1, y0, -z2);
	v[5] = irr::core::vector3df(-x2, y0, z1);
	v[6] = irr::core::vector3df(x1, -y0, z2);
	v[7] = irr::core::vector3df(x2, -y0, -z1);
	v[8] = irr::core::vector3df(x0, -y0, -z3);
	v[9] = irr::core::vector3df(-x2, -y0, -z1);
	v[10] = irr::core::vector3df(-x1, -y0, z2);
	v[11] = irr::core::vector3df(x0, -y1, z0);

	buffer->Vertices.reallocate(60);
	buffer->Vertices.set_used(60);

	buffer->Vertices[0] = irr::video::S3DVertex(v[0], v[0], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[1] = irr::video::S3DVertex(v[1], v[1], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[2] = irr::video::S3DVertex(v[2], v[2], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[3] = irr::video::S3DVertex(v[0], v[0], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[4] = irr::video::S3DVertex(v[2], v[2], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[5] = irr::video::S3DVertex(v[3], v[3], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[6] = irr::video::S3DVertex(v[0], v[0], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[7] = irr::video::S3DVertex(v[3], v[3], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[8] = irr::video::S3DVertex(v[4], v[4], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[9] = irr::video::S3DVertex(v[0], v[0], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[10] = irr::video::S3DVertex(v[4], v[4], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[11] = irr::video::S3DVertex(v[5], v[5], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[12] = irr::video::S3DVertex(v[0], v[0], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[13] = irr::video::S3DVertex(v[5], v[5], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[14] = irr::video::S3DVertex(v[1], v[1], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[15] = irr::video::S3DVertex(v[1], v[1], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[16] = irr::video::S3DVertex(v[6], v[6], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[17] = irr::video::S3DVertex(v[2], v[2], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[18] = irr::video::S3DVertex(v[2], v[2], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[19] = irr::video::S3DVertex(v[6], v[6], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[20] = irr::video::S3DVertex(v[7], v[7], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[21] = irr::video::S3DVertex(v[2], v[2], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[22] = irr::video::S3DVertex(v[7], v[7], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[23] = irr::video::S3DVertex(v[3], v[3], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[24] = irr::video::S3DVertex(v[3], v[3], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[25] = irr::video::S3DVertex(v[7], v[7], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[26] = irr::video::S3DVertex(v[8], v[8], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[27] = irr::video::S3DVertex(v[3], v[3], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[28] = irr::video::S3DVertex(v[8], v[8], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[29] = irr::video::S3DVertex(v[4], v[4], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[30] = irr::video::S3DVertex(v[4], v[4], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[31] = irr::video::S3DVertex(v[8], v[8], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[32] = irr::video::S3DVertex(v[9], v[9], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[33] = irr::video::S3DVertex(v[4], v[4], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[34] = irr::video::S3DVertex(v[9], v[9], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[35] = irr::video::S3DVertex(v[5], v[5], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[36] = irr::video::S3DVertex(v[5], v[5], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[37] = irr::video::S3DVertex(v[9], v[9], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[38] = irr::video::S3DVertex(v[10], v[10], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[39] = irr::video::S3DVertex(v[5], v[5], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[40] = irr::video::S3DVertex(v[10], v[10], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[41] = irr::video::S3DVertex(v[1], v[1], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[42] = irr::video::S3DVertex(v[1], v[1], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[43] = irr::video::S3DVertex(v[10], v[10], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[44] = irr::video::S3DVertex(v[6], v[6], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[45] = irr::video::S3DVertex(v[6], v[6], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[46] = irr::video::S3DVertex(v[11], v[11], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[47] = irr::video::S3DVertex(v[7], v[7], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[48] = irr::video::S3DVertex(v[7], v[7], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[49] = irr::video::S3DVertex(v[11], v[11], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[50] = irr::video::S3DVertex(v[8], v[8], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[51] = irr::video::S3DVertex(v[8], v[8], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[52] = irr::video::S3DVertex(v[11], v[11], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[53] = irr::video::S3DVertex(v[9], v[9], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[54] = irr::video::S3DVertex(v[9], v[9], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[55] = irr::video::S3DVertex(v[11], v[11], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[56] = irr::video::S3DVertex(v[10], v[10], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

	buffer->Vertices[57] = irr::video::S3DVertex(v[10], v[10], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    buffer->Vertices[58] = irr::video::S3DVertex(v[11], v[11], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
	buffer->Vertices[59] = irr::video::S3DVertex(v[6], v[6], irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));

    buffer->Indices.reallocate(60);
    buffer->Indices.set_used(60);

    for (int i = 0; i < 60; ++i) {
    	buffer->Indices[i] = i;
    }

    buffer->recalculateBoundingBox();

	irr::scene::IMeshSceneNode *node = manager->addMeshSceneNode(mesh);

	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	while (device->run()) {
        driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
        manager->drawAll();
        driver->endScene();
	}

	device->drop();

	return EXIT_SUCCESS;

}
