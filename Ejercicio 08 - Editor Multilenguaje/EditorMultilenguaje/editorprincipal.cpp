#include "editorprincipal.h"

#include "appcontroller.h"
#include "lineawaretextedit.h"
#include "logger.h"
#include "validadorsintaxis.h"

#include <QCloseEvent>
#include <QComboBox>
#include <QDir>
#include <QFileInfo>
#include <QFrame>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QImage>
#include <QInputDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPlainTextEdit>
#include <QPixmap>
#include <QProcess>
#include <QPushButton>
#include <QRegularExpression>
#include <QResizeEvent>
#include <QSplitter>
#include <QStandardPaths>
#include <QTemporaryFile>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextFormat>
#include <QTextStream>
#include <QVBoxLayout>

EditorPrincipal::EditorPrincipal(AppController *controller, QWidget *parent)
    : Pantalla(controller, parent)
{
    inicializarUI();
    conectarEventos();
    cargarDatos();
}

EditorPrincipal::~EditorPrincipal()
{
    delete m_validadorActual;
}

void EditorPrincipal::inicializarUI()
{
    setWindowTitle("Editor Principal");
    setObjectName("EditorRoot");
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(12, 10, 12, 10);
    root->setSpacing(8);

    auto *topBar = new QFrame(this);
    topBar->setObjectName("TopBar");
    topBar->setMaximumHeight(52);
    auto *topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(10, 5, 10, 5);
    topBarLayout->setSpacing(8);

    auto *top = new QHBoxLayout();
    top->setSpacing(8);
    auto *lbl = new QLabel("Lenguaje:", this);
    lbl->setObjectName("TopLabel");
    m_selectorLenguaje = new QComboBox(this);
    m_selectorLenguaje->setObjectName("LanguageCombo");
    m_selectorLenguaje->addItems(QStringList() << "C++" << "Python" << "Java");
    m_selectorLenguaje->setMinimumHeight(28);
    m_selectorLenguaje->setMaximumHeight(30);
    auto *btnExportar = new QPushButton("Exportar JPG", this);
    btnExportar->setObjectName("ExportButton");
    btnExportar->setMinimumHeight(28);
    btnExportar->setMaximumHeight(30);
    auto *btnLimpiar = new QPushButton("Limpiar", this);
    btnLimpiar->setObjectName("ClearButton");
    btnLimpiar->setMinimumHeight(28);
    btnLimpiar->setMaximumHeight(30);
    m_diagnostico = new QLabel("Sin diagnostico.", this);
    m_diagnostico->setObjectName("DiagLabel");

    top->addWidget(lbl);
    top->addWidget(m_selectorLenguaje);
    top->addStretch();
    top->addWidget(btnLimpiar);
    top->addWidget(btnExportar);
    topBarLayout->addLayout(top);

    auto *compilerBar = new QFrame(this);
    compilerBar->setObjectName("CompilerBar");
    compilerBar->setMaximumHeight(40);
    auto *compilerLayout = new QHBoxLayout(compilerBar);
    compilerLayout->setContentsMargins(10, 4, 10, 4);
    compilerLayout->setSpacing(8);
    auto *compilerLbl = new QLabel("Chequeo:", this);
    compilerLbl->setObjectName("CompilerBarLabel");
    m_barraErrores = new QLabel("Esperando validacion...", this);
    m_barraErrores->setObjectName("CompilerBarValue");
    m_barraErrores->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    compilerLayout->addWidget(compilerLbl);
    compilerLayout->addWidget(m_barraErrores, 1);

    m_splitter = new QSplitter(this);
    m_splitter->setHandleWidth(12);
    m_editor = new LineAwareTextEdit(this);
    m_editor->setObjectName("CodeEditor");
    m_editor->setFrameStyle(QFrame::NoFrame);
    m_editor->setLineWrapMode(QPlainTextEdit::NoWrap);
    m_editor->setTabStopDistance(32.0);
    auto *panel = new QWidget(this);
    panel->setObjectName("ProfilePanel");
    auto *panelLayout = new QVBoxLayout(panel);
    panelLayout->setContentsMargins(18, 18, 18, 18);
    panelLayout->setSpacing(10);
    auto *foto = new QLabel(panel);
    foto->setObjectName("ProfilePhoto");
    foto->setFixedSize(120, 120);
    foto->setAlignment(Qt::AlignCenter);
    QPixmap px(":/new/foto1/EGRESADOSICO2023(152).jpg");
    if (px.isNull()) {
        px = QPixmap(120, 120);
        px.fill(Qt::lightGray);
    }
    foto->setPixmap(px.scaled(foto->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    auto *bio = new QLabel("Nombre: Lucas Guzman\nPerfil: Estudiante de Ingenieria en Informatica.\n\nExperiencia:\nDesarrollo de software backend, aplicaciones de escritorio y proyectos interactivos.\nImplementacion de sistemas cliente-servidor con despliegue en VPS.", panel);
    bio->setObjectName("ProfileBio");
    bio->setWordWrap(true);
    auto *skills = new QLabel("Habilidades tecnicas:\n- FastAPI\n- C++ con Qt\n- Docker\n- MySQL\n- Arquitectura cliente-servidor\n- Programacion orientada a objetos\n- Integracion de multiples componentes", panel);
    skills->setObjectName("ProfileBlock");
    auto *contacto = new QLabel("Contacto:\nMail: lguzmandominguez@ubp.edu.ar\nLinkedIn: lucasGuzman12", panel);
    contacto->setObjectName("ProfileBlock");
    panelLayout->addWidget(foto);
    panelLayout->addWidget(bio);
    panelLayout->addWidget(skills);
    panelLayout->addWidget(contacto);
    panelLayout->addStretch();

    m_splitter->addWidget(panel);
    m_splitter->addWidget(m_editor);
    m_splitter->setStretchFactor(1, 1);

    auto *statusBar = new QFrame(this);
    statusBar->setObjectName("StatusBar");
    statusBar->setMaximumHeight(32);
    auto *statusLayout = new QHBoxLayout(statusBar);
    statusLayout->setContentsMargins(8, 2, 8, 2);
    statusLayout->setSpacing(4);
    m_diagnostico->setMinimumHeight(18);
    m_diagnostico->setMaximumHeight(20);
    m_diagnostico->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    statusLayout->addWidget(m_diagnostico);

    root->addWidget(topBar);
    root->addWidget(m_splitter);
    root->addWidget(compilerBar);
    root->addWidget(statusBar);
    root->setStretch(1, 1);

    setStyleSheet(
        "#EditorRoot { background: #173a56; }"
        "#TopBar { background: #f6f9fc; border: 1px solid #b4c5d6; border-radius: 9px; }"
        "#TopLabel { color: #1f3042; font-size: 13px; font-weight: 600; }"
        "#LanguageCombo { color: #1c2d3e; background: #ffffff; border: 1px solid #a8bccf; border-radius: 7px; padding: 4px 8px; min-width: 132px; }"
        "#LanguageCombo:hover { border: 1px solid #7f9eb9; }"
        "#LanguageCombo:focus { border: 1px solid #2e74b7; }"
        "#LanguageCombo::drop-down { border: none; width: 20px; }"
        "#LanguageCombo QAbstractItemView { background: #ffffff; color: #1c2d3e; border: 1px solid #a8bccf; selection-background-color: #d7e9fb; selection-color: #10243a; }"
        "#ExportButton { background: #17665d; color: #ffffff; border: none; border-radius: 7px; padding: 5px 12px; font-weight: 600; }"
        "#ExportButton:hover { background: #13574f; }"
        "#ExportButton:pressed { background: #10473f; }"
        "#ClearButton { background: #5f6a78; color: #ffffff; border: none; border-radius: 7px; padding: 5px 12px; font-weight: 600; }"
        "#ClearButton:hover { background: #525c69; }"
        "#ClearButton:pressed { background: #454f5b; }"
        "#CompilerBar { background: #f6f9fc; border: 1px solid #b4c5d6; border-radius: 8px; }"
        "#CompilerBarLabel { color: #26384a; font-size: 12px; font-weight: 600; }"
        "#CompilerBarValue { color: #26384a; font-size: 12px; font-weight: 500; }"
        "#ProfilePanel { background: #f8fbff; border: 1px solid #b4c5d6; border-radius: 12px; }"
        "#ProfilePhoto { border: 2px solid #bfd0e0; border-radius: 60px; background: #eef4fa; }"
        "#ProfileBio { color: #1e3042; font-size: 13px; line-height: 1.35; }"
        "#ProfileBlock { color: #2b3f52; font-size: 13px; }"
        "#CodeEditor { color: #eef4ff; background: #111827; border: 1px solid #3a4a61; border-radius: 12px; font-family: 'Consolas'; font-size: 13px; selection-background-color: #2b4f75; selection-color: #f2f7ff; }"
        "#CodeEditor:focus { border: 1px solid #4e80b8; }"
        "#StatusBar { background: #f6f9fc; border: 1px solid #b4c5d6; border-radius: 7px; }"
        "#DiagLabel { color: #1f3042; font-weight: 500; padding: 0px 1px; }"
        "QSplitter::handle { background: #173a56; width: 12px; }");

    connect(btnExportar, SIGNAL(clicked()), this, SLOT(exportarJPG()));
    connect(btnLimpiar, SIGNAL(clicked()), this, SLOT(limpiarEditor()));
}

void EditorPrincipal::conectarEventos()
{
    connect(m_selectorLenguaje, SIGNAL(currentTextChanged(QString)), this, SLOT(cambiarLenguaje(QString)));
    connect(m_editor, SIGNAL(lineaAbandonada(int)), this, SLOT(validarLinea(int)));
    connect(m_editor, SIGNAL(focoPerdidoEnLinea(int)), this, SLOT(validarLineaFoco(int)));
}

void EditorPrincipal::cargarDatos()
{
    const QString def = m_controller->config().lenguajePorDefecto;
    const int idx = m_selectorLenguaje->findText(def);
    m_selectorLenguaje->setCurrentIndex(idx >= 0 ? idx : 0);
    cambiarLenguaje(m_selectorLenguaje->currentText());
}

bool EditorPrincipal::validarEstado()
{
    return m_validadorActual != nullptr;
}

void EditorPrincipal::registrarEvento(const QString &descripcion)
{
    Logger::log("Editor: " + descripcion);
}

void EditorPrincipal::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S) {
        exportarJPG();
        return;
    }
    registrarEvento("Tecla en editor.");
    QWidget::keyPressEvent(event);
}

