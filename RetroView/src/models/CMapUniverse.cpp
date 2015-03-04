#include <GL/glew.h>
#include "models/CMapUniverse.hpp"
#include "core/GXCommon.hpp"
#include "core/CMaterial.hpp"
#include "core/CMaterialCache.hpp"
#include "core/CResourceManager.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "models/CMapArea.hpp"

CMapUniverse::CMapUniverse()
{

}

CMapUniverse::~CMapUniverse()
{

}

void CMapUniverse::draw()
{
    CMapArea* hex = dynamic_cast<CMapArea*>(CResourceManager::instance()->loadResourceFromPak(m_source, m_mapAreaID, "mapa"));

    if (!hex)
        return;

    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(.025, .025, .025));
    hex->updateViewProjectionUniforms(m_viewMatrix, m_projectionMatrix);
    for (SMapWorld world : m_worlds)
    {
        for (glm::mat4 transform : world.hexagonTransforms)
        {
            glm::mat4 model = scaleMatrix * world.transform * transform;
            hex->setTransformMatrix(model);
            hex->setColor(world.color);
            hex->draw();
        }
    }
}

void CMapUniverse::drawBoundingBox()
{

}

void CMapUniverse::updateViewProjectionUniforms(const glm::mat4& view, const glm::mat4& proj)
{
    m_viewMatrix = view;
    m_projectionMatrix = proj;
}

SBoundingBox& CMapUniverse::boundingBox()
{
    return m_boundingBox;
}