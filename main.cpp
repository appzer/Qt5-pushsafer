#include <QApplication>

#include "pushsafer.h"

PushSafer ps;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//ps.Push(QString Title, QString Message, QString Device, QString Priority, QString Sound, QString Vibration, QString Icon, QString IconColor, QString Time2Live, QString Retry, QString Expire, QString Confirm, QString Answer, QString AnswerOptions, QString URL, QString URLTitle, QString Giphy, QString Image1, QString Image2, QString Image3, QString ImageSize)
    ps.Push("Title", "Message...", "a", "2", "15", "3", "45", "#FF0000", "0", "", "", "", "1", "Yes|No|Maybe", "https://www.pushsafer.com", "Open Pushsafer", "", "", "", "", "0"); // send Push-Notification

    return a.exec();
}
