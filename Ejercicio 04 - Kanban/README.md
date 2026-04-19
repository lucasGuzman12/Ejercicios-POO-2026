# Ejercicio 04 - Tablero Kanban Colaborativo (Qt + API)

## 📌 Descripción

Este proyecto consiste en el desarrollo de una aplicación de escritorio en **Qt** que permite gestionar tareas mediante un tablero tipo **Kanban**, utilizando un backend desarrollado en **FastAPI** desplegado en un VPS y persistencia en **MySQL**.

El sistema permite realizar operaciones CRUD completas, mover tarjetas entre columnas, mantener el orden de las mismas y actualizar la información de forma colaborativa.

---

## 🧩 Arquitectura del Proyecto

El proyecto se divide en dos partes principales:

### 🔹 Backend (VPS)

* API de Kanban (FastAPI)
* Base de datos MySQL
* Archivos para Docker
* Sistema de autenticación general (no se encuentra en esta carpeta)

> ⚠️ Nota: Se utilizó el sistema de autenticación general para este proyecto, el cual se encuentra en su respectiva carpeta "AUTENTICACION-USUARIOS" en este repositorio y cuenta con su propio README.

### 🔹 Aplicación de Escritorio en QT (Cliente)

* Interfaz gráfica tipo tablero Kanban
* Comunicación con la API del VPS
* Gestión de columnas y tarjetas

---

## ⚙️ Funcionalidades

### Backend (FastAPI)

* CRUD de columnas
* CRUD de tarjetas
* Movimiento de tarjetas entre columnas
* Reordenamiento de tarjetas dentro de una columna
* Persistencia en base de datos MySQL

### Base de Datos (MySQL)

Tablas utilizadas:

* `columns`
* `cards`
* `card_order`

### Aplicación Qt

* Visualización del tablero Kanban
* Creación, edición y eliminación de columnas y tarjetas
* Movimiento de tarjetas (por botones)
* Actualización en tiempo real (polling cada 4 segundos)

---

## 🔄 Persistencia

El estado del tablero se mantiene en la base de datos, por lo que al reiniciar la aplicación, la información se conserva sin pérdidas.

---

## 🌐 Endpoints de la API (Resumen)

El backend expone los siguientes endpoints principales:

* `GET /board`: Obtiene el estado completo del tablero, incluyendo columnas y tarjetas.
* `POST /columns`: Crea una nueva columna en el tablero.
* `PUT /columns/{column_id}`: Actualiza la información de una columna existente.
* `DELETE /columns/{column_id}`: Elimina una columna y sus tarjetas asociadas.
* `POST /cards`: Crea una nueva tarjeta dentro de una columna.
* `PUT /cards/{card_id}`: Modifica los datos de una tarjeta existente.
* `DELETE /cards/{card_id}`: Elimina una tarjeta del tablero.
* `POST /cards/{card_id}/move`: Mueve una tarjeta de una columna a otra.
* `POST /cards/{card_id}/reorder`: Cambia el orden de una tarjeta dentro de su columna.

---

## 🧾 Formato JSON de los Endpoints

A continuación se muestra el formato de datos que utiliza cada endpoint:

### 🔹 GET /board (Response)

```json
{
  "columns": [
    {
      "id": 1,
      "title": "To Do",
      "position": 0,
      "cards": [
        {
          "id": 10,
          "title": "Tarea",
          "description": "Descripción",
          "position": 0
        }
      ]
    }
  ]
}
```

---

### 🔹 POST /columns (Request)

```json
{
  "title": "Nueva columna"
}
```

### 🔹 POST /columns (Response)

```json
{
  "message": "created"
}
```

---

### 🔹 PUT /columns/{column_id} (Request)

```json
{
  "title": "Nuevo título"
}
```

### 🔹 PUT /columns/{column_id} (Response)

```json
{
  "message": "updated"
}
```

---

### 🔹 DELETE /columns/{column_id} (Response)

```json
{
  "message": "deleted"
}
```

---

### 🔹 POST /cards (Request)

```json
{
  "title": "Nueva tarjeta",
  "description": "Detalle",
  "column_id": 1
}
```

### 🔹 POST /cards (Response)

```json
{
  "message": "created"
}
```

---

### 🔹 PUT /cards/{card_id} (Request)

```json
{
  "title": "Nuevo título",
  "description": "Nuevo detalle",
  "column_id": 2
}
```

### 🔹 PUT /cards/{card_id} (Response)

```json
{
  "message": "updated"
}
```

---

### 🔹 DELETE /cards/{card_id} (Response)

```json
{
  "message": "deleted"
}
```

---

### 🔹 POST /cards/{card_id}/move (Request)

```json
{
  "to_column_id": 2,
  "new_position": 0
}
```

### 🔹 POST /cards/{card_id}/move (Response)

```json
{
  "message": "moved"
}
```

---

### 🔹 POST /cards/{card_id}/reorder (Request)

```json
{
  "new_position": 1
}
```

### 🔹 POST /cards/{card_id}/reorder (Response)

```json
{
  "message": "reordered"
}
```

---

## 🎯 Objetivo del Ejercicio

Consolidar el uso de:

* APIs REST
* Integración frontend-backend
* Manejo de estado persistente
* Interfaces gráficas con Qt
* Sistemas colaborativos básicos

---

## 🚀 Tecnologías Utilizadas

* **Frontend:** Qt (C++) + Codex
* **Backend:** FastAPI (Python)
* **Base de datos:** MySQL
* **Infraestructura:** VPS + Docker

---

## 📌 Notas Finales

Este proyecto forma parte de una serie de ejercicios independientes dentro del repositorio, compartiendo componentes comunes como el sistema de autenticación.
