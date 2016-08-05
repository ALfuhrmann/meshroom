#pragma once

#include <QOpenGLFunctions_3_2_Core>
#include <QObject>
#include <QColor>
#include <QVector3D>
#include "GLScene.hpp"
#include "GLPointCloud.hpp"
#include "GLAligner.hpp"

namespace meshroom
{

class GLView;
class GLPointCloud;
class GLSLBackgroundShader;

class GLRenderer : public QObject
{
    Q_OBJECT

public:
    GLRenderer();
    ~GLRenderer();

public:
    void setViewport(const QRect& viewport);
    void setCameraMatrix(const QMatrix4x4& cameraMat);
    void setClearColor(const QColor& color);
    void addAlembicScene(const QUrl& url);
    void resetScene();
    void setShowCameras(bool v);
    void setShowGrid(bool v);
    
    void addPointsToSelection(const QRectF& selection);
    void clearSelection();
    const std::vector<QVector3D>& getSelection() const { return _selection; }
    
    void setPlane(const QVector3D& normal, const QVector3D& origin);
    void clearPlane();
    
    void setDistanceLine(const QPointF& p0, const QPointF& p1);
    void clearDistanceLine();
    

public slots:
    void draw();

private:
    void updateWorldMatrix();

private:
    QMatrix4x4 _cameraMat;
    QRect _viewport;
    GLScene _scene;                     // Simple scene: a list of drawable objects
    std::unique_ptr<GLPointCloud> _selectionPC;
    std::unique_ptr<GLAligner> _aligner;
    GLSLBackgroundShader* _background;  // Keep background drawing outside the scene
    std::vector<QVector3D> _selection;  // Selected points
};

} // namespace
