#ifndef NOTESTAB_H
#define NOTESTAB_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QFileSystemModel>
#include <QTreeView>
#include <QTabWidget>
#include <QString>

class NotesTab : public QWidget {
    Q_OBJECT

public:
    explicit NotesTab(QWidget *parent = nullptr);
    void addToTabWidget(QTabWidget* widget);

private slots:
    void saveNote();
    void deleteNote();
    void loadNote(const QModelIndex &index);

private:
    QWidget *notesTab;
    QLineEdit *noteTitleField;
    QTextEdit *notesEditor;
    QPushButton *saveNoteButton;
    QPushButton *deleteNoteButton;

    QFileSystemModel *fileModel;
    QTreeView *fileTree;
    QString notesDirectoryPath = "Notes";
};

#endif // NOTESTAB_H

