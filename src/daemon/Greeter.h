/***************************************************************************
* Copyright (c) 2013 Abdurrahman AVCI <abdurrahmanavci@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the
* Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***************************************************************************/

#ifndef SDDM_GREETER_H
#define SDDM_GREETER_H

#include <QObject>

#include "qauth/QAuth.h"

namespace SDDM {
    class Session;
    class Display;

    class Greeter : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY(Greeter)
    public:
        explicit Greeter(QObject *parent = 0);
        ~Greeter();

        void setDisplay(Display *display);
        void setAuthPath(const QString &authPath);
        void setSocket(const QString &socket);
        void setTheme(const QString &theme);

    public slots:
        bool start();
        void stop();
        void finished();

    private slots:
        void onRequestChanged();
        void onSessionStarted(bool success);
        void onHelperFinished(bool success);
        void onReadyReadStandardOutput();
        void onReadyReadStandardError();
        void authInfo(const QString &message, QAuth::Info info);
        void authError(const QString &message, QAuth::Error error);

    private:
        bool m_started { false };

        Display *m_display { nullptr };
        QString m_authPath { "" };
        QString m_socket { "" };
        QString m_theme { "" };

        QAuth *m_auth { nullptr };
        Session *m_process { nullptr };
    };
}

#endif // SDDM_GREETER_H
