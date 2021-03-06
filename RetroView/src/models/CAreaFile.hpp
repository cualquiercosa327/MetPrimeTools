#ifndef MREAFILE_HPP
#define MREAFILE_HPP

#include "core/CModelData.hpp"
#include "core/IRenderableModel.hpp"
#include "core/IResource.hpp"
#include "core/GXCommon.hpp"
#include "core/CScene.hpp"
#include "CAreaBspTree.hpp"

#include <vector>
#include <string>

struct SAABB
{
    SBoundingBox aabb;
    atInt32 unkIndex; // -1 for area extents
    atInt16 selfIndex1; // if this value != -1, this is the root AABB, 1 indexed
    atInt16 selfIndex2; // if this value != -1, this is a child AABB, 1 indexed
};

class CAreaFile : public IRenderableModel, public IResource
{
public:
    enum Version
    {
        MetroidPrimeDemo = 12,
        MetroidPrime1 = 15,
        MetroidPrime2 = 25,
        MetroidPrime3 = 30,
        DKCR          = 32
    };

    CAreaFile();
    virtual ~CAreaFile();

    void exportToObj(const std::string& filename);


    void draw();
    void drawBoundingBox();
    void updateViewProjectionUniforms(const CTransform& view, const CProjection& proj);
    void updateTexturesEnabled(const bool& enabled);

    CTransform transform() const;

    SBoundingBox& boundingBox();

    CMaterialSet& currentMaterialSet();

    bool canExport() const { return true; }

    atUint32 materialSetCount() const;
    atUint32 currentMaterialSetIndex() const;
    void setCurrentMaterialSet(atUint32 set);

    void nearestSpawnPoint(const CVector3f& pos, CVector3f& targetPos, CVector3f& rot);
    bool skyEnabled();
private:
    friend class CAreaReader;
    friend class CAreaBspTree;
    void drawIbos(bool transparents, CMaterialSet& materialSet, const CTransform& model);
    void buildBBox();

    Version                         m_version;
    // Buffers
    // GL specific code
    CVertexBuffer                   m_vertexBuffer;
    CIndexBuffer                    m_indexBuffer;
    std::vector<CMaterialSet>       m_materialSets;
    atUint32                        m_currentSet;
    std::vector<CModelData>         m_models;
    std::vector<SAABB>              m_aabbs;
    CTransform                      m_transform;
    SBoundingBox                    m_boundingBox;
    CAreaBspTree                    m_bspTree;
    // HACK: CAreaFile should be part of CScene, not the other way around
    std::vector<CScene*>            m_scriptLayers; // NOT FINAL!!!
};

#endif // MREAFILE_HPP