void EditorPrincipal::mousePressEvent(QMouseEvent *event)
{
    registrarEvento("Click en editor principal.");
    QWidget::mousePressEvent(event);
}

void EditorPrincipal::resizeEvent(QResizeEvent *event)
{
    QList<int> sz;
    sz << width() / 4 << (width() * 3) / 4;
    m_splitter->setSizes(sz);
    registrarEvento("Resize editor.");
    QWidget::resizeEvent(event);
}

void EditorPrincipal::closeEvent(QCloseEvent *event)
{
    const auto r = QMessageBox::question(this, "Salir", "Desea exportar el codigo antes de salir?");
    if (r == QMessageBox::Yes) {
        exportarJPG();
    }
    registrarEvento("Cierre editor confirmado.");
    event->accept();
}

void EditorPrincipal::focusInEvent(QFocusEvent *event)
{
    registrarEvento("Focus in en editor.");
    QWidget::focusInEvent(event);
}

void EditorPrincipal::focusOutEvent(QFocusEvent *event)
{
    validarLineaFoco(m_editor->textCursor().blockNumber());
    registrarEvento("Focus out en editor.");
    QWidget::focusOutEvent(event);
}

void EditorPrincipal::cambiarLenguaje(const QString &lenguaje)
{
    delete m_validadorActual;
    m_validadorActual = nullptr;
    if (lenguaje == "C++") {
        m_validadorActual = new ValidadorCpp();
    } else if (lenguaje == "Python") {
        m_validadorActual = new ValidadorPython();
    } else {
        m_validadorActual = new ValidadorJava();
    }
    m_diagnostico->setText("Lenguaje activo: " + lenguaje);
    if (lenguaje == "C++") {
        actualizarBarraErrores("Chequeo por compilador C++ activado.", false);
        ejecutarChequeoCompiladorCpp();
    } else {
        m_lineaErrorCompilador = -1;
        actualizarResaltado();
        actualizarBarraErrores("Chequeo basico activo para " + lenguaje + ".", false);
    }
    registrarEvento("Cambio de lenguaje a " + lenguaje);
}

