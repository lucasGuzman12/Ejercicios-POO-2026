#include "gamewidget.h"

#include "cactus.h"
#include "pajaro.h"
#include "trex.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QRandomGenerator>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent),
      // El T-Rex, los timers y el boton tienen como padre a GameWidget.
      // Asi Qt se encarga de liberar la memoria automaticamente al cerrar.
      m_trex(new TRex(this)),
      m_mainTimer(new QTimer(this)),
      m_birdSpawner(new QTimer(this)),
      m_restartButton(new QPushButton("Reiniciar", this)),
      m_gameOver(false),
      m_speed(8),
      m_ticks(0),
      m_score(0)
{
    setupUi();

    // Conexion clasica pedida por la consigna:
    // cada vez que vence m_mainTimer, se ejecuta gameLoop().
    connect(m_mainTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));

    // Este timer no mueve objetos: solo crea un pajaro nuevo cada 5 segundos.
    connect(m_birdSpawner, SIGNAL(timeout()), this, SLOT(spawnBird()));

    // El boton de reinicio aparece al perder y llama a restartGame().
    connect(m_restartButton, SIGNAL(clicked()), this, SLOT(restartGame()));

    // Deja el juego listo apenas se abre la ventana.
    restartGame();
}

GameWidget::~GameWidget()
{
}

void GameWidget::setupUi()
{
    // Configuracion basica de la ventana principal del juego.
    setWindowTitle("T-Rex Extremo");
    setFixedSize(900, 420);

    // Permite que este QWidget reciba eventos de teclado.
    setFocusPolicy(Qt::StrongFocus);

    // Se crean tres cactus y se guardan en una lista.
    // Luego se van reciclando: cuando salen de pantalla, vuelven a aparecer a la derecha.
    for (int i = 0; i < 3; ++i) {
        Cactus *cactus = new Cactus(this);
        m_cactus.append(cactus);
    }

    // Boton que se muestra unicamente cuando termina la partida.
    m_restartButton->setFixedSize(110, 34);
    m_restartButton->move(width() / 2 - m_restartButton->width() / 2, 245);
    m_restartButton->hide();

    // En lugar de depender de un archivo externo, se genera una imagen de Game Over
    // dibujando sobre un QPixmap con QPainter.
    m_gameOverImage = QPixmap(330, 92);
    m_gameOverImage.fill(Qt::transparent);
    QPainter painter(&m_gameOverImage);

    // Antialiasing suaviza bordes de rectangulos y texto.
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(245, 245, 245));

    // Fondo claro del cartel.
    painter.drawRoundedRect(0, 0, 330, 92, 8, 8);

    // Borde del cartel.
    painter.setPen(QPen(QColor(45, 45, 45), 3));
    painter.drawRoundedRect(2, 2, 326, 88, 8, 8);

    // Texto principal.
    QFont titleFont = painter.font();
    titleFont.setPointSize(25);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(QRect(0, 8, 330, 42), Qt::AlignCenter, "GAME OVER");

    // Texto de ayuda para reiniciar.
    QFont smallFont = painter.font();
    smallFont.setPointSize(10);
    smallFont.setBold(false);
    painter.setFont(smallFont);
    painter.drawText(QRect(0, 54, 330, 28), Qt::AlignCenter, "Espacio o boton para reiniciar");
}

int GameWidget::groundY() const
{
    // El suelo queda un poco por encima del borde inferior de la ventana.
    return height() - 74;
}

void GameWidget::restartGame()
{
    // Reinicio del estado numerico de la partida.
    m_gameOver = false;
    m_speed = 8;
    m_ticks = 0;
    m_score = 0;

    // El T-Rex vuelve a su posicion inicial.
    m_trex->reset(groundY());

    // Los cactus se distribuyen inicialmente fuera de la pantalla, hacia la derecha.
    resetCactus(m_cactus[0], width() + 260);
    resetCactus(m_cactus[1], width() + 560);
    resetCactus(m_cactus[2], width() + 900);

    // Si quedaron pajaros de una partida anterior, se eliminan.
    qDeleteAll(m_birds);
    m_birds.clear();

    // Se oculta el boton y se reactivan los timers del juego.
    m_restartButton->hide();

    // 28 ms da aproximadamente 35 actualizaciones por segundo.
    m_mainTimer->start(28);

    // Cada 5000 ms aparece un pajaro nuevo.
    m_birdSpawner->start(5000);

    // Se recupera el foco para que las teclas funcionen despues de tocar el boton.
    setFocus();
    update();
}

void GameWidget::gameLoop()
{
    // Si el juego termino, no se debe seguir actualizando la escena.
    if (m_gameOver) {
        return;
    }

    // m_ticks mide el tiempo de juego en cantidad de ejecuciones del timer.
    ++m_ticks;

    // Puntaje simple basado en supervivencia.
    m_score = m_ticks / 3;

    // La velocidad sube gradualmente con el tiempo.
    updateSpeed();

    // Actualiza salto/gravedad del T-Rex.
    m_trex->updatePhysics(groundY());

    // Se usa para reubicar cactus siempre mas adelante que el cactus mas lejano.
    int farthestX = width();
    for (int i = 0; i < m_cactus.size(); ++i) {
        Cactus *cactus = m_cactus[i];

        // Los cactus se mueven a la izquierda con el timer principal.
        cactus->move(cactus->x() - m_speed, cactus->y());
        farthestX = qMax(farthestX, cactus->x());

        // Cuando un cactus sale por completo de la pantalla, se recicla a la derecha.
        if (cactus->x() + cactus->width() < 0) {
            resetCactus(cactus, farthestX + 280 + QRandomGenerator::global()->bounded(260));
        }

        // Si el rectangulo de colision del T-Rex toca al del cactus, se pierde.
        if (m_trex->collisionRect().intersects(cactus->collisionRect())) {
            endGame();
            return;
        }
    }

    // Los pajaros se mueven solos con su propio timer, pero aca se actualiza su velocidad
    // y se revisa si chocan contra el T-Rex.
    for (int i = 0; i < m_birds.size(); ++i) {
        m_birds[i]->setSpeed(m_speed + 2);
        if (m_trex->collisionRect().intersects(m_birds[i]->collisionRect())) {
            endGame();
            return;
        }
    }

    // Pide a Qt que vuelva a dibujar la ventana.
    update();
}

