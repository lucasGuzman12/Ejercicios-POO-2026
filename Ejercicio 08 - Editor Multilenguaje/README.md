# 🧠 Ejercicio 08 - Editor Multilenguaje

## 📌 Descripción

Aplicación desarrollada en **C++ con Qt** que implementa un editor de código multilenguaje con validación de sintaxis, arquitectura basada en polimorfismo y manejo avanzado de eventos.

El sistema combina autenticación de usuario, edición de código, validación dinámica y exportación visual en una interfaz moderna y completamente funcional offline.

---

## 🚀 Funcionalidades principales

### 🔐 Login

* Sistema de autenticación inicial
* Usuario por defecto:

  * **Usuario:** `admin`
  * **Contraseña:** `1234`
* Bloqueo temporal tras **3 intentos fallidos**
* Validación de credenciales con mensajes amigables

---

### 💻 Editor multilenguaje

El editor permite trabajar con distintos lenguajes de programación:

* C++
* Python
* Java

Características:

* Selector de lenguaje
* Área de edición dinámica
* Interfaz moderna y organizada
* Validación automática por línea

---

### ✅ Validación de sintaxis

El sistema implementa validación básica de sintaxis utilizando una jerarquía de clases polimórficas.

#### 🧩 Clase base abstracta

```cpp
class ValidadorSintaxis {
public:
    virtual bool validarLinea() = 0;
};
```

#### 🪟 Clases derivadas

* `ValidadorCpp`
* `ValidadorPython`
* `ValidadorJava`

---

### 🚨 Detección de errores

* Validación ejecutada al abandonar la línea editada
* Resaltado de líneas inválidas en rojo
* Mensajes de diagnóstico amigables en pantalla
* Prevención de errores comunes de sintaxis

---

### 🧱 Arquitectura orientada a objetos

#### 🧩 Clase base abstracta

```cpp
class Pantalla {
public:
    virtual void inicializarUI() = 0;
    virtual void cargarDatos() = 0;
    ...
};
```

#### 🪟 Clases derivadas

* `Login`
* `EditorPrincipal`
* `ModoBloqueado`

---

### 🔄 Polimorfismo

La aplicación trabaja utilizando referencias y punteros a la clase base.

Esto permite:

* Reutilización de código
* Escalabilidad
* Arquitectura modular
* Separación clara de responsabilidades

---

### 📜 Logging

Registro automático de eventos importantes:

* Inicio de aplicación
* Intentos de login
* Errores de validación
* Exportaciones
* Apertura y cierre de ventanas

---

### ⚙️ Configuración externa

Lectura de configuración desde archivo:

* Usuario inicial
* Tiempo de bloqueo
* Lenguaje por defecto
* Ruta de exportación

Permite modificar parámetros sin recompilar.

---

### 📴 Funcionamiento offline

* Aplicación totalmente funcional sin internet
* No depende de servicios externos
* Todas las funcionalidades trabajan localmente

---

### 🖼️ Exportación a JPG

El editor permite exportar todo el código escrito a una única imagen JPG.

Características:

* Respeta saltos de línea
* Mantiene formato legible
* Exportación completa del contenido

---

### 🧑‍💼 Panel lateral estilo LinkedIn

La ventana principal incluye un panel lateral con información profesional.

* Foto de perfil
* Nombre
* Carrera
* Acerca de

---

### 🛠️ Tecnologías utilizadas

* C++
* Qt
* GPT Codex

---

## 📂 Estructura del proyecto

<img width="292" height="433" alt="image" src="https://github.com/user-attachments/assets/ce4eec9c-a311-43f4-ac50-dc502c0d457d" />

---

## ⚡ Ejecución

1. Configurar parámetros en el archivo `config.txt`

2. Abrir el proyecto en Qt Creator

3. Compilar y ejecutar

---

## 📌 Notas

* Aplicación desarrollada utilizando conceptos vistos en clase
* Uso obligatorio de:
  * Signals & Slots
  * Eventos personalizados
  * Polimorfismo
  * Clases abstractas
  * Uso intenso de IA con GPT Codex
* Arquitectura modular y escalable

---

## ✨ Autor

**Lucas Guzman**  
Ingeniería en Informática - UBP
