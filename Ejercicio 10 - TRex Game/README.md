# 🦖 Ejercicio 10 - T-Rex Extremo

## 📌 Descripción

Aplicación desarrollada en **C++ con Qt** inspirada en el clásico juego del **T-Rex de Google Chrome**, incorporando nuevas mecánicas, obstáculos dinámicos y mayor dificultad progresiva.

El jugador controla un dinosaurio que debe esquivar cactus y pájaros mientras la velocidad del juego aumenta con el paso del tiempo.

---

## 🎮 Funcionalidades principales

### 🦖 Personaje principal

* Clase `TRex` creada de forma modular
* Hereda de:

  * `QWidget`
* Representa al dinosaurio controlado por el jugador
* Gestiona su posición, movimiento y estado actual

---

### 🌵 Obstáculos: cactus

* Obstáculos que se desplazan horizontalmente hacia la izquierda
* Controlados mediante un `QTimer` principal
* Participan en la detección de colisiones
* Su velocidad aumenta progresivamente con el tiempo

---

### 🐦 Obstáculos: pájaros

* Clase `Pajaro` creada de forma modular
* Hereda de:

  * `QWidget`
* Cada instancia de `Pajaro` posee su propio `QTimer`
* Cada `QTimer` mueve al pájaro horizontalmente hacia la izquierda
* Cada 5 segundos aparece un nuevo pájaro
* Los pájaros pueden aparecer en distintas alturas aleatorias

---

## ⏱️ Uso de QTimer

### Timer principal

El juego utiliza un `QTimer` principal para:

* Mover cactus
* Actualizar el estado general del juego
* Detectar colisiones
* Aumentar dificultad
* Refrescar la escena

---

### Timers independientes de pájaros

Cada pájaro tiene su propio temporizador independiente:

```cpp id="b7k2q1"
connect(timer, SIGNAL(timeout()), this, SLOT(mover()));
```

Esto permite que cada pájaro tenga comportamiento propio y pueda desplazarse de forma independiente dentro del juego.

---

### Eventos únicos

Se puede utilizar `QTimer::singleShot()` para programar eventos especiales:

```cpp id="m9p4x8"
QTimer::singleShot(3000, this, SLOT(aparecerObstaculoSorpresa()));
```

Ejemplos de uso:

* Aparición de obstáculos sorpresa
* Cambios temporales de velocidad
* Eventos especiales durante la partida

---

## 🎮 Controles del jugador

El dinosaurio puede realizar distintas acciones mediante el teclado:

| Acción      | Tecla              |
| ----------- | ------------------ |
| Saltar      | `Espacio`          |
| Agacharse   | `Flecha Abajo`     |
| Adelantarse | `Flecha Derecha`   |
| Frenarse    | `Flecha Izquierda` |

---

## 💥 Colisiones

El juego implementa detección de colisiones entre:

* Dinosaurio y cactus
* Dinosaurio y pájaros

Si el dinosaurio colisiona con un obstáculo:

* La partida termina
* Se detienen los temporizadores necesarios
* Se muestra una imagen de **Game Over**
* Se permite reiniciar el juego

---

## 🔁 Reinicio del juego

Luego de perder, el jugador puede reiniciar la partida.

Al reiniciar:

* Se restaura la posición del dinosaurio
* Se eliminan o reinician obstáculos
* Se reinician velocidades
* Se vuelve a iniciar el `QTimer` principal
* Se oculta la imagen de Game Over

---

## 📈 Dificultad progresiva

La velocidad de los cactus y pájaros aumenta a medida que pasa el tiempo.

Esto permite que el juego sea cada vez más desafiante, manteniendo una experiencia dinámica similar al juego original, pero con una dificultad más extrema.

---

## 🧱 Arquitectura

### Clase `TRex`

```cpp id="a2x6n4"
class TRex : public QWidget
{
    Q_OBJECT

public:
    explicit TRex(QWidget *parent = nullptr);

    void saltar();
    void agacharse();
    void adelantarse();
    void frenarse();

protected:
    void paintEvent(QPaintEvent *event) override;
};
```

---

### Clase `Pajaro`

```cpp id="f3t9c5"
class Pajaro : public QWidget
{
    Q_OBJECT

public:
    explicit Pajaro(QWidget *parent = nullptr);
    void iniciarMovimiento();

private slots:
    void mover();

private:
    QTimer *timer;
};
```

---

### Clase principal del juego

```cpp id="v8r1s7"
class Juego : public QWidget
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = nullptr);

private slots:
    void actualizarJuego();
    void crearPajaro();
    void reiniciarJuego();

private:
    QTimer *timerPrincipal;
};
```

---

## 📦 Organización modular

El proyecto se organiza en clases separadas para facilitar su mantenimiento y crecimiento.

### Componentes principales

* `TRex`
* `Pajaro`
* `Cactus`
* `Juego`
* `GameOver`

---

## 📂 Estructura del proyecto

```id="q6m2w9"
/proyecto
│
├── main.cpp
├── Juego.h / Juego.cpp
├── TRex.h / TRex.cpp
├── Pajaro.h / Pajaro.cpp
├── Cactus.h / Cactus.cpp
│
├── recursos/
│   ├── trex.png
│   ├── pajaro.png
│   ├── cactus.png
│   └── game_over.png
│
└── README.md
```

---

## 🛠️ Tecnologías utilizadas

* C++
* Qt Widgets
* QWidget
* QImage
* QPainter
* QTimer
* Signals & Slots
* Eventos de teclado
* Detección de colisiones
* Programación orientada a objetos

---

## ⚡ Ejecución

1. Abrir el proyecto en Qt Creator
2. Verificar que las imágenes estén correctamente cargadas
3. Compilar el proyecto
4. Ejecutar el juego
5. Controlar el dinosaurio con el teclado

---

## 📌 Notas

* Cada pájaro posee su propio `QTimer`
* El `QTimer` principal controla la lógica general del juego
* Las conexiones se realizan utilizando `connect`
* Se prioriza una arquitectura modular
* El juego puede ampliarse fácilmente agregando nuevos obstáculos, sonidos o puntajes

---

## 🎯 Objetivo académico

Aplicar conceptos de:

* Programación orientada a objetos
* Herencia
* Modularización
* Manejo de eventos en Qt
* Uso de `QTimer`
* Signals & Slots
* Detección de colisiones
* Desarrollo de interfaces interactivas

---

## ✨ Autor

**Lucas Guzman**
Ingeniería en Informática - UBP