void EditorPrincipal::validarLinea(int linea)
{
    if (!m_validadorActual || linea < 0) {
        return;
    }
    QString diagnostico;
    const bool ok = m_validadorActual->validarLinea(textoLinea(linea), diagnostico);
    if (ok) {
        m_erroresPorLinea.remove(linea);
        m_diagnostico->setStyleSheet("background:#edf9f0; border:1px solid #bfe5c8; border-radius:6px; padding:2px 8px; color:#1b7f3a; font-weight:600;");
    } else {
        m_erroresPorLinea[linea] = diagnostico;
        m_diagnostico->setStyleSheet("background:#fff0f0; border:1px solid #efc4c4; border-radius:6px; padding:2px 8px; color:#b3261e; font-weight:700;");
    }
    m_diagnostico->setText(diagnostico);
    actualizarResaltado();

    if (m_selectorLenguaje->currentText() == "C++") {
        ejecutarChequeoCompiladorCpp();
    } else {
        actualizarBarraErrores(resumenErrorBasico(diagnostico), !ok);
    }
}

void EditorPrincipal::validarLineaFoco(int linea)
{
    validarLinea(linea);
    registrarEvento("Validacion por perdida de foco en linea " + QString::number(linea + 1));
}

void EditorPrincipal::exportarJPG()
{
    const QString ruta = m_controller->config().rutaExportacion;
    const QString texto = m_editor->toPlainText();
    const QStringList lineas = texto.split('\n');
    const int ancho = 1800;
    const int alto = qMax(1000, 40 + lineas.size() * 28);
    QImage img(ancho, alto, QImage::Format_RGB32);
    img.fill(Qt::white);
    QPainter p(&img);
    QFont font("Courier New");
    font.setPointSize(12);
    p.setFont(font);
    p.setPen(Qt::black);
    int y = 40;
    for (const QString &linea : lineas) {
        p.drawText(30, y, linea);
        y += 28;
    }
    p.end();
    const bool ok = img.save(ruta, "JPG", 95);
    if (ok) {
        m_diagnostico->setStyleSheet("background:#edf9f0; border:1px solid #bfe5c8; border-radius:6px; padding:2px 8px; color:#1b7f3a; font-weight:600;");
        m_diagnostico->setText("Exportado a: " + ruta);
        registrarEvento("Exportacion JPG exitosa en " + ruta);
    } else {
        m_diagnostico->setStyleSheet("background:#fff0f0; border:1px solid #efc4c4; border-radius:6px; padding:2px 8px; color:#b3261e; font-weight:700;");
        m_diagnostico->setText("No se pudo exportar JPG.");
        registrarEvento("Error al exportar JPG.");
    }
}

