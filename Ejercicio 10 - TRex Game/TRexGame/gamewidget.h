#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QList>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

// Declaraciones adelantadas: permiten usar punteros a estas clases
// sin incluir todos los headers en este archivo.
class Cactus;
class QKeyEvent;
class QPaintEvent;
class Pajaro;
class QPushButton;
class TRex;

// GameWidget representa la ventana completa del juego.
// Hereda de QWidget para cumplir la consigna de no usar QMainWindow.
class GameWidget : public QWidget
{
    Q_OBJECT

public:
    // Constructor y destructor de la pantalla del juego.
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

public slots:
    // Slot ejecutado por el QTimer principal. Mueve cactus, actualiza fisica y revisa colisiones.
    void gameLoop();

    // Slot llamado cada 5 segundos para crear un nuevo pajaro.
    void spawnBird();

    // Slot que elimina un pajaro cuando sale completamente de la pantalla.
    void removeBird(Pajaro *pajaro);

    // Reinicia todos los valores del juego despues de perder o al comenzar.
    void restartGame();

protected:
    // Recibe las teclas presionadas: espacio, abajo, derecha e izquierda.
    void keyPressEvent(QKeyEvent *event);

    // Detecta cuando se suelta la flecha abajo para que el T-Rex deje de agacharse.
    void keyReleaseEvent(QKeyEvent *event);

    // Dibuja el fondo, el suelo, el puntaje y la imagen de Game Over.
    void paintEvent(QPaintEvent *event);

private:
    // Configura el tamano de la ventana, crea cactus iniciales y prepara el cartel de Game Over.
    void setupUi();

    // Reubica un cactus a la derecha de la pantalla y le da una forma aleatoria.
    void resetCactus(Cactus *cactus, int minimumX);

    // Aumenta la velocidad progresivamente segun el tiempo transcurrido.
    void updateSpeed();

    // Detiene timers y muestra la opcion de reiniciar.
    void endGame();

    // Devuelve la posicion vertical del suelo. Los personajes se apoyan sobre esta linea.
    int groundY() const;

    // Personaje controlado por el jugador.
    TRex *m_trex;

    // Obstaculos terrestres controlados por el timer principal.
    QList<Cactus *> m_cactus;

    // Lista de pajaros activos. Cada Pajaro tiene su propio QTimer interno.
    QList<Pajaro *> m_birds;

    // Timer principal del juego: mueve cactus, actualiza fisica y detecta colisiones.
    QTimer *m_mainTimer;

    // Timer que crea un pajaro nuevo cada 5 segundos.
    QTimer *m_birdSpawner;

    // Boton que aparece cuando termina la partida.
    QPushButton *m_restartButton;

    // Imagen generada con QPainter para mostrar "GAME OVER".
    QPixmap m_gameOverImage;

    // Estado general de la partida.
    bool m_gameOver;

    // Velocidad actual de obstaculos. Sube con el tiempo.
    int m_speed;

    // Cantidad de vueltas del timer principal desde que empezo la partida.
    int m_ticks;

    // Puntaje mostrado en pantalla.
    int m_score;
};

#endif
