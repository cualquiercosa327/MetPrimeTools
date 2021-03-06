#ifndef CMATERIALCACHE_HPP
#define CMATERIALCACHE_HPP


#include <vector>
#include <memory>
#include <unordered_map>
#include <Athena/Types.hpp>
#include <QOpenGLShader>
#include "core/CMaterial.hpp"

class CMaterialCache : QObject
{
    Q_OBJECT
public:
    typedef std::vector<CMaterial>::iterator       MaterialIterator;
    typedef std::vector<CMaterial>::const_iterator ConstMaterialIterator;
    CMaterialCache();
    virtual ~CMaterialCache();


    void initialize();
    CMaterial& defaultMaterial();
    static std::shared_ptr<CMaterialCache> instance();
    atUint32 addMaterial(const CMaterial& mat);
    CMaterial& material(atUint32 index);

    void setAmbientOnMaterials(std::vector<atUint32> materials, const CColor& ambient);

    QOpenGLShader* shaderFromSource(const QString& source, QOpenGLShader::ShaderType type);

private:
    std::vector<CMaterial> m_cachedMaterials;
    std::unordered_map<atUint64, QOpenGLShader*> m_vertexShaders;
    std::unordered_map<atUint64, QOpenGLShader*> m_fragmentShaders;
};

#endif // CMATERIALCACHE_HPP
