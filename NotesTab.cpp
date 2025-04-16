
#include "NotesTab.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>
#include <QMessageBox>

NotesTab::NotesTab(QWidget *parent)
    : QWidget(parent) {
}

void NotesTab::addToTabWidget(QTabWidget* widget) {
    notesTab = new QWidget(this);
    QVBoxLayout *notesLayout = new QVBoxLayout(notesTab);

    QGridLayout *gridLayout = new QGridLayout();
    notesLayout->addLayout(gridLayout);

    noteTitleField = new QLineEdit(this);
    noteTitleField->setPlaceholderText("Note title...");

    saveNoteButton = new QPushButton("Save Note", this);
    deleteNoteButton = new QPushButton("Delete Note", this);

    gridLayout->addWidget(noteTitleField, 0, 0);
    gridLayout->addWidget(saveNoteButton, 1, 0);
    gridLayout->addWidget(deleteNoteButton, 1, 1);

    notesEditor = new QTextEdit(this);
    notesEditor->setPlaceholderText("Write your notes here...");
    notesLayout->addWidget(notesEditor);

    // Ensure Notes folder exists
    QDir().mkpath(notesDirectoryPath);

    // Set up file system model
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(notesDirectoryPath);
    fileModel->setNameFilters(QStringList() << "*.txt");
    fileModel->setNameFilterDisables(false);

    fileTree = new QTreeView(this);
    fileTree->setModel(fileModel);
    fileTree->setRootIndex(fileModel->index(notesDirectoryPath));
    fileTree->setColumnHidden(1, true); // Size
    fileTree->setColumnHidden(2, true); // Type
    fileTree->setColumnHidden(3, true); // Modified

    notesLayout->addWidget(fileTree);

    widget->addTab(notesTab, "Notes");

    connect(saveNoteButton, &QPushButton::clicked, this, &NotesTab::saveNote);
    connect(deleteNoteButton, &QPushButton::clicked, this, &NotesTab::deleteNote);
    connect(fileTree, &QTreeView::clicked, this, &NotesTab::loadNote);
}

void NotesTab::saveNote() {
    QString title = noteTitleField->text().trimmed();
    if (title.isEmpty()) {
        QMessageBox::warning(this, "Empty Title", "Please enter a title for the note.");
        return;
    }

    QString filename = notesDirectoryPath + "/" + title + ".txt";
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save the note.");
        return;
    }

    QTextStream out(&file);
    out << notesEditor->toPlainText();
    file.close();
}

void NotesTab::deleteNote() {
    QString title = noteTitleField->text().trimmed();
    if (title.isEmpty()) return;

    QString filename = notesDirectoryPath + "/" + title + ".txt";
    if (!QFile::exists(filename)) {
        QMessageBox::information(this, "Note Not Found", "The note does not exist.");
        return;
    }

    if (!QFile::remove(filename)) {
        QMessageBox::warning(this, "Delete Failed", "Unable to delete the note.");
        return;
    }

    noteTitleField->clear();
    notesEditor->clear();
}

void NotesTab::loadNote(const QModelIndex &index) {
    QString filePath = fileModel->filePath(index);
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Load Error", "Unable to open the note.");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QString title = QFileInfo(filePath).baseName();

    noteTitleField->setText(title);
    notesEditor->setPlainText(content);
}
