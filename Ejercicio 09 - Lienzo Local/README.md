# 🎨 Ejercicio 09 - Lienzo Local con Base de Datos

## 📌 Descripción

Aplicación desarrollada en **C++ con Qt** que implementa un sistema de dibujo interactivo con persistencia de coordenadas en base de datos SQLite.

El proyecto combina programación orientada a objetos, manejo de eventos gráficos, almacenamiento persistente y autenticación de usuarios mediante una arquitectura modular y escalable.

---

## 🚀 Funcionalidades principales

### 🔐 Login con Qt Designer

* Interfaz construida con **Qt Designer**
* Validación de usuarios almacenados en:

  * **SQLite**
* Verificación de credenciales desde base de datos
* Mensajes de error amigables
* Separación entre interfaz y lógica

---

### 🖌️ Sistema de dibujo

* Clase `Pintura` derivada de `QWidget`
* Dibujo a mano alzada utilizando:

  * Mouse
  * Eventos de movimiento
* Actualización dinámica del lienzo

---

### 🎚️ Control del pincel

* Ajuste del grosor mediante:

  * Rueda del mouse
* Cambio de color utilizando teclado:

  * `R` → Rojo
  * `G` → Verde
  * `B` → Azul

---

### 🧹 Limpieza del lienzo

* Tecla `Escape`:

  * Borra completamente el dibujo actual

---

### ↩️ Deshacer acciones

* Soporte de:

  * `Ctrl + Z`
* Historial limitado a:

  * Últimas 10 acciones
* Reconstrucción dinámica del dibujo tras deshacer

---

### 💾 Persistencia en base de datos

* Almacenamiento de coordenadas del dibujo en:

  * **SQLite**
* Persistencia de:

  * Posición X
  * Posición Y
  * Color
  * Grosor
  * Orden del trazo

Esto permite:

* Reconstruir el dibujo completo
* Mantener información entre ejecuciones

---

## 🗄️ Base de datos

### Motor utilizado

* SQLite

---

## 📜 Logging

Registro de eventos en archivo de texto:

### Eventos registrados

* Accesos exitosos
* Intentos fallidos
* Apertura de aplicación
* Eventos importantes

### Seguridad

* ❌ No se almacenan contraseñas en logs

---

## 🎨 Interfaz

### Características visuales

* Diseño realizado con Qt Designer
* Lienzo interactivo
* Cambios visuales en tiempo real
* Interfaz simple y clara

---

## 🛠️ Tecnologías utilizadas

* C++
* Qt Widgets
* Qt Designer
* GPT Codex

---

## 📂 Estructura del proyecto

<img width="220" height="282" alt="image" src="https://github.com/user-attachments/assets/50bac42a-d9f3-4165-b3ca-28ff5c2abe11" />

---

## ⚡ Ejecución

1. Abrir el proyecto en Qt Creator
2. Compilar y ejecutar

---

## 🎯 Objetivo académico

Aplicar conceptos de:

* Interfaces gráficas
* Persistencia de datos
* Programación orientada a objetos
* Manejo de eventos
* Bases de datos SQLite
* Arquitectura modular en Qt

---

## ✨ Autor

**Lucas Guzman**
Ingeniería en Informática - UBP
