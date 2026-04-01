# 🖥️ Panel de Monitoreo VPS - Qt Desktop App

## 📌 Descripción

Este proyecto consiste en una aplicación de escritorio desarrollada con **Qt (C++ y qmake)** que permite monitorear el estado de un servidor VPS en tiempo real.

La aplicación consume un endpoint HTTP expuesto por una API desarrollada con **FastAPI** y desplegada mediante **Docker** en el VPS. A partir de estos datos, construye un panel visual inspirado en herramientas profesionales de monitoreo como Grafana o Zabbix.

---

## 🎯 Objetivos del proyecto

* Visualizar el estado general de un VPS (OK / Alerta / Caído)
* Mostrar métricas clave del sistema:

  * Uptime
  * Carga del sistema
  * Uso de memoria
  * Uso de disco
* Registrar el último chequeo realizado
* Mantener un historial reciente de eventos
* Permitir interacción del usuario mediante controles configurables

---

## 🌐 Endpoint utilizado

La aplicación consume el siguiente endpoint:

```
http://147.93.189.45:8000/health
```

Formato esperado de respuesta:

```json
{
  "status": "OK",
  "uptime": "3 days 04:12:55",
  "load": 0.72,
  "mem_used": 2048,
  "mem_total": 4096,
  "disk_used": 35,
  "disk_total": 80
}
```

---

## 🧱 Arquitectura del sistema

### 📍 Cliente (Qt Desktop App)

* Interfaz gráfica desarrollada con Qt Widgets
* Consumo de API mediante solicitudes HTTP
* Lógica de monitoreo separada en clases propias
* Manejo de estado e historial

### 📍 Servidor (VPS)

* API desarrollada con FastAPI
* Contenerizada con Docker
* Endpoint `/health` que devuelve métricas del sistema

---

## ⚙️ Tecnologías utilizadas

* **C++**
* **Qt (Widgets + qmake)**
* **FastAPI**
* **Docker**
* **HTTP / JSON**

---

## 🔁 Funcionalidades principales

* 🔄 **Refresco manual** mediante botón
* ⏱️ **Intervalo configurable** de chequeo automático
* 📊 **Visualización clara de métricas**
* 🚦 **Indicador de estado general**
* 📝 **Historial de eventos recientes**

---

## 🐳 Backend (API en VPS)

La API fue desarrollada con **FastAPI** y desplegada en un contenedor Docker.

Incluye:

* Endpoint `/health`
* Obtención de métricas del sistema
* Formato JSON estandarizado
* Ejecución aislada en contenedor

📁 Se incluye en el repositorio una carpeta con los archivos del servidor (Dockerfile, código de la API, etc.)

---

## 🖼️ Inspiración de diseño

El diseño del panel está inspirado en herramientas profesionales como:

* Grafana
* Zabbix
* Prometheus
* Netdata
* Datadog

Se priorizó:

* Claridad visual
* Lectura rápida de métricas
* Separación de información crítica
* Feedback inmediato del estado del sistema

---

## 🚀 Cómo ejecutar

### 🖥️ Cliente (Qt)

1. Abrir el proyecto con Qt Creator
2. Configurar el kit de compilación
3. Compilar y ejecutar

### 🌐 Servidor (opcional)

1. Navegar a la carpeta del backend
2. Construir la imagen Docker:

```bash
docker compose build
```

3. Levantar el contenedor:

```bash
docker compose up
```

---

## 📂 Estructura del proyecto

- Cliente: Todo el proyecto local.
- Servidor: Lo que corre en el VPS (La API).

---

## ✅ Cumplimiento de requisitos

✔ Aplicación Qt con qmake
✔ Consumo de endpoint real en VPS
✔ Visualización de estado y métricas
✔ Widgets interactivos correctamente utilizados
✔ Refresco manual y automático configurable
✔ Historial de eventos
✔ Clase propia para lógica de monitoreo
✔ Inspiración en herramientas profesionales
✔ Uso de Docker y FastAPI en backend

---

## 📌 Notas finales

Este proyecto simula un panel real de monitoreo de infraestructura, integrando frontend de escritorio con backend en la nube, siguiendo buenas prácticas de separación de responsabilidades y diseño modular.