void EditorPrincipal::limpiarEditor()
{
    m_editor->clear();
    m_erroresPorLinea.clear();
    m_lineaErrorCompilador = -1;
    actualizarResaltado();
    m_diagnostico->setText("Editor limpiado.");
    if (m_selectorLenguaje->currentText() == "C++") {
        ejecutarChequeoCompiladorCpp();
    } else {
        actualizarBarraErrores("Editor limpio. Sin errores basicos.", false);
    }
    registrarEvento("Limpieza desde boton visual.");
}

void EditorPrincipal::actualizarResaltado()
{
    QList<QTextEdit::ExtraSelection> selections;
    for (auto it = m_erroresPorLinea.cbegin(); it != m_erroresPorLinea.cend(); ++it) {
        QTextEdit::ExtraSelection s;
        s.format.setBackground(QColor(185, 56, 56, 95));
        s.format.setProperty(QTextFormat::FullWidthSelection, true);
        QTextCursor c(m_editor->document()->findBlockByNumber(it.key()));
        c.select(QTextCursor::LineUnderCursor);
        s.cursor = c;
        selections.append(s);
    }

    if (m_lineaErrorCompilador >= 0) {
        QTextBlock block = m_editor->document()->findBlockByNumber(m_lineaErrorCompilador);
        if (block.isValid()) {
            QTextEdit::ExtraSelection s;
            s.format.setBackground(QColor(185, 56, 56, 95));
            s.format.setProperty(QTextFormat::FullWidthSelection, true);
            QTextCursor c(block);
            c.select(QTextCursor::LineUnderCursor);
            s.cursor = c;
            selections.append(s);
        }
    }
    m_editor->setExtraSelections(selections);
}

