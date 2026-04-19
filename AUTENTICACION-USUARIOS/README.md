# Sistema de Autenticación General (FastAPI + MySQL)

## 📌 Descripción

Este proyecto implementa un sistema de autenticación basado en **FastAPI** que permite registrar usuarios, iniciar sesión y validar tokens.

Está diseñado como un módulo **general y reutilizable**, pensado para integrarse fácilmente en distintos proyectos sin necesidad de modificar su lógica interna.

---

## 🎯 Objetivo

Proveer un sistema de autenticación simple, desacoplado y reutilizable que permita:

* Registrar usuarios
* Autenticar credenciales
* Generar tokens JWT
* Validar usuarios autenticados desde otros sistemas

---

## 📁 Estructura del Proyecto

```
AUTENTICACION-USUARIOS/
│
├── app/
│   └── main.py          # Lógica principal de la API
│
├── Dockerfile           # Imagen del servicio
├── docker-compose.yml   # Orquestación con MySQL y phpmyadmin
├── requirements.txt     # Dependencias del proyecto
```

---

## ⚙️ Funcionamiento General

El sistema se basa en:

* **FastAPI** como framework backend
* **MySQL** como base de datos
* **JWT (JSON Web Tokens)** para autenticación
* **SQLAlchemy** para acceso a datos

### 🔐 Flujo de autenticación

1. El usuario se registra (`/register`)
2. Luego inicia sesión (`/login`)
3. Se genera un **token JWT**
4. Otros sistemas utilizan ese token para validar al usuario (`/verify`)

---

## 🗄️ Base de Datos

Se utiliza una única tabla:

### `users`

* `id`: Identificador único
* `username`: Nombre de usuario (único)
* `password`: Contraseña (almacenada en texto plano en este ejercicio)

---

## 🌐 Endpoints

### 🔹 `GET /health`

Verifica que el servicio esté activo.

---

### 🔹 `POST /register`

Registra un nuevo usuario.

**Body:**

```json
{
  "username": "usuario",
  "password": "password"
}
```

---

### 🔹 `POST /login`

Autentica un usuario y devuelve un token JWT.

**Body:**

```json
{
  "username": "usuario",
  "password": "password"
}
```

**Respuesta:**

```json
{
  "access_token": "TOKEN",
  "token_type": "bearer"
}
```

---

### 🔹 `GET /verify`

Valida un token JWT.

**Query param:**

```
?token=TOKEN
```

**Respuesta:**

```json
{
  "valid": true,
  "user": "usuario"
}
```

---

## 🔑 Generación de Tokens

Los tokens JWT:

* Incluyen el usuario (`sub`)
* Tienen una expiración de **2 horas**
* Se firman con `HS256` y una `SECRET_KEY`

---

## 🚀 Despliegue

El sistema está preparado para ejecutarse con **Docker**:

* `docker-compose.yml` levanta:

  * Servicio de autenticación
  * Base de datos MySQL

---

## ⚠️ Consideraciones

* Las contraseñas se almacenan en texto plano (solo para fines académicos)
* No incluye refresh tokens
* No maneja roles ni permisos
* Pensado para integrarse con otros sistemas mediante HTTP

---

## 📌 Notas Finales

Este sistema fue diseñado como un componente **genérico y reutilizable**, por lo que puede integrarse en múltiples proyectos sin necesidad de modificaciones estructurales.
