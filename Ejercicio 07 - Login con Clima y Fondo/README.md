# 🌤️ Ejercicio 07 - Login con clima y fondo de pantalla

## 📌 Descripción

Aplicación desarrollada en **C++ con Qt** que implementa un sistema de login interactivo con integración de datos en tiempo real, descarga de recursos externos y manejo robusto de red.

El sistema combina autenticación de usuario, consumo de API externa de clima, carga dinámica de imágenes y arquitectura orientada a objetos con buenas prácticas.

---

## 🚀 Funcionalidades principales

### 🔐 Login

* Interfaz creada con **Qt Designer**
* Usuario por defecto:

  * **Usuario:** `admin`
  * **Contraseña:** `1234`
* Bloqueo temporal tras **3 intentos fallidos**
* Validación de credenciales con mensajes amigables

---

### 🌦️ Clima en tiempo real

* Consumo de API externa:

  * https://api.weatherapi.com/v1/current.json
* Parámetros utilizados:

  * Ciudad (configurable)
  * Unidades métricas
* Autenticación mediante **API Key (query o header)**
* Muestra en pantalla:

  * 🌡️ Temperatura actual
  * 🕒 Hora local

---

### 🖼️ Fondo dinámico

* Descarga de imagen desde URL pública
* Sistema de **caché local**
* La ventana principal:

  * Se abre solo cuando la imagen termina de descargarse
  * Se muestra en **pantalla completa**
* Imagen ajustada:

  * Mantiene relación de aspecto
  * Sin deformación

---

### 🌐 Red y conectividad

* Uso obligatorio de:

  * `QNetworkAccessManager`
  * `signals/slots`
* Soporte para:

  * Proxy
  * Manejo de errores de red
* Validación de datos recibidos

---

### 📴 Modo offline

* Detección automática de conexión
* En caso de fallo:

  * Uso de **datos simulados**
  * UI funcional sin conexión

---

### 📜 Logging

* Registro de eventos en archivo:

  * Inicio de app
  * Intentos de login
  * Errores de red
  * Descargas

---

### 🧠 Manejo de errores

* Validación de respuestas de la API
* Mensajes claros en la UI
* Prevención de fallos por datos inválidos

---

## 👤 Ventana principal (Perfil estilo LinkedIn)

Una vez autenticado el usuario, se muestra una interfaz profesional con información personal:

### 🧑‍💻 Perfil

* Foto de perfil
* Nombre
* Carrera
* Info breve en **Acerca de**

---

## 🛠️ Tecnologías utilizadas

* C++
* Qt (Qt Designer, Signals & Slots)
* QNetworkAccessManager
* JSON parsing
* APIs REST
* Manejo de archivos
* Arquitectura orientada a objetos

---

## 📂 Estructura del proyecto

<img width="252" height="479" alt="image" src="https://github.com/user-attachments/assets/c3793e86-97b9-4754-bb15-d92c8349ffe1" />

---

## ⚡ Ejecución

Compilar y ejecutar el proyecto desde Qt Creator

---

## 📌 Notas

* No se utilizan SDKs oficiales → consumo directo de la API
* Implementación centrada en conceptos vistos en clase
* Código estructurado y escalable

---

## 🎯 Objetivo académico

Aplicar conceptos de:

* Redes y consumo de APIs
* Programación orientada a objetos
* Manejo de interfaces gráficas
* Manejo de errores y robustez
* Buenas prácticas de desarrollo

---

## ✨ Autor

**Lucas Guzman**
Ingeniería en Informática - UBP
