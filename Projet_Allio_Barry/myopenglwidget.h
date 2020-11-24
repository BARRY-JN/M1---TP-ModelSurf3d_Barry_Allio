#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include "visualisationsegments.h"
#include "carreauxbezier.h"


class myOpenGLWidget : public QOpenGLWidget,
			   protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit myOpenGLWidget(QWidget *parent = nullptr);
	~myOpenGLWidget();

public slots:
    void on_set_u(double _U);
    void on_set_nbU(int _NbU);
    void on_set_v(double _V);
    void on_set_nbV(int _NbV);

    void on_pt_ctrl(bool value);
    void on_triangulation(bool value);
    void on_vertices(bool value);
    void on_edges(bool value);
    void on_carreaux(bool value);
    void on_forme(bool value);

signals:  // On ne les implémente pas, elles seront générées par MOC ;
		  // les paramètres seront passés aux slots connectés.
    void u_changed(double newU);
    void nbU_changed(int newNbU);
    void v_changed(double newV);
    void nbV_changed(int newNbV);

    void flag_pt_ctrl_changed(bool value);
    void flag_triangulation_changed(bool value);
    void flag_vertices_changed(bool value);
    void flag_edges_changed(bool value);
    void flag_carreaux_changed(bool value);
    void flag_forme_changed(bool value);

protected slots:
	void onTimeout();

protected:
	void initializeGL() override;
	void doProjection();
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent *ev) override;
	void keyReleaseEvent(QKeyEvent *ev) override;
	void mousePressEvent(QMouseEvent *ev) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;
    QVector<GLfloat> vertData1;
    QVector<GLfloat> vertData2;
    QVector<GLfloat> vertData3;

private:
	double m_angle = 0;
	QTimer *m_timer = nullptr;
	double m_ratio = 1;

	//RR matrices utiles
	QMatrix4x4 m_modelView;
	QMatrix4x4 m_projection;
	QMatrix4x4 m_model;

	QOpenGLShaderProgram *m_program;

    QOpenGLBuffer m_vbo1;
    QOpenGLBuffer m_vbo2;
    QOpenGLBuffer m_vbo3;

	void makeGLObjects();
	void tearGLObjects();

    VisualisationSegments *VisSeg = new VisualisationSegments();
    int nbVertex;
    int dimVertex;
    int drawMode = GL_POINTS;
    std::vector<Segment> ListeSegment;

    int n=4;
    int m=4;
    int nbPt=0;

    std::vector<Point> ListePointControle;
    CarreauxBezier *CarBez;
    float U = 0, V = 0, NbU = 32, NbV = 24;
    void update_point();
    void Discretisation_Carreaux_Beziers(float U, float V);
    void paint_vbo(int idVbo, QMatrix4x4 *m);
    void switch_vbo(int idVbo);

    void update_discret_carBez();
    void carreaux_tri();
    void carreaux_lines();

    bool PtCtrl=false;
    bool Triangle=true;
    bool Vertices=false;
    bool Edges=true;
    bool Carreaux=true;
    bool Forme=false;
};


#endif // MYOPENGLWIDGET_H
