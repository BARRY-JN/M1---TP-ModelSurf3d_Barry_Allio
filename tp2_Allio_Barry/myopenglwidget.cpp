//R. Raffin, M1 Informatique, "Surfaces 3D"
//tiré de CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "myopenglwidget.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>

#include <iostream>

#include "segment.h"
#include "PointToVbo.h"
#include "discretisation.h"
#include "courbeparametrique.h"
#include "courbebezier.h"


static const QString vertexShaderFile   = ":/basic.vsh";
static const QString fragmentShaderFile = ":/basic.fsh";


myOpenGLWidget::myOpenGLWidget(QWidget *parent) :
	QOpenGLWidget(parent)
{
	qDebug() << "init myOpenGLWidget" ;

	QSurfaceFormat sf;
	sf.setDepthBufferSize(24);
	sf.setSamples(16);  // nb de sample par pixels : suréchantillonnage por l'antialiasing, en décalant à chaque fois le sommet
						// cf https://www.khronos.org/opengl/wiki/Multisampling et https://stackoverflow.com/a/14474260
	setFormat(sf);

	setEnabled(true);  // événements clavier et souris
	setFocusPolicy(Qt::StrongFocus); // accepte focus
	setFocus();                      // donne le focus

	m_timer = new QTimer(this);
	m_timer->setInterval(50);  // msec
	connect (m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

myOpenGLWidget::~myOpenGLWidget()
{
	qDebug() << "destroy GLArea";

	delete m_timer;

	// Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
	// dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
	makeCurrent();
	tearGLObjects();
	doneCurrent();
}


void myOpenGLWidget::initializeGL()
{
	qDebug() << __FUNCTION__ ;
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);

	makeGLObjects();

	//shaders
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile);  // compile
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile);

	if (! m_program->link()) {  // édition de lien des shaders dans le shader program
		qWarning("Failed to compile and link shader program:");
		qWarning() << m_program->log();
	}
}

void myOpenGLWidget::doProjection()
{
	//m_mod.setToIdentity();
	//modelMatrix.ortho( -aratio, aratio, -1.0f, 1.0f, -1.0f, 1.0f );
}


void myOpenGLWidget::makeGLObjects()
{
    std::vector<Point> ListePoint = VisSeg->list_points();
    ListeSegment = VisSeg->list_segments();
    std::vector<float> colors = VisSeg->colors();
    std::vector<Point> ListePointControle = VisSeg->list_points();

    QVector<GLfloat> vertData1;
    QVector<GLfloat> vertData2;

    CourbeBezier *CB = new CourbeBezier(ListePointControle);
    CB->display_points_courbe();
    std::vector<Point> ListePointDiscr = Discretisation::discretiser_courbe(CB, 100, 1);

    for(int p=0; p<ListePointDiscr.size(); p++){
        ListePointDiscr[p].display(p);
    }

    dimVertex = 3;
    drawMode = GL_LINES;

    vertData1 = PointToVbo::convert_listPoints_to_vbo(ListePointControle, 100, 0, 0);
    vertData2 = PointToVbo::convert_listPoints_to_vbo(ListePointDiscr, 0, 100, 0);

    m_vbo1.create();
    m_vbo2.create();

}


void myOpenGLWidget::tearGLObjects()
{
	m_vbo.destroy();
}


void myOpenGLWidget::resizeGL(int w, int h)
{
	qDebug() << __FUNCTION__ << w << h;

	//C'est fait par défaut
	glViewport(0, 0, w, h);

	m_ratio = (double) w / h;
	//doProjection();
}

void myOpenGLWidget::paintGL()
{
	qDebug() << __FUNCTION__ ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_program->bind(); // active le shader program


	/// Ajout RR pour gérer les 3 matrices utiles
	/// à mettre dans doProjection() pour clarifier
	/// -----------------------------------------
		m_modelView.setToIdentity();
		m_modelView.lookAt(QVector3D(0.0f, 0.0f, 3.0f),    // Camera Position
						 QVector3D(0.0f, 0.0f, 0.0f),    // Point camera looks towards
						 QVector3D(0.0f, 1.0f, 0.0f));   // Up vector

		m_projection.setToIdentity ();
        m_projection.perspective(70.0, width() / height(), 0.1f, 100.0); //ou m_ratio

		//m_model.translate(0, 0, -3.0);

		// Rotation de la scène pour l'animation
        m_model.rotate(m_angle, 0.f, 1.f, 0.f);

		QMatrix4x4 m = m_projection * m_modelView * m_model;
	///----------------------------

	m_program->setUniformValue("matrix", m);

    // posAttr taille 3 + colAttr taille 3
    int taille = 6;
    m_program->setAttributeBuffer("posAttr",
                                  GL_FLOAT, 0 * sizeof(GLfloat), dimVertex, taille * sizeof(GLfloat));
    m_program->setAttributeBuffer("colAttr",
                                  GL_FLOAT, 3 * sizeof(GLfloat), 3, taille * sizeof(GLfloat));
	m_program->enableAttributeArray("posAttr");
	m_program->enableAttributeArray("colAttr");

    glPointSize (5.0f);
    //glDrawArrays(_drawMode, 0, _nbVertex);
    /*
    for (unsigned i=0; i<_listSegment.size(); i++)
    {
        int pointBegin;
        int pointEnd; */
        glDrawArrays(GL_LINE_STRIP, 0, nbVertex);
        glDrawArrays(GL_POINTS, 0, nbVertex);
    //}


	m_program->disableAttributeArray("posAttr");
	m_program->disableAttributeArray("colAttr");

	m_program->release();
}

void myOpenGLWidget::keyPressEvent(QKeyEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->text();

	switch(ev->key()) {
		case Qt::Key_Z :
			m_angle += 1;
			if (m_angle >= 360) m_angle -= 360;
			update();
			break;
		case Qt::Key_A :
			if (m_timer->isActive())
				m_timer->stop();
			else m_timer->start();
			break;
		case Qt::Key_R :
			break;
	}
}

void myOpenGLWidget::keyReleaseEvent(QKeyEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->text();
}

void myOpenGLWidget::mousePressEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void myOpenGLWidget::mouseReleaseEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void myOpenGLWidget::mouseMoveEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y();
}

void myOpenGLWidget::onTimeout()
{
	qDebug() << __FUNCTION__ ;

	update();
}





