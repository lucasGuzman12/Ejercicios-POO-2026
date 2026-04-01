# 🗂️ Ejercicio 01 - Planificador de Trabajos Prácticos

## 📌 Descripción

Aplicación desarrollada en Qt que permite planificar trabajos prácticos, incluyendo funcionalidades de autenticación, seguimiento de entregas y persistencia de datos a nivel local.

## 🎯 Objetivo

Implementar una solución que integre conceptos de **Programación Orientada a Objetos** junto con el uso de **Qt (QWidget)**, permitiendo gestionar trabajos prácticos de manera organizada. Utilizar las herramientas modernas de desarrollo basado en IA, debido al escaso conocimiento sobre QT en estas etapas iniciales.

---

## ⚙️ Funcionalidades implementadas

- 🔐 **Login de usuarios**
  - Validación contra archivo local (CSV o JSON)

- ⏳ **Persistencia de sesión**
  - Recordatorio de sesión por 5 minutos mediante archivo local

- 📋 **Tablero de trabajos prácticos**
  - Visualización en grilla usando `QGridLayout`
  - Cada fila contiene información del trabajo y botones de acción
  - Filtro por estado y/o prioridad

- ✏️ **Gestión de trabajos prácticos**
  - Alta
  - Edición
  - Eliminación

- 📝 **Editor de notas**
  - Asociado a cada trabajo práctico
  - Guardado manual

- 📜 **Historial de acciones**
  - Visualización en la interfaz
  - Persistencia en archivo

---

## 🧱 Requisitos técnicos

- ❌ No se utilizó QML  
- ✅ Se utilizó `QWidget` (sin `QMainWindow`)  
- ✅ Código organizado en múltiples clases (no todo en `main.cpp`)  

---

## 🛠️ Tecnologías utilizadas

- Lenguaje: C++  
- Framework: Qt (Widgets)
- Herramienta de Vibecoding: Extensión "GPT-5.2 Codex" en VSCode

---

## ▶️ Instrucciones de compilación y ejecución

1. Abrir el proyecto en Qt Creator  
2. Compilar el proyecto  
3. Ejecutar la aplicación  

---

## 📸 Capturas requeridas

- Pantalla de login
<img width="365" height="255" alt="image" src="https://github.com/user-attachments/assets/2070b512-edf4-4d42-b3c7-ff3a395aea6e" />


- Tablero con filtros aplicados
<img width="904" height="633" alt="image" src="https://github.com/user-attachments/assets/07998ee0-9dac-4f16-ba19-82f47bfe34f9" />
<img width="905" height="636" alt="image" src="https://github.com/user-attachments/assets/608d6f08-2315-4935-8153-afc777637942" />


- Editor de notas con estado guardado
<img width="903" height="634" alt="image" src="https://github.com/user-attachments/assets/1f1adc21-6d15-47dc-b174-67f85df57902" />


- Historial de acciones  
<img width="879" height="245" alt="image" src="https://github.com/user-attachments/assets/27941a45-143d-4eeb-89b9-a92f7a7c6aa2" />

---

✏️ *Ejercicio individual correspondiente a la materia Programación Orientada a Objetos.*
