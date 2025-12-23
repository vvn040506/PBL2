#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>

class StartupDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StartupDialog(QWidget *parent = nullptr);
    StartupDialog(const StartupDialog&) = delete;
    StartupDialog& operator=(const StartupDialog&) = delete;

public slots:
    void addStatusMessage(const QString &message, bool isSuccess = true);
    void updateProgress(int value);
    void showContinueButton();
    void onReadDataChoiceClicked(bool readData);

private:
    void setupUI();

    QProgressBar *progressBar;
    QVBoxLayout *statusLayout;
    QPushButton *continueBtn;
signals:
    void continueClicked();
};

#endif // STARTUPDIALOG_H