QString EditorPrincipal::textoLinea(int linea) const
{
    const QTextBlock block = m_editor->document()->findBlockByNumber(linea);
    return block.isValid() ? block.text() : QString();
}

void EditorPrincipal::actualizarBarraErrores(const QString &mensaje, bool esError)
{
    if (!m_barraErrores) {
        return;
    }
    m_barraErrores->setText(mensaje);
    if (esError) {
        m_barraErrores->setStyleSheet("color:#a32020; font-weight:600;");
    } else {
        m_barraErrores->setStyleSheet("color:#1f6f3f; font-weight:600;");
    }
}

void EditorPrincipal::ejecutarChequeoCompiladorCpp()
{
    const QString codigo = m_editor->toPlainText();
    if (codigo.trimmed().isEmpty()) {
        m_lineaErrorCompilador = -1;
        actualizarBarraErrores("C++: sin codigo para validar.", false);
        actualizarResaltado();
        return;
    }

    QString compilador = QStandardPaths::findExecutable("g++");
    if (compilador.isEmpty()) {
        compilador = QStandardPaths::findExecutable("clang++");
    }
    if (compilador.isEmpty()) {
        m_lineaErrorCompilador = -1;
        actualizarBarraErrores("No se encontro g++/clang++. Se usa validacion basica.", true);
        actualizarResaltado();
        return;
    }

    QTemporaryFile tempFile(QDir::tempPath() + "/editor_multilenguaje_XXXXXX.cpp");
    tempFile.setAutoRemove(true);
    if (!tempFile.open()) {
        m_lineaErrorCompilador = -1;
        actualizarBarraErrores("No se pudo crear archivo temporal para compilar.", true);
        actualizarResaltado();
        return;
    }

    QTextStream out(&tempFile);
    out << codigo;
    out.flush();
    tempFile.flush();

    QProcess process;
    QStringList args;
    args << "-fsyntax-only" << "-std=c++17" << tempFile.fileName();
    process.start(compilador, args);
    if (!process.waitForStarted(1500)) {
        m_lineaErrorCompilador = -1;
        actualizarBarraErrores("No se pudo iniciar el compilador C++.", true);
        actualizarResaltado();
        return;
    }
    if (!process.waitForFinished(4000)) {
        process.kill();
        m_lineaErrorCompilador = -1;
        actualizarBarraErrores("Tiempo agotado en chequeo de compilacion C++.", true);
        actualizarResaltado();
        return;
    }

    const QString stderrSalida = QString::fromLocal8Bit(process.readAllStandardError());
    if (process.exitCode() == 0) {
        m_lineaErrorCompilador = -1;
        if (stderrSalida.trimmed().isEmpty()) {
            actualizarBarraErrores("C++ compilador: sin errores sintacticos.", false);
        } else {
            const QString info = extraerMensajeCompilador(stderrSalida, tempFile.fileName());
            actualizarBarraErrores("C++ aviso: " + info, false);
        }
        actualizarResaltado();
        return;
    }

    m_lineaErrorCompilador = extraerLineaErrorCompilador(stderrSalida, tempFile.fileName());
    const QString msg = extraerMensajeCompilador(stderrSalida, tempFile.fileName());
    actualizarBarraErrores("C++ error: " + msg, true);
    actualizarResaltado();
}

