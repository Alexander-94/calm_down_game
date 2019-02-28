#include <irrlicht.h>
#include <S3DVertex.h>
#include <cmath>

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

struct map {
    int face[3];
};

struct node {
    irr::core::vector3df vert;
    int *next;
};

struct nodes {
    struct node *node_arr;
    int node_len;
    nodes (int map_size) {
        node_arr = (struct node*)malloc((10 * map_size * map_size + 2) * sizeof(struct node));
        node_len = 0;
    }
    int add(irr::core::vector3df vert) {
        if (node_len) {
            for (int i = 0; i < node_len; ++i) {
                if (node_arr[i].vert.equals(vert)) {
                    return i;
                }
            }
        }
        node_arr[node_len].vert = vert;
        ++node_len;
        return node_len - 1;
    }
    ~nodes() {
        free(node_arr);
    }
};

irr::core::vector3df vector_combine(irr::core::vector3df v1, irr::core::vector3df v2, irr::core::vector3df v3, float f1, float f2, float f3) {
    irr::core::vector3df result;
    result.X = f1 * v1.X + f2 * v2.X + f3 * v3.X;
    result.Y = f1 * v1.Y + f2 * v2.Y + f3 * v3.Y;
    result.Z = f1 * v1.Z + f2 * v2.Z + f3 * v3.Z;
    return result;
}

int main() {

    // 34 and larger value crashes buffer
    const int map_size = 33;

    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 32, false);
    if (!device) {
        return 1;
    }
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager *manager = device->getSceneManager();
    manager->addCameraSceneNode(0, irr::core::vector3df(0.0, -1.7, 0.0), irr::core::vector3df(0.0, 0.0, 0.0));
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

    irr::core::vector3df f[20][3];

    f[0][0] = v[0];
    f[0][1] = v[1];
    f[0][2] = v[2];

    f[1][0] = v[0];
    f[1][1] = v[2];
    f[1][2] = v[3];

    f[2][0] = v[0];
    f[2][1] = v[3];
    f[2][2] = v[4];

    f[3][0] = v[0];
    f[3][1] = v[4];
    f[3][2] = v[5];

    f[4][0] = v[0];
    f[4][1] = v[5];
    f[4][2] = v[1];

    f[5][0] = v[1];
    f[5][1] = v[6];
    f[5][2] = v[2];

    f[6][0] = v[2];
    f[6][1] = v[6];
    f[6][2] = v[7];

    f[7][0] = v[2];
    f[7][1] = v[7];
    f[7][2] = v[3];

    f[8][0] = v[3];
    f[8][1] = v[7];
    f[8][2] = v[8];

    f[9][0] = v[3];
    f[9][1] = v[8];
    f[9][2] = v[4];

    f[10][0] = v[4];
    f[10][1] = v[8];
    f[10][2] = v[9];

    f[11][0] = v[4];
    f[11][1] = v[9];
    f[11][2] = v[5];

    f[12][0] = v[5];
    f[12][1] = v[9];
    f[12][2] = v[10];

    f[13][0] = v[5];
    f[13][1] = v[10];
    f[13][2] = v[1];

    f[14][0] = v[1];
    f[14][1] = v[10];
    f[14][2] = v[6];

    f[15][0] = v[6];
    f[15][1] = v[11];
    f[15][2] = v[7];

    f[16][0] = v[7];
    f[16][1] = v[11];
    f[16][2] = v[8];

    f[17][0] = v[8];
    f[17][1] = v[11];
    f[17][2] = v[9];

    f[18][0] = v[9];
    f[18][1] = v[11];
    f[18][2] = v[10];

    f[19][0] = v[10];
    f[19][1] = v[11];
    f[19][2] = v[6];

    int i = 0;
    float gap = 0.03;

    const int map_len = 20 * map_size * map_size;
    struct map map[map_len];
    struct nodes nodes(map_size);

    for (int j = 0; j < 20; ++j) {
        for (int k = 0; k < map_size; ++k) {
            for (int l = 0; l < map_size; ++l) {
                if ((k + l) <= (map_size - 1)) {
                    map[i].face[0] = nodes.add(vector_combine(f[j][0], f[j][1], f[j][2], k, l, map_size - k - l));
                    map[i].face[1] = nodes.add(vector_combine(f[j][0], f[j][1], f[j][2], k + 1, l, map_size - 1 - k - l));
                    map[i].face[2] = nodes.add(vector_combine(f[j][0], f[j][1], f[j][2], k, l + 1, map_size - 1 - k - l));
                    ++i;
                    if ((k + l) != map_size - 1) {
                        map[i].face[0] = nodes.add(vector_combine(f[j][0], f[j][1], f[j][2], k + 1, l + 1, map_size - 2 - k - l));
                        map[i].face[1] = map[i - 1].face[2];
                        map[i].face[2] = map[i - 1].face[1];
                        ++i;
                    }
                }
            }
        }
    }

    for (i = 0; i < nodes.node_len; ++i) {
        nodes.node_arr[i].vert.normalize();
    }

    buffer->Vertices.reallocate(map_len * 3);
    buffer->Vertices.set_used(map_len * 3);
    for (i = 0; i < map_len; ++i) {
        irr::core::vector3df temp = vector_combine(nodes.node_arr[map[i].face[0]].vert, nodes.node_arr[map[i].face[1]].vert, nodes.node_arr[map[i].face[2]].vert, 1 - gap * 2, gap, gap);
        buffer->Vertices[i * 3 + 0] = irr::video::S3DVertex(temp, temp, irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
        temp = vector_combine(nodes.node_arr[map[i].face[0]].vert, nodes.node_arr[map[i].face[1]].vert, nodes.node_arr[map[i].face[2]].vert, gap, 1 - gap * 2, gap);
        buffer->Vertices[i * 3 + 1] = irr::video::S3DVertex(temp, temp, irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
        temp = vector_combine(nodes.node_arr[map[i].face[0]].vert, nodes.node_arr[map[i].face[1]].vert, nodes.node_arr[map[i].face[2]].vert, gap, gap, 1 - gap * 2);
        buffer->Vertices[i * 3 + 2] = irr::video::S3DVertex(temp, temp, irr::video::SColor(255, 0, 255, 0), irr::core::vector2df(0, 0));
    }

    buffer->Indices.reallocate(map_len * 3);
    buffer->Indices.set_used(map_len * 3);
    for (i = 0; i < map_len; ++i) {
        buffer->Indices[i * 3 + 0] = i * 3 + 0;
        buffer->Indices[i * 3 + 1] = i * 3 + 1;
        buffer->Indices[i * 3 + 2] = i * 3 + 2;
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
