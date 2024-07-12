#ifndef NEWPLAYLISTDIALOG_H
#define NEWPLAYLISTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>

class NewPlaylistDialog : public QDialog
{
    Q_OBJECT

public:
    NewPlaylistDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *nameLabel = new QLabel("Playlist Name:", this);
        nameEdit = new QLineEdit(this);

        QLabel *publicLabel = new QLabel("Is Public:", this);
        publicCheckBox = new QCheckBox(this);

        QPushButton *uploadImageButton = new QPushButton("Upload Image", this);

        QPushButton *okButton = new QPushButton("OK", this);
        QPushButton *cancelButton = new QPushButton("Cancel", this);

        layout->addWidget(nameLabel);
        layout->addWidget(nameEdit);
        layout->addWidget(publicLabel);
        layout->addWidget(publicCheckBox);
        layout->addWidget(uploadImageButton);
        layout->addWidget(okButton);
        layout->addWidget(cancelButton);

        connect(uploadImageButton, &QPushButton::clicked, this, &NewPlaylistDialog::onUploadImageClicked);
        connect(okButton, &QPushButton::clicked, this, &NewPlaylistDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &NewPlaylistDialog::reject);
    }

    QString playlistName() const
    {
        return nameEdit->text();
    }

    bool isPublic() const
    {
        return publicCheckBox->isChecked();
    }

    QString imagePath() const
    {
        return selectedImagePath;
    }

private slots:
    void onUploadImageClicked()
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Choose Image"), "", tr("Images (*.png *.jpg *.jpeg)"));
        if (!fileName.isEmpty())
        {
            selectedImagePath = fileName;
            // Optionally, display the selected image or show its path
            // For example:
            // QLabel *imageLabel = new QLabel("Selected Image: " + fileName, this);
            // layout->addWidget(imageLabel);
        }
    }

private:
    QLineEdit *nameEdit;
    QCheckBox *publicCheckBox;
    QString selectedImagePath;
};
#endif // NEWPLAYLISTDIALOG_H