QString EditorPrincipal::extraerMensajeCompilador(const QString &salida, const QString &archivoTemporal) const
{
    const QStringList lineas = salida.split('\n', Qt::SkipEmptyParts);
    QString mejor;
    for (const QString &raw : lineas) {
        const QString l = raw.trimmed();
        if (l.contains(": error:") || l.contains(": fatal error:")) {
            mejor = l;
            break;
        }
        if (mejor.isEmpty() && (l.contains(": warning:") || l.contains("error:"))) {
            mejor = l;
        }
    }
    if (mejor.isEmpty()) {
        mejor = salida.simplified();
    }
    if (mejor.isEmpty()) {
        return "Diagnostico no disponible.";
    }

    QString limpio = mejor;
    limpio.replace(archivoTemporal, "temp.cpp");
    QRegularExpression prefijo("^temp\\.cpp:(\\d+):(\\d+):\\s*");
    auto match = prefijo.match(limpio);
    if (match.hasMatch()) {
        limpio.remove(0, match.capturedLength());
        limpio = "L" + match.captured(1) + " C" + match.captured(2) + ": " + limpio;
    }
    return limpio;
}

int EditorPrincipal::extraerLineaErrorCompilador(const QString &salida, const QString &archivoTemporal) const
{
    const QString escaped = QRegularExpression::escape(archivoTemporal);
    const QRegularExpression rxPath("^" + escaped + ":(\\d+):(\\d+):\\s*(fatal\\s+error|error):");
    const QRegularExpression rxTemp("^temp\\.cpp:(\\d+):(\\d+):\\s*(fatal\\s+error|error):");

    const QStringList lineas = salida.split('\n', Qt::SkipEmptyParts);
    for (const QString &raw : lineas) {
        const QString l = raw.trimmed();
        QRegularExpressionMatch m = rxPath.match(l);
        if (!m.hasMatch()) {
            m = rxTemp.match(l);
        }
        if (m.hasMatch()) {
            const int line1 = m.captured(1).toInt();
            return qMax(0, line1 - 1);
        }
    }
    return -1;
}

QString EditorPrincipal::resumenErrorBasico(const QString &diagnostico) const
{
    if (diagnostico.contains("Parentesis", Qt::CaseInsensitive)) {
        return "Chequeo basico: parentesis desbalanceados.";
    }
    if (diagnostico.contains("llaves", Qt::CaseInsensitive)) {
        return "Chequeo basico: uso invalido de llaves.";
    }
    if (diagnostico.contains("print", Qt::CaseInsensitive)) {
        return "Chequeo basico: sintaxis de print incorrecta.";
    }
    if (diagnostico.contains("cout", Qt::CaseInsensitive)) {
        return "Chequeo basico: uso de cout invalido.";
    }
    if (diagnostico.contains(";", Qt::CaseInsensitive)) {
        return "Chequeo basico: posible falta de ';'.";
    }
    return "Chequeo basico: sin errores relevantes.";
}