void GameWidget::spawnBird()
{
    // No se crean nuevos pajaros si la partida ya termino.
    if (m_gameOver) {
        return;
    }

    // Cada Pajaro se crea como QWidget hijo de GameWidget.
    Pajaro *bird = new Pajaro(this);

    // Alturas posibles: alto, medio y bajo. Esto obliga a saltar o agacharse.
    int heightOptions[] = { groundY() - 150, groundY() - 105, groundY() - 62 };
    int y = heightOptions[QRandomGenerator::global()->bounded(3)];

    // Aparece apenas fuera del borde derecho.
    bird->move(width() + 20, y);
    bird->show();

    // Arranca su timer propio. Los pajaros van un poco mas rapido que los cactus.
    bird->start(m_speed + 2);

    // Cuando el pajaro avisa que salio de pantalla, GameWidget lo elimina.
    connect(bird, SIGNAL(leftScreen(Pajaro*)), this, SLOT(removeBird(Pajaro*)));
    m_birds.append(bird);

    // Evento sorpresa opcional: a veces programa otro pajaro poco despues.
    // QTimer::singleShot ejecuta el slot una sola vez.
    if (QRandomGenerator::global()->bounded(4) == 0) {
        QTimer::singleShot(1200, this, SLOT(spawnBird()));
    }
}

void GameWidget::removeBird(Pajaro *pajaro)
{
    // Se quita de la lista para que ya no se revise colision contra el.
    m_birds.removeAll(pajaro);

    // deleteLater() borra el widget de forma segura cuando Qt vuelva al loop de eventos.
    pajaro->deleteLater();
}

void GameWidget::resetCactus(Cactus *cactus, int minimumX)
{
    // Cambia su forma para dar variedad visual.
    cactus->randomizeShape();

    // Se apoya el cactus sobre el suelo.
    cactus->move(minimumX, groundY() - cactus->height());
    cactus->show();
}

void GameWidget::updateSpeed()
{
    // Cada 420 ticks aumenta 1 punto la velocidad.
    // Como el timer corre cada 28 ms, esto ocurre aproximadamente cada 12 segundos.
    m_speed = 8 + (m_ticks / 420);
}

void GameWidget::endGame()
{
    // Marca la partida como terminada.
    m_gameOver = true;

    // Se detienen los timers globales del juego.
    m_mainTimer->stop();
    m_birdSpawner->stop();

    // Los pajaros tienen timers propios. En vez de borrarlos inmediatamente,
    // se les baja la velocidad a 0 para que queden quietos en la escena final.
    for (int i = 0; i < m_birds.size(); ++i) {
        m_birds[i]->setSpeed(0);
    }

    // Muestra el boton de reinicio y repinta para mostrar el cartel de Game Over.
    m_restartButton->show();
    update();
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    // Si ya se perdio, espacio o enter reinician la partida.
    if (m_gameOver) {
        if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Return) {
            restartGame();
        }
        QWidget::keyPressEvent(event);
        return;
    }

    // Controles pedidos por la consigna.
    // Se permite saltar con espacio y tambien con flecha arriba.
    switch (event->key()) {
    case Qt::Key_Space:
    case Qt::Key_Up:
        // Saltar.
        m_trex->jump();
        break;
    case Qt::Key_Down:
        // Agacharse mientras la tecla este presionada.
        m_trex->crouch(true);
        break;
    case Qt::Key_Right:
        // Adelantarse.
        m_trex->advance();
        break;
    case Qt::Key_Left:
        // Frenarse o retroceder.
        m_trex->brake();
        break;
    default:
        // Cualquier otra tecla se deja al comportamiento normal de QWidget.
        QWidget::keyPressEvent(event);
        break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event)
{
    // Al soltar flecha abajo, el T-Rex vuelve a estar parado.
    if (event->key() == Qt::Key_Down) {
        m_trex->crouch(false);
    } else {
        QWidget::keyReleaseEvent(event);
    }
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // QPainter permite dibujar directamente sobre el QWidget.
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fondo del juego.
    painter.fillRect(rect(), QColor(250, 250, 247));

    // Linea del suelo.
    painter.setPen(QPen(QColor(92, 92, 92), 3));
    painter.drawLine(0, groundY() + 1, width(), groundY() + 1);

    // Puntaje e instrucciones.
    painter.setPen(QColor(65, 65, 65));
    QFont scoreFont = painter.font();
    scoreFont.setPointSize(12);
    scoreFont.setBold(true);
    painter.setFont(scoreFont);
    painter.drawText(QRect(0, 18, width() - 24, 26), Qt::AlignRight, QString("Puntos: %1").arg(m_score));
    painter.drawText(22, 36, "Espacio: saltar  |  Abajo: agacharse  |  Derecha/Izquierda: moverse");

    // Si se perdio, se dibuja el cartel generado en setupUi().
    if (m_gameOver) {
        painter.drawPixmap(width() / 2 - m_gameOverImage.width() / 2, 132, m_gameOverImage);
    }
}
