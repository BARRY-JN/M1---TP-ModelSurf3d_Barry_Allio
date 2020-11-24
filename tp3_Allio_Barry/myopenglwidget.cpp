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

    connect (this, SIGNAL(u_changed(double)), this, SLOT(on_set_u(double)));
    connect (this, SIGNAL(nbU_changed(int)), this, SLOT(on_set_nbU(int)));

    connect (this, SIGNAL(v_changed(double)), this, SLOT(on_set_v(double)));
    connect (this, SIGNAL(nbV_changed(int)), this, SLOT(on_set_nbV(int)));
}

void myOpenGLWidget::on_set_nbU(int _NbU)
{
    NbU = _NbU;
    Discretisation_Carreaux_Beziers(NbU, NbV);
}

void myOpenGLWidget::on_set_nbV(int _NbV)
{
    NbV = _NbV;

    Discretisation_Carreaux_Beziers(NbU, NbV);
}

void myOpenGLWidget::on_set_u(double _U)
{
    U = _U;
    update_point();
}

void myOpenGLWidget::on_set_v(double _V)
{
    V = _V;
    update_point();
}

void myOpenGLWidget::update_point()
{
    if (U>=0 && U<=1 && V>=0 && V<=1)
    {
        vertData3.clear();
        vector<Point> tmp;
        tmp.push_back(CarBez->eval(U, V));
        Point p;
        p.set(-1, 1, 1);
        tmp.push_back(p);
        vertData3 = PointToVbo::convert_listPoints_to_vbo(tmp, 0, 0, 100);
        update();
    }
}

myOpenGLWidget::~myOpenGLWidget()
{
	qDebug() << "destroy GLArea";

	delete m_timer;
    delete CarBez;

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
    //ListeSegment = VisSeg->list_segments();
    std::vector<float> colors = VisSeg->colors();

    dimVertex = 3;
    drawMode = GL_LINES;


    Discretisation_Carreaux_Beziers(NbU, NbV);

    vertData1 = PointToVbo::convert_listPoints_to_vbo(ListePoint, 100, 0, 0);

    m_vbo1.create();
    m_vbo2.create();
    m_vbo3.create();

}

vector<vector<Point>> tab_to_bezier(std::vector<Point> listPoint, int n, int m, int debut)
{
    vector<vector<Point>> tab(n, vector<Point>(m));
    int k=debut;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            tab[i][j] = listPoint[k];
            k++;
        }
    }
    return tab;
}

void myOpenGLWidget::Discretisation_Carreaux_Beziers(float U, float V)
{
    vector<vector<Point>> tabCarBez = tab_to_bezier(ListePointControle, 4, 4, 0);

    CarBez = new CarreauxBezier(tabCarBez, 4, 4);
    CarBez->display_points();

    std::vector<Point> listPointDiscr1 = Discretisation::discretiser_carreaux_bezier(CarBez, U, V, 0);
    for (int p=0; p<listPointDiscr1.size(); p++)
        listPointDiscr1[p].display(p);
    int SomDiscr = listPointDiscr1.size();
    tabCarBez = tab_to_bezier(ListePointControle, 4, 4, (ListePointControle.size()/2));
    delete CarBez;

    CarBez = new CarreauxBezier(tabCarBez, 4, 4);
    CarBez->display_points();

    vector<Point> listPointDiscr2 = Discretisation::discretiser_carreaux_bezier(CarBez, U, V, 0);
    for (int p=0; p<listPointDiscr2.size(); p++)
        listPointDiscr2[p].display(p);
    SomDiscr += listPointDiscr2.size();

    vertData2.clear();
    vertData2 = PointToVbo::convert_listPoints_to_vbo(listPointDiscr1,0,100,0);
    vertData2 += PointToVbo::convert_listPoints_to_vbo(listPointDiscr2,0,50,50);
    update();
}


void myOpenGLWidget::tearGLObjects()
{
    m_vbo1.destroy();
    m_vbo2.destroy();
    m_vbo3.destroy();
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

    //glDrawArrays(_drawMode, 0, _nbVertex);
    /*
    for (unsigned i=0; i<_listSegment.size(); i++)
    {
        int pointBegin;
        int pointEnd; */
        //glDrawArrays(GL_LINE_STRIP, 0, nbVertex);
        //glDrawArrays(GL_POINTS, 0, nbVertex);
    //}

    paint_vbo(1, &m);
    paint_vbo(2, &m);
    paint_vbo(3, &m);


	m_program->disableAttributeArray("posAttr");
	m_program->disableAttributeArray("colAttr");

	m_program->release();
}

void myOpenGLWidget::switch_vbo(int idVbo)
{
    if (idVbo==1){
        m_vbo1.bind();
        m_vbo1.allocate(vertData1.constData(), vertData1.count() * sizeof(GLfloat));
    }
    else if (idVbo==2){
        m_vbo2.bind();
        m_vbo2.allocate(vertData2.constData(), vertData2.count() * sizeof(GLfloat));
    }
    else if (idVbo>=3){
        m_vbo3.bind();
        m_vbo3.allocate(vertData3.constData(), vertData3.count() * sizeof(GLfloat));
    }
}

void myOpenGLWidget::paint_vbo(int idVbo, QMatrix4x4 *mat)
{
    switch_vbo(idVbo);

    m_program->setUniformValue("matrix", *mat);

    int taille = 6;
    m_program->setAttributeBuffer("posAttr",GL_FLOAT, 0 * sizeof(GLfloat), dimVertex, taille * sizeof(GLfloat));
    m_program->setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, taille * sizeof(GLfloat));
    m_program->enableAttributeArray("posAttr");
    m_program->enableAttributeArray("colAttr");

    glPointSize (5.0f);

    if (idVbo==1)
    {
        glDrawArrays(GL_POINTS, 0, nbPt);
        for (int i=0; i<n*m; i+=n){
            glDrawArrays(GL_LINE_STRIP, i, n);
        }
        for (int i=n*m; i<(n*m)*2; i+=n){
            glDrawArrays(GL_LINE_STRIP, i, n);
        }

    }else if (idVbo==2)
    {
        for (int i=0; i<NbU*NbV; i+=NbV){
            glDrawArrays(GL_LINE_STRIP, i, NbV);
        }

        for (int i=NbU*NbV; i<(NbU*NbV)*2; i+=NbV){
            glDrawArrays(GL_LINE_STRIP, i, NbV);
        }
    }else if (idVbo>=3) {
        glDrawArrays(GL_POINTS, 0, 2);
        glDrawArrays(GL_LINE_STRIP, 0, 2);
    }


    m_program->disableAttributeArray("posAttr");
    m_program->disableAttributeArray("colAttr");

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





